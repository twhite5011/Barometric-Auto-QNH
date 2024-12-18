# Barometric-Auto-QNH
Developed by HELIOS Rockets R&D, BaroAutoQNH is a lightweight Arduino library for calculating the QNH (altimeter setting) based on barometric pressure and station elevation. This library is ideal for aviation / aerospace projects, allowing you to accurately set the altimeter for takeoff based on your local pressure readings.

# BaroAutoQNH Function Description:
```C++
BaroAutoQNH qnhCalculator();
```
Use this to define the station's altitude. This value corresponds to the elevation of the runway, helipad, or any location from which your flight requiring an altimeter begins. This function is called during the initialization at the beginning of the code.

```C++
qnhCalculator.setPressureOffset();
```
Use this to set a measurement offset for the current pressure reading. This value might be obtained from the sensor's datasheet or determined through calibration and testing.

```C++
qnhCalculator.calculateQNH();
```
Inputs the sensor's initial pressure reading, which corresponds to the station's barometric pressure. This function calculates the QNH based on the station elevation and pressure.

```C++
qnhCalculator.getQNH();
```
Outputs the calculated QNH. Use this to retrieve the QNH value for your application.

# Installation
1. Download or clone this repository.
2. Copy the BaroAutoQNH folder into your Arduino libraries directory (Windows: Documents/Arduino/libraries) or (macOS/Linux: ~/Arduino/libraries)
3. Restart your Arduino IDE to ensure the library is recognized.

# References
www.weather.gov/media/epz/wxcalc/altimeterSetting.pdf
