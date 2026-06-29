#include "SDLogger.h"

#include <SD.h>
#include <SPI.h>
#include <math.h>

#include "Config.h"

namespace {
SPIClass sdSpi(VSPI);

void printCsvFloat(File &file, float value, uint8_t digits = 2) {
  if (isnan(value)) {
    file.print("NA");
    return;
  }

  file.print(value, digits);
}
}  // namespace

bool SDLogger::begin() {
  sdSpi.begin(SD_SCK_PIN, SD_MISO_PIN, SD_MOSI_PIN, SD_CS_PIN);

  ready_ = SD.begin(SD_CS_PIN, sdSpi);
  if (!ready_) {
    Serial.println("Warning: SD card initialization failed. Logging disabled.");
    return false;
  }

  if (!writeHeaderIfNeeded()) {
    ready_ = false;
    return false;
  }

  Serial.println("SD card initialized.");
  return true;
}

bool SDLogger::isReady() const {
  return ready_;
}

bool SDLogger::writeHeaderIfNeeded() {
  File dataFile = SD.open(LOG_FILE_PATH, FILE_APPEND);
  if (!dataFile) {
    Serial.println("Warning: Could not open CSV log file.");
    return false;
  }

  if (dataFile.size() == 0) {
    dataFile.println("TimestampMs,FlowRateLpm,RainRaw,DistanceCm,DhtTemperatureC,HumidityPercent,BmpTemperatureC,PressureHpa,FloodAlert");
  }

  dataFile.close();
  return true;
}

bool SDLogger::log(const SensorData &data) {
  if (!ready_) {
    return false;
  }

  File dataFile = SD.open(LOG_FILE_PATH, FILE_APPEND);
  if (!dataFile) {
    Serial.println("Warning: Failed to open CSV log file.");
    return false;
  }

  dataFile.print(data.timestampMs);
  dataFile.print(',');
  printCsvFloat(dataFile, data.flowRateLpm);
  dataFile.print(',');
  dataFile.print(data.rainRaw);
  dataFile.print(',');
  printCsvFloat(dataFile, data.distanceCm);
  dataFile.print(',');
  printCsvFloat(dataFile, data.dhtTemperatureC);
  dataFile.print(',');
  printCsvFloat(dataFile, data.humidityPercent);
  dataFile.print(',');
  printCsvFloat(dataFile, data.bmpTemperatureC);
  dataFile.print(',');
  printCsvFloat(dataFile, data.pressureHpa);
  dataFile.print(',');
  dataFile.println(data.floodAlert ? 1 : 0);

  dataFile.close();
  return true;
}

