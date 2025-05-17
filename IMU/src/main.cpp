#include <Arduino.h>
#include <Adafruit_LSM6DS3.h>
#include <MadgwickAHRS.h>

#include "LED.h"
#include "config.h"

// #define USE_TELEPLOT

constexpr uint8_t IMU_ADDRESS = 0x6B; // I2C address of the LSM6DS3 IMU
Adafruit_LSM6DS3 imu;
Madgwick filter;

void setup()
{
  // put your setup code here, to run once:

  // Start the serial communication at 115200 baud rate
  Serial.begin(115200);

  pinMode(CORE_LED_PIN, OUTPUT);

  Wire.setPins(IMU_SDA_PIN, IMU_SCL_PIN);
  if (!imu.begin_I2C(IMU_ADDRESS))
  {
    Serial.println("Failed to initialize IMU");
    // Blink the LED to indicate failure
    while (1)
    {
      digitalWrite(CORE_LED_PIN, HIGH);
      delay(500);
      digitalWrite(CORE_LED_PIN, LOW);
      delay(500);
    }
  }

  Serial.println("IMU initialized successfully");

  // Set the output data rate and range for the accelerometer and gyroscope
  imu.setAccelDataRate(LSM6DS_RATE_52_HZ);
  imu.setGyroDataRate(LSM6DS_RATE_52_HZ);
  imu.setAccelRange(LSM6DS_ACCEL_RANGE_4_G);
  imu.setGyroRange(LSM6DS_GYRO_RANGE_2000_DPS);

#ifdef USE_TELEPLOT
  // Initialize the Madgwick filter with a sample frequency of 50 Hz
  filter.begin(50);
#endif

  // Start the LED effect
  LED::begin();
}

#ifdef USE_TELEPLOT
String formatToTeleplot(const String name, const float angles[3])
{
  String result = ">3D|" + name + ":S:cube:R:" +
                  String(angles[0]) + ":" +
                  String(angles[1]) + ":" +
                  String(angles[2]);
  return result;
}

inline float radToDeg(float rad)
{
  return rad * (180.0 / M_PI);
}

#endif

TickType_t lastWakeTime = 0;

void loop()
{
  sensors_event_t accel, gyro, temp;
  imu.getEvent(&accel, &gyro, &temp);

#ifdef USE_TELEPLOT
  filter.updateIMU(radToDeg(gyro.gyro.x),
                   radToDeg(gyro.gyro.y),
                   radToDeg(gyro.gyro.z),
                   accel.acceleration.x,
                   accel.acceleration.y,
                   accel.acceleration.z);

  float angles[] = {filter.getRollRadians(),
                    filter.getPitchRadians(),
                    filter.getYawRadians()};

  auto cubeStr = formatToTeleplot("My Fucking Cube", angles);
  Serial.println(cubeStr);
  xTaskDelayUntil(&lastWakeTime, 20);
#else
  // Print accelerometer in m/s^2
  Serial.print("Accel: ");
  Serial.print(accel.acceleration.x);
  Serial.print(",\t");
  Serial.print(accel.acceleration.y);
  Serial.print(",\t");
  Serial.print(accel.acceleration.z);

  // Print gyroscope in rad/s
  Serial.print(";\tGyro: ");
  Serial.print(gyro.gyro.x);
  Serial.print(",\t");
  Serial.print(gyro.gyro.y);
  Serial.print(",\t");
  Serial.print(gyro.gyro.z);

  // Print temperature in Celsius
  Serial.print(";\tTemp: ");
  Serial.println(temp.temperature);
  xTaskDelayUntil(&lastWakeTime, 100);
#endif
}
