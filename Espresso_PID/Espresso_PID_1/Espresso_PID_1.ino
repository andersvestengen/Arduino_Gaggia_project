// File based on the tutorial: https://randomnerdtutorials.com/arduino-k-type-thermocouple-max6675/
#include "math.h"

// MAX thermal sensor setup
#include "max6675.h"

int thermoDO = 6;
int thermoCS = 5;
int thermoCLK = 4;

MAX6675 thermocouple(thermoCLK, thermoCS, thermoDO);

// Dimmer setup
#include <RBDdimmer.h>

int ZeroCross_Pin = 14; // A0 pin
int DimmerDIM = 11;
int DimmerZC = 12;
dimmerLamp dimmer(11, 12);

// Pressure sensor setup
int PressureAnalogIn = A1;


// PID setup
#include <PID_v1.h>
// setup for the pressure PID loop
double input, output, setpoint;
PID PressurePID(&input, &output, &setpoint, 2, 5, 1, DIRECT);

// setup for the temperature PID loop
// We can assume SSR is normally off 
double, Tinput, Toutput, Tsetpoint;
PID TemperaturePID(&Tinput, &Toutput, &Tsetpoint, 2, 5, 1, DIRECT);
int WindowSize = 3000; // 3s wait between relay on/off
unsigned long windowSTartTime;

// SSR Relay setup
#define RelayPin 2


void setup() {
  //Setup writing to console for testing. TBD
  Serial.begin(9600);

  // Define octocoupler as digital input
  dimmer.toggleSettings(0,100); // sets the dimmermode operating range when (smooth) toggling mode is enabled
  dimmer.begin(NORMAL_MODE, ON); // toggles dimmer on or off  
  pinMode(ZeroCross_Pin, INPUT);
  int PressureReading;
  double CurrentPressure;

  // Define and initialize Pressure PID values
  setpoint = 9;
  PressurePID.setMode(AUTOMATIC)
  Pressure.setOutputLimits(0, 100);

  // Define and Initalize Temperature PID values
  Tsetpoint = 93;
  pinMode(RelayPin, OUTPUT);
  windowStartTime = millis();
  TemperaturePID.SetOutputLimits(0, WindowSize);
  TemperaturePID.SetMode(AUTOMATIC)

}

void loop() {


  //feed octo output to dimmer ZC pin.
  digitalWrite(DimmerZC, digitalRead(ZeroCross_PIN)); // feed octo zero-cross events to the dimmer ZC input
  
  // Calculate current pressure
  PressureReading = analogRead(PressureAnalogIn);
  CurrentPressure = PressureCalc(PressureReading);

  //Run PID calc for pressure loop
  input = CurrentPressure;
  PressurePID.compute();

  //Output PID proportion to Dimmer
  dimmer.setPower(int(output));

  // Read temperature and compute PID
  Tinput (double) thermocouple.readCelsius();
  TemperaturePID.Compute();
  unsigned long now = millis();
  if (now - windowStartTime > WindowSize)
  { //time to shift the Relay Window
    windowStartTime += WindowSize;
  }
  if (Toutput > now - windowStartTime) digitalWrite(RelayPin, HIGH);
  else digitalWrite(RelayPin, LOW);
  
  // print outputs
  Serial.print("C = ");
  Serial.println(thermocouple.readCelsius());

  Serial.print("P = ");
  Serial.println(CurrentPressure);
}

double PressureCalc(int Vsig){

  double pressure;
  int Vmin = 0.5;
  int Vmax = 4; // this is Vmax - Vmin 
  int MaxBar = 12;
  int ADC = 1024;


  pressure = MaxBar * (Vsig*ADC - Vmin) / Vmax;

  return pressure;

}