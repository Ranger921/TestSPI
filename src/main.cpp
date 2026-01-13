#include <Arduino.h>
#include <Wire.h>
#include <Adafruit_BNO08x.h>
#include <math.h>

#define BNO_RST 3

Adafruit_BNO08x bno08x(BNO_RST);
sh2_SensorValue_t sensorValue;

void setup() {
  Serial.begin(115200);
  while (!Serial);

  // Allow IMU to fully boot
  delay(500);

  Wire.begin();
  Wire.setClock(100000);  // Safe I2C speed

  Serial.println("BNO085 Rotation Vector init...");

  if (!bno08x.begin_I2C(0x4B, &Wire)) {
    Serial.println("BNO085 not detected");
    while (1);
  }

  Serial.println("BNO085 detected");

  delay(200);

  // Enable rotation vector (50 Hz)
  bno08x.enableReport(SH2_ROTATION_VECTOR, 20000);
}

void loop() {
  if (bno08x.getSensorEvent(&sensorValue)) {

    if (sensorValue.sensorId == SH2_ROTATION_VECTOR) {

      // Quaternion components
      float qi = sensorValue.un.rotationVector.i;
      float qj = sensorValue.un.rotationVector.j;
      float qk = sensorValue.un.rotationVector.k;
      float qr = sensorValue.un.rotationVector.real;

      // Quaternion → Euler (Tait-Bryan angles)
      float roll  = atan2(2.0f * (qr * qi + qj * qk),
                          1.0f - 2.0f * (qi * qi + qj * qj));

      float pitch = asin(2.0f * (qr * qj - qk * qi));

      float yaw   = atan2(2.0f * (qr * qk + qi * qj),
                          1.0f - 2.0f * (qj * qj + qk * qk));

      // Convert to degrees
      roll  *= 180.0f / PI;
      pitch *= 180.0f / PI;
      yaw   *= 180.0f / PI;

      // Output as CSV
      Serial.print(roll, 2);
      Serial.print(",");
      Serial.print(pitch, 2);
      Serial.print(",");
      Serial.println(yaw, 2);
    }
  }
}
