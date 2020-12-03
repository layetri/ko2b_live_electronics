#include <Arduino.h>

const int mic_pin = 16;
const int light_pin = 18;
const int thres = 370;
const int delay_time = 200;

int result = 0;
int counter = 0;
int countdown = 500;
int pulse_count = 0;
int silence_count = 0;

bool light_status = false;
bool counting_down = false;
bool is_tone = false;

void resetCountdown() {
  counting_down = false;
  countdown = 500;
  pulse_count = 0;
}

void setup() {
  Serial.begin(9600);
  pinMode(OUTPUT, light_pin);
}

void loop() {
  // Increment the counter
  counter++;

  // Decrement the countdown
  if(counting_down) {
    countdown--;
  }
  
  if(counter > delay_time) {
    // Read the result
    result = analogRead(mic_pin);
    
    if(result < thres) {
      if(is_tone == false) {
        Serial.print(counter);
        Serial.print(": ");
        Serial.println(result);
    
        if(light_status) {
          if(pulse_count < 2) {
            counting_down = true;
            pulse_count++;
          } else {
            digitalWrite(light_pin, LOW);
            light_status = false;
            resetCountdown();
          }
  
          if(countdown <= 0) {
            resetCountdown();
          }
        } else {
          digitalWrite(light_pin, HIGH);
          light_status = true;
        }
        
        counter = 0;
        is_tone = true;
      }
    } else {
      silence_count++;

      if(silence_count > 200 && result > thres + 200) {
        is_tone = false;
      }
    }
  }

  delay(1);
}
