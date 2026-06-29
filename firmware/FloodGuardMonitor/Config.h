#pragma once

#include <Arduino.h>

static constexpr uint32_t SERIAL_BAUD_RATE = 115200;
static constexpr uint16_t SENSOR_STARTUP_DELAY_MS = 2000;
static constexpr uint32_t MEASUREMENT_INTERVAL_MS = 1000;

// Sensor pins
static constexpr uint8_t FLOW_SENSOR_PIN = 4;
static constexpr uint8_t RAIN_SENSOR_PIN = 32;
static constexpr uint8_t ULTRASONIC_TRIG_PIN = 23;
static constexpr uint8_t ULTRASONIC_ECHO_PIN = 2;
static constexpr uint8_t DHT_PIN = 14;
static constexpr uint8_t BUZZER_PIN = 27;

// SD card SPI pins
static constexpr uint8_t SD_CS_PIN = 5;
static constexpr uint8_t SD_MOSI_PIN = 13;
static constexpr uint8_t SD_MISO_PIN = 19;
static constexpr uint8_t SD_SCK_PIN = 18;

// Calibration and thresholds
static constexpr float FLOW_SENSOR_HZ_PER_LPM = 7.5f;
static constexpr float SOUND_SPEED_CM_PER_US = 0.0343f;
static constexpr uint32_t ULTRASONIC_TIMEOUT_US = 50000;
static constexpr float DISTANCE_FLOOD_LEVEL_CM = 30.0f;
static constexpr float FLOW_OVERFLOW_THRESHOLD_LPM = 50.0f;

static constexpr char LOG_FILE_PATH[] = "/data.csv";

