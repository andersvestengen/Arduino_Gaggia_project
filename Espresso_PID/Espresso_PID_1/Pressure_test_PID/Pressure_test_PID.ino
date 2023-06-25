// Pressure sensor setup
int PressureAnalogIn = A1;

void setup() {

}

void loop() {
  int PressureReading = analogRead(PressureAnalogIn);
  double CurrentPressure = PressureCalc(PressureReading);

  // print outputs
  Serial.println(CurrentPressure);

}

double PressureCalc(int Vsig){

  double pressure;


  pressure = 12 * (Vsig - 102) / 818;

  if (pressure < 0)
  {
    pressure = 0;
  };

  return pressure;

}