#include <Arduino.h>
#include <Adafruit_LSM6DS3.h>
#include "config.h"


Adafruit_LSM6DS3 imu;
void setup()
{
  // put your setup code here, to run once:

  // Start the serial communication at 115200 baud rate
  Serial.begin(115200);

  pinMode(LED1_PIN, OUTPUT);

  Wire.setPins(IMU_SDA_PIN, IMU_SCL_PIN);
  if (!imu.begin_I2C())
  {
    Serial.println("Failed to initialize IMU");
    // Blink the LED to indicate failure
    while (1)
    {
      digitalWrite(LED1_PIN, HIGH);
      delay(500);
      digitalWrite(LED1_PIN, LOW);
      delay(500);
    }
  }

  Serial.println("IMU initialized successfully");

  // Set the output data rate and range for the accelerometer and gyroscope
  imu.setAccelDataRate(LSM6DS_RATE_52_HZ);
  imu.setGyroDataRate(LSM6DS_RATE_52_HZ);
  imu.setAccelRange(LSM6DS_ACCEL_RANGE_4_G);
  imu.setGyroRange(LSM6DS_GYRO_RANGE_2000_DPS);
}

void loop()
{
  sensors_event_t accel, gyro, temp;
  imu.getEvent(&accel, &gyro, &temp);

  // Print accelerometer in m/s^2
  Serial.print("Accel: ");
  Serial.print(accel.acceleration.x);
  Serial.print(", ");
  Serial.print(accel.acceleration.y);
  Serial.print(", ");
  Serial.println(accel.acceleration.z);

  // Print gyroscope in rad/s
  Serial.print("Gyro: ");
  Serial.print(gyro.gyro.x);
  Serial.print(", ");
  Serial.print(gyro.gyro.y);
  Serial.print(", ");
  Serial.println(gyro.gyro.z);

  // Print temperature in Celsius
  Serial.print("Temp: ");
  Serial.print(temp.temperature);
  Serial.println();

  delay(200);
}
