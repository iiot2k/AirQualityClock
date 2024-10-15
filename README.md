# Air-Quality-Clock

Displays clock and air quality data from BME680 sensor on LCD.<br>
An cheap LCD12864 is used as display.<br>

Functions of Air-Quality-Clock:<br>

- Display of the time in large letters
- Display of temperature, humidity and air pressure
- Display of air quality Indoor Air Quality and level index (IAQ)
- Display of air quality Carbon Dioxide in ppm (CO2) 
- Display of air quality Volatile Organic Compounds (VOC)
- Control of the display background depending on the brightness
- Update the software via OTA

Software is developed on Arduino IDE.<br>

- Install bsec2 library from Bosch Sensotec
- Install u8g2lib library
- Change your wifi settings in file wlan.ino
- Change timezone and ntp server in file wlan.ino
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



