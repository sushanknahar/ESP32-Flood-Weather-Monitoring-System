#include "FloodAlert.h"

#include "Config.h"

FloodAlertResult evaluateFloodRisk(const SensorData &data) {
  FloodAlertResult result;

  if (data.distanceValid && data.distanceCm < DISTANCE_FLOOD_LEVEL_CM) {
    result.reasons |= ALERT_WATER_LEVEL;
  }

  if (data.flowRateLpm > FLOW_OVERFLOW_THRESHOLD_LPM) {
    result.reasons |= ALERT_FLOW_RATE;
  }

  result.active = result.reasons != ALERT_NONE;
  return result;
}

void setFloodAlertOutput(bool active) {
  digitalWrite(BUZZER_PIN, active ? HIGH : LOW);
}

