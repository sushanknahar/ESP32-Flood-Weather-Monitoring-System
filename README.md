# ESP32 Flood and Weather Monitoring System

An embedded IoT firmware project that monitors water flow, rain level, water height, temperature, humidity, and air pressure using an ESP32. The system logs sensor readings to an SD card and activates a buzzer when flood-risk conditions are detected.

This repository is designed as a portfolio-ready embedded systems project. It demonstrates sensor interfacing, interrupt handling, SPI/I2C communication, analog and digital GPIO, SD card logging, and modular Arduino C++ firmware design.

## Features

- ESP32-based real-time environmental monitoring
- Flow sensor pulse counting using hardware interrupts
- Ultrasonic water-level measurement
- Rain sensor analog input
- DHT11 temperature and humidity readings
- BMP180 pressure and temperature readings over I2C
- SD card CSV logging over SPI
- Buzzer alert for flood-risk conditions
- Modular firmware split into sensor, logger, and alert modules
- Graceful handling when DHT, BMP180, ultrasonic, or SD readings fail

## Hardware Used

| Component | Purpose |
| --- | --- |
| ESP32 development board | Main controller |
| Water flow sensor | Measures water flow rate |
| Rain sensor module | Detects rainfall intensity |
| HC-SR04 ultrasonic sensor | Measures water level distance |
| DHT11 sensor | Measures temperature and humidity |
| BMP180 sensor | Measures pressure and temperature |
| MicroSD card module | Stores CSV data logs |
| Buzzer | Flood alert output |

## Pin Connections

| ESP32 Pin | Connected To |
| --- | --- |
| GPIO 4 | Flow sensor signal |
| GPIO 32 | Rain sensor analog output |
| GPIO 23 | Ultrasonic trigger |
| GPIO 2 | Ultrasonic echo |
| GPIO 14 | DHT11 data |
| GPIO 27 | Buzzer |
| GPIO 5 | SD card CS |
| GPIO 13 | SD card MOSI |
| GPIO 19 | SD card MISO |
| GPIO 18 | SD card SCK |
| GPIO 21 | BMP180 SDA, default ESP32 I2C |
| GPIO 22 | BMP180 SCL, default ESP32 I2C |

## Firmware Structure

```text
ESP32-Flood-Weather-Monitoring-System/
|-- README.md
|-- LICENSE
|-- .gitignore
|-- firmware/
|   `-- FloodGuardMonitor/
|       |-- FloodGuardMonitor.ino
|       |-- Config.h
|       |-- SensorData.h
|       |-- Sensors.h
|       |-- Sensors.cpp
|       |-- SDLogger.h
|       |-- SDLogger.cpp
|       |-- FloodAlert.h
|       `-- FloodAlert.cpp
|-- docs/
|   |-- Flowchart.md
|   |-- GitHub-Upload-Guide.md
|   |-- Pinout.md
|   `-- Resume-Bullets.md
`-- images/
    `-- .gitkeep
```

## Required Arduino Libraries

Install these libraries from the Arduino IDE Library Manager:

- Adafruit Unified Sensor
- Adafruit BMP085 Unified
- DHT sensor library

The ESP32 board package must also be installed in Arduino IDE.

## How To Run

1. Open `firmware/FloodGuardMonitor/FloodGuardMonitor.ino` in Arduino IDE.
2. Select your ESP32 board from `Tools > Board`.
3. Install the required libraries listed above.
4. Connect the sensors using the pin table.
5. Insert a formatted microSD card into the SD module.
6. Upload the sketch.
7. Open Serial Monitor at `115200` baud.

## Hardware Safety Notes

- Many HC-SR04 modules output a 5 V echo signal. Use a voltage divider or level shifter before connecting echo to the ESP32.
- Use a common ground between the ESP32, sensors, buzzer, and SD card module.
- Confirm that the SD card module is ESP32-compatible and supports 3.3 V logic.
- Keep water sensors electrically isolated from exposed high-current wiring.

The firmware creates `/data.csv` on the SD card and appends readings in this format:

```csv
TimestampMs,FlowRateLpm,RainRaw,DistanceCm,DhtTemperatureC,HumidityPercent,BmpTemperatureC,PressureHpa,FloodAlert
```

## Flood Alert Logic

The buzzer turns on when either condition is true:

- Water-level distance is below `30 cm`
- Flow rate is above `50 L/min`

You can adjust these values in `firmware/FloodGuardMonitor/Config.h`.

## Calibration Notes

The default flow sensor calibration value is:

```cpp
FLOW_SENSOR_HZ_PER_LPM = 7.5
```

This is common for YF-S201-style sensors, but you should verify it with your sensor datasheet or by measuring known water volume over time.

## Images To Add Before Publishing

Add these files to the `images/` folder before sharing the repository:

- `setup.jpg` - full working hardware setup
- `wiring.jpg` - close-up wiring view
- `serial-monitor.png` - Serial Monitor output
- `sd-card-log.png` - sample CSV data
- `circuit-diagram.png` - Fritzing, KiCad, or EasyEDA diagram

Projects with real build photos look much stronger to recruiters than code-only repositories.

## Future Improvements

- Add LCD or OLED display for local readings
- Add Wi-Fi dashboard using MQTT or HTTP
- Upload readings to Firebase, ThingsBoard, or AWS IoT
- Add non-blocking ultrasonic reads
- Store configuration values in EEPROM or SPIFFS
- Add unit-tested logic for flood alert decisions
- Add enclosure design and field test results


