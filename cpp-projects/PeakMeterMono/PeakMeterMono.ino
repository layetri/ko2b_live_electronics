/* Mono Peak Meter

   Scrolling peak audio level meter in the Arduino Serial Monitor

   Audio input needs to connect to pin 16 (A2).  The signal range is 0 to 1.2V.
   See the documentation in the Audio System Design Tool for the recommended
   circuit to connect an analog signal.

   This example code is in the public domain
*/

#include <Audio.h>
#include <Wire.h>
#include <SPI.h>
#include <SD.h>
#include <SerialFlash.h>

const int mic_pin = 16;
const int light_pin = 18;
const int thres = 400;
const int delay_time = 100;

int result = 0;
int counter = 0;
bool light_status = false;
bool is_tone = false;

void setup() {
  Serial.begin(9600);
  pinMode(OUTPUT, light_pin);
}

void loop() {
  result = analogRead(mic_pin);
  counter++;
  if(counter > delay_time) {
    if(result < thres) {
      Serial.print("PEAK! ");
      Serial.println(result);
  
      if(!is_tone) {
        if(light_status) {
          digitalWrite(light_pin, LOW);
        } else {
          digitalWrite(light_pin, HIGH);
        }
      }
  
      light_status = !light_status;
      is_tone = true;
      counter = 0;
    } else {
      is_tone = false;
    }
  }
}
