#pragma once

#include <Arduino.h>
#include "SensorData.h"

class SDLogger {
 public:
  bool begin();
  bool log(const SensorData &data);
  bool isReady() const;

 private:
  bool ready_ = false;
  bool writeHeaderIfNeeded();
};

