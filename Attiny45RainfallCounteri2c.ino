// Based on the Wire Slave Sender
// by Nicholas Zambetti <http://www.zambetti.com>

// This example records rainfall ticks from a tipping bucket rainfall sensor, and sends them over i2c when requested by the weather station before resetting the count.
// If it has worked, it write (ok#) where # is the number of ticks. This is polled by my setup every 15 mins, so I request 3 bits, as I doubt it is ever going to be over 255 'ticks' in 15 minutes. (as that equates to over 1m of rainfall)
// It is simple, but seems to work....


#include <Wire.h>

uint8_t count = 0;
const int buttonPin = PB1;
int buttonState = 0;

void setup() {
  pinMode(buttonPin, INPUT_PULLUP);
  Wire.begin(8);                // join i2c bus with address #8
  Wire.onRequest(requestEvent); // register event
}

void loop() {
  buttonState = digitalRead(buttonPin);
  if (buttonState == LOW){
    count = count +1;
    delay(1000);
    }
   delay(100);
}

// function that executes whenever data is requested by master
// this function is registered as an event, see setup()
void requestEvent() {
  Wire.write("ok");
  Wire.write(count);// respond with message of 6 bytes
  count = 0;
  // as expected by master
}
