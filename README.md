# Air-Quality-Clock

The Bosch sensor BME680 is used.<br>
An LCD12864 is used as display.<br>

Functions of Air-Quality-Clock:<br>

- Display of the time in large letters
- Display of temperature, humidity and air pressure
- Display of air quality (IAQ, CO2 and VOC)
- Control of the display background depending on the brightness
- Update the software via OTA

Software is developed on Arduino IDE.<br>

- Install bsec2 library from Bosch Sensotec
- Install u8g2lib library
- Change your wifi settings in file wlan.ino
- Change timezone and ntp server in wlan.ino
- Select XIAO_ESP32C3 as board
- On first time, transfer software over USB port

## Schematic:

![image info](images/schematic.jpg)

## Displayed data:

![image info](images/temp_hum.jpg)

![image info](images/pressure.jpg)

![image info](images/iaq.jpg)

![image info](images/co2.jpg)

![image info](images/voc.jpg)



