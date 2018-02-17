/*********************************************************
This is a library for the MPR121 12-channel Capacitive touch sensor

Designed specifically to work with the MPR121 Breakout in the Adafruit shop 
  ----> https://www.adafruit.com/products/

These sensors use I2C communicate, at least 2 pins are required 
to interface

Adafruit invests time and resources providing this open source code, 
please support Adafruit and open-source hardware by purchasing 
products from Adafruit!

Written by Limor Fried/Ladyada for Adafruit Industries.  
BSD license, all text above must be included in any redistribution
**********************************************************/

#include "Adafruit_TinyMPR121.h"

// You can have up to 4 on one i2c bus but one is enough for testing!
Adafruit_TinyMPR121 cap = Adafruit_TinyMPR121();

//pin 1 is red led on Trinket
#define ledPin 1

uint16_t currtouched = 0;

void setup() {

  pinMode(ledPin, OUTPUT);
  digitalWrite(ledPin, LOW); //turn led off for 1 second
  delay(1000);
  
  // Default address is 0x5A, if tied to 3.3V its 0x5B
  // If tied to SDA its 0x5C and if SCL then 0x5D
  if (!cap.begin(0x5A)) {
    digitalWrite(ledPin, HIGH);
    delay(500);
    // Dim led to indicate failure
    analogWrite(ledPin, 16);
    while (1);
  }

  //if initialized OK, turn led on for 2 seconds
  digitalWrite(ledPin, HIGH);
  delay(2000);
  digitalWrite(ledPin, LOW);

}

void loop() {
  // Get the currently touched pads
  currtouched = cap.touched();

  // Touch contact 0 to turn on the built in LED
  if (currtouched & _BV(0)) {
    digitalWrite(ledPin, HIGH);
    return;
  }

  // Touch contact 11 to turn off the built in LED
  if (currtouched & _BV(11)) {
    digitalWrite(ledPin, LOW);
    return;
  }

  delay(10);
}
