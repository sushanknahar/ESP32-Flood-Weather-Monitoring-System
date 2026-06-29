# Pinout

| ESP32 Pin | Module Pin | Notes |
| --- | --- | --- |
| GPIO 4 | Flow sensor signal | Uses interrupt on falling edge |
| GPIO 32 | Rain sensor analog output | ADC input |
| GPIO 23 | HC-SR04 trigger | Digital output |
| GPIO 2 | HC-SR04 echo | Digital input |
| GPIO 14 | DHT11 data | Digital single-wire data |
| GPIO 27 | Buzzer positive | Digital output |
| GPIO 5 | MicroSD CS | SPI chip select |
| GPIO 13 | MicroSD MOSI | SPI data out |
| GPIO 19 | MicroSD MISO | SPI data in |
| GPIO 18 | MicroSD SCK | SPI clock |
| GPIO 21 | BMP180 SDA | Default ESP32 I2C data |
| GPIO 22 | BMP180 SCL | Default ESP32 I2C clock |

Use common ground between the ESP32 and all sensor modules.

