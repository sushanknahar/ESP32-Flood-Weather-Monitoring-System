#pragma once

#include <Arduino.h>
#include "SensorData.h"

enum FloodAlertReason : uint8_t {
  ALERT_NONE = 0,
  ALERT_WATER_LEVEL = 1 << 0,
  ALERT_FLOW_RATE = 1 << 1
};

struct FloodAlertResult {
  bool active = false;
  uint8_t reasons = ALERT_NONE;
};

FloodAlertResult evaluateFloodRisk(const SensorData &data);
void setFloodAlertOutput(bool active);

