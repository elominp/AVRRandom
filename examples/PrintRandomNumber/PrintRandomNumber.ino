#include <AVRRandom.h>

// Example inspired from https://www.arduino.cc/reference/en/language/functions/random-numbers/random/

long randNumber;

void setup() {
  // put your setup code here, to run once:
  initSeed(); // Seed the random number generator
  Serial.begin(9600);
  delay(1000);
  Serial.print(F("Seed = "));
  Serial.println(getSeed());
}

void loop() {
  // print a random number from 0 to 299
  randNumber = random(300);
  Serial.println(randNumber);

  // print a random number from 10 to 19
  randNumber = random(10, 20);
  Serial.println(randNumber);

  delay(50);
}