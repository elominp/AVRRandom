# AVRRandom

A simple library to seed Arduino random number generators for AVR mcu using the internal ram behaviour.

There are some articles about how it works on the internet, like this one on HaD: https://hackaday.com/2015/06/29/true-random-number-generator-for-a-true-hacker/

This library implements this phenomenon on a simple basis, just taking 4 bytes of uninitialized RAM (at least if used at an early stage) in the middle of the address space between the stack and the heap, give them as a seed to the PRNG and overwrite them with 4 bytes generated by the PRNG so the next time it's called we're sure it won't use the same seed again if no electrical reset of the RAM occured.

## How to use it?

Include the `AVRRandom.h` header in your sketch and call the `initSeed` function in the `setup` function of your sketch (preferably the first thing to do).

For example you can take a look of this code (also available as the `PrintRandomNumber` example sketch in the library):

```
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
```
