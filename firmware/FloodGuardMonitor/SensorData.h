#pragma once

#include <Arduino.h>
#include <math.h>

struct SensorData {
  uint32_t timestampMs = 0;

  float flowRateLpm = 0.0f;
  int rainRaw = 0;

  float distanceCm = NAN;
  bool distanceValid = false;

  float dhtTemperatureC = NAN;
  float humidityPercent = NAN;
  bool dhtValid = false;

  float bmpTemperatureC = NAN;
  float pressureHpa = NAN;
  bool bmpValid = false;

  bool floodAlert = false;
};
