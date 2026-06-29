#include "Config.h"
#include "FloodAlert.h"
#include "SDLogger.h"
#include "SensorData.h"
#include "Sensors.h"
#include <math.h>

SDLogger logger;
uint32_t previousMeasurementMs = 0;

void printReading(const SensorData &data, const FloodAlertResult &alert);
void printFloatOrNA(float value, uint8_t digits = 2);
void printAlertReasons(const FloodAlertResult &alert);

void setup() {
  Serial.begin(SERIAL_BAUD_RATE);
  delay(500);

  Serial.println();
  Serial.println("ESP32 Flood and Weather Monitoring System");
  Serial.println("Initializing sensors...");

  beginSensors();
  logger.begin();

  previousMeasurementMs = millis();
  Serial.println("System ready.");
}

void loop() {
  const uint32_t currentMs = millis();
  if (currentMs - previousMeasurementMs < MEASUREMENT_INTERVAL_MS) {
    return;
  }

  const uint32_t elapsedMs = currentMs - previousMeasurementMs;
  previousMeasurementMs = currentMs;

  SensorData data = readSensors(elapsedMs);
  const FloodAlertResult alert = evaluateFloodRisk(data);
  data.floodAlert = alert.active;

  setFloodAlertOutput(alert.active);
  printReading(data, alert);
  logger.log(data);
}

void printReading(const SensorData &data, const FloodAlertResult &alert) {
  Serial.print("Flow: ");
  printFloatOrNA(data.flowRateLpm);
  Serial.print(" L/min | Rain: ");
  Serial.print(data.rainRaw);
  Serial.print(" | Distance: ");
  printFloatOrNA(data.distanceCm);
  Serial.print(" cm | DHT Temp: ");
  printFloatOrNA(data.dhtTemperatureC);
  Serial.print(" deg C | Humidity: ");
  printFloatOrNA(data.humidityPercent);
  Serial.print(" % | BMP Temp: ");
  printFloatOrNA(data.bmpTemperatureC);
  Serial.print(" deg C | Pressure: ");
  printFloatOrNA(data.pressureHpa);
  Serial.print(" hPa | Alert: ");
  printAlertReasons(alert);
  Serial.println();
}

void printFloatOrNA(float value, uint8_t digits) {
  if (isnan(value)) {
    Serial.print("NA");
    return;
  }

  Serial.print(value, digits);
}

void printAlertReasons(const FloodAlertResult &alert) {
  if (!alert.active) {
    Serial.print("OK");
    return;
  }

  if (alert.reasons & ALERT_WATER_LEVEL) {
    Serial.print("WATER_LEVEL ");
  }

  if (alert.reasons & ALERT_FLOW_RATE) {
    Serial.print("FLOW_RATE ");
  }
}
