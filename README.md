# I2C Scanner for M5Cardputer

It scans the I2C bus for connected devices and displays their addresses on the built-in screen. The addresses are shown in hexadecimal format.


## Hardware Requirements

- M5Cardputer
- I2C device to scan on the grove connector


## Usage

- The M5 Card Computer will start scanning the I2C bus upon startup.
- Detected I2C device addresses will be displayed on the screen in hexadecimal format with the prefix 0x.
- If no I2C devices are found, the message "No I2C devices" will be displayed.
The scan will repeat every 8 seconds.

