#include <Arduino.h>
#include <SPI.h>
#include <Adafruit_BNO08x.h>
#include <Adafruit_BusIO_Register.h>
#include <Adafruit_Sensor.h>
#include "hardware-configs/pins.h"

Adafruit_BNO08x bno(BNO_RST);
sh2_SensorValue sensorValue;

void setup() {
  // put your setup code here, to run once:
  Serial.begin(115200);
  while (!Serial) delay(5);

  Serial.println("Starting BNO08x SPI...");

  if (!bno.begin_SPI(BNO_CS, BNO_INT)) {
    Serial.println("Failed to find BNO08x chip");
    while (1);
  }

  Serial.println("BNO08x found!");

  bno.enableReport(SH2_ACCELEROMETER, 10000);
}

void loop() {
  if (bno.getSensorEvent(&sensorValue)) {
    if (sensorValue.sensorId == SH2_ACCELEROMETER) {
      Serial.print("{"); // Start marker

      Serial.print(sensorValue.un.accelerometer.x);
      Serial.print(",");
      Serial.print(sensorValue.un.accelerometer.y);
      Serial.print(",");
      Serial.print(sensorValue.un.accelerometer.z);
      Serial.println("}"); // End marker
    }
  }

  delay(50);
}