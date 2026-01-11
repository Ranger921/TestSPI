#include <Arduino.h>
#include "hardware-configs/pins.h"

void setup() {
  // put your setup code here, to run once:
  Serial.begin(115200);
}

void loop() {
  Serial.print("{"); // Start marker

  float joy_x = analogRead(JOY_X_PIN) / 512.0 - 1;
  float joy_y = analogRead(JOY_Y_PIN) / 512.0 - 1;

  Serial.print(joy_x);
  Serial.print(",");
  Serial.print(joy_y);
  Serial.println("}"); // End marker

  delay(100);
}