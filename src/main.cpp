#include <Arduino.h>
#include "hardware-configs/pins.h"

void setup() {
  // put your setup code here, to run once:
  Serial.begin(115200);
}

void loop() {
  Serial.print("{"); // Start marker

  float joy_x = 1023 - analogRead(JOY_X_PIN);
  float joy_y = analogRead(JOY_Y_PIN);

  Serial.print(joy_x);
  Serial.print(",");
  Serial.print(joy_y);
  Serial.println("}"); // End marker

  delay(50);
}