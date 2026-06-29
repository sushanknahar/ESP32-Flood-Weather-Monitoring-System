#pragma once

#include <Arduino.h>
#include "SensorData.h"

void beginSensors();
SensorData readSensors(uint32_t elapsedMs);

