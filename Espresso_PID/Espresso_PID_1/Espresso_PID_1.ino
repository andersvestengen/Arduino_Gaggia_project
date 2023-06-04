// File based on the tutorial: https://randomnerdtutorials.com/arduino-k-type-thermocouple-max6675/
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
dimmerlamp dimmer(11, 12);

void setup() {
  //Setup writing to console for testing. TBD
  Serial.begin(9600);

  // Define octocoupler as digital input
  dimmer.toggleSettings(0,100); // sets the dimmermode operating range when (smooth) toggling mode is enabled
  dimmer.setState(OFF); // toggles dimmer on or off  
  pinMode(ZeroCross_Pin, INPUT);
  


}

void loop() {


  //feed octo output to dimmer ZC pin.
  digitalWrite(DimmerZC, digitalRead(ZeroCross_PIN)); // feed octo zero-cross events to the dimmer ZC input







  Serial.print("C = ");
  Serial.println(thermocouple.readCelsius());
  // there must be a delay of atleast 250ms between each read.
  delay(500); // delay uses milliseconds as the understood input magnitude.



}
