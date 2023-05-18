
// File based on the tutorial: https://randomnerdtutorials.com/arduino-k-type-thermocouple-max6675/
#include "max6675.h"

int thermoDO = 4;
int thermoCS = 5;
int thermoCLK = 6;

MAX6675 thermocouple(thermoCLK, thermoCS, thermoDO);

void setup() {
  Serial.begin(9600);

  Serial.println("MAX6675 test");
  // waiting for the MAX chip to stabilize
  delay(500); // Might need to bake this into the final program.
}

void loop() {

  Serial.print("C = ");
  Serial.println(thermocouple.readCelsius());
  // there must be a delay of atleast 250ms between each read.
  delay(500); // delay uses milliseconds as the understood input magnitude.



}
