#include "Sensors.h"

#include <Adafruit_BMP085_U.h>
#include <Adafruit_Sensor.h>
#include <DHT.h>
#include <Wire.h>
#include <math.h>

#include "Config.h"

namespace {
DHT dht(DHT_PIN, DHT11);
Adafruit_BMP085_Unified bmp(10085);

volatile uint32_t flowPulseCount = 0;
bool bmpAvailable = false;

void IRAM_ATTR onFlowPulse() {
  flowPulseCount++;
}

uint32_t takeFlowPulseCount() {
  noInterrupts();
  const uint32_t pulses = flowPulseCount;
  flowPulseCount = 0;
  interrupts();
  return pulses;
}

float readFlowRateLpm(uint32_t elapsedMs) {
  if (elapsedMs == 0) {
    return 0.0f;
  }

  const uint32_t pulses = takeFlowPulseCount();
  const float elapsedSeconds = static_cast<float>(elapsedMs) / 1000.0f;
  const float pulseFrequencyHz = static_cast<float>(pulses) / elapsedSeconds;
  return pulseFrequencyHz / FLOW_SENSOR_HZ_PER_LPM;
}

float readDistanceCm() {
  digitalWrite(ULTRASONIC_TRIG_PIN, LOW);
  delayMicroseconds(2);
  digitalWrite(ULTRASONIC_TRIG_PIN, HIGH);
  delayMicroseconds(10);
  digitalWrite(ULTRASONIC_TRIG_PIN, LOW);

  const uint32_t durationUs = pulseIn(ULTRASONIC_ECHO_PIN, HIGH, ULTRASONIC_TIMEOUT_US);
  if (durationUs == 0) {
    return NAN;
  }

  return (static_cast<float>(durationUs) * SOUND_SPEED_CM_PER_US) / 2.0f;
}

void readDht(SensorData &data) {
  data.dhtTemperatureC = dht.readTemperature();
  data.humidityPercent = dht.readHumidity();
  data.dhtValid = !isnan(data.dhtTemperatureC) && !isnan(data.humidityPercent);

  if (!data.dhtValid) {
    Serial.println("Warning: DHT11 read failed.");
  }
}

void readBmp180(SensorData &data) {
  if (!bmpAvailable) {
    return;
  }

  sensors_event_t event;
  bmp.getEvent(&event);
  data.pressureHpa = event.pressure;
  data.bmpValid = data.pressureHpa > 0.0f;

  if (!data.bmpValid) {
    data.pressureHpa = NAN;
    Serial.println("Warning: BMP180 pressure read failed.");
  }

  bmp.getTemperature(&data.bmpTemperatureC);
  if (isnan(data.bmpTemperatureC)) {
    data.bmpTemperatureC = NAN;
    data.bmpValid = false;
    Serial.println("Warning: BMP180 temperature read failed.");
  }
}
}  // namespace

void beginSensors() {
  pinMode(FLOW_SENSOR_PIN, INPUT_PULLUP);
  attachInterrupt(digitalPinToInterrupt(FLOW_SENSOR_PIN), onFlowPulse, FALLING);

  pinMode(RAIN_SENSOR_PIN, INPUT);
  pinMode(ULTRASONIC_TRIG_PIN, OUTPUT);
  pinMode(ULTRASONIC_ECHO_PIN, INPUT);
  pinMode(BUZZER_PIN, OUTPUT);
  digitalWrite(ULTRASONIC_TRIG_PIN, LOW);
  digitalWrite(BUZZER_PIN, LOW);

  dht.begin();
  delay(SENSOR_STARTUP_DELAY_MS);

  bmpAvailable = bmp.begin();
  if (!bmpAvailable) {
    Serial.println("Warning: BMP180 not found. Pressure readings disabled.");
  }
}

SensorData readSensors(uint32_t elapsedMs) {
  SensorData data;
  data.timestampMs = millis();
  data.flowRateLpm = readFlowRateLpm(elapsedMs);
  data.rainRaw = analogRead(RAIN_SENSOR_PIN);

  data.distanceCm = readDistanceCm();
  data.distanceValid = !isnan(data.distanceCm);
  if (!data.distanceValid) {
    Serial.println("Warning: Ultrasonic distance read timed out.");
  }

  readDht(data);
  readBmp180(data);

  return data;
}
