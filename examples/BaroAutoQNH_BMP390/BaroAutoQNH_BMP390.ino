/*
BaroAutoQNH.h

Original Authors: 
Daniel Betancourt, Liliana Castro, Tomas White
2024-11-20
Helios Rockets R & D - Universidad Pontificia Bolivariana
Aeronautical & Mechanical Engineering 

The main formula utilized was obtained from: www.weather.gov/media/epz/wxcalc/altimeterSetting.pdf

Permission is hereby granted, free of charge, to any person obtaining a copy of this software 
and associated documentation files (the "Software"), to deal in the Software without restriction, 
including without limitation the rights to use, copy, modify, merge, publish, distribute, sublicense, 
and/or sell copies of the Software, and to permit persons to whom the Software is furnished to do so, 
subject to the following conditions:

The above copyright notice and this permission notice shall be included in all copies or 
substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR IMPLIED, INCLUDING 
BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND 
NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, 
DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, 
OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.

---------------------------------------------------------------------------------------------
The following example uses a regular barometer, in this case the Adafruit BMP390, 
and provides the required sea level altitude measurement (barometric adjustment or QNH) 
*/

#include <Wire.h>
#include <BaroAutoQNH.h>
#include "Adafruit_BMP3XX.h" // Replace with your sensor library, e.g., Adafruit_BMP280, Adafruit_BMP3XX

Adafruit_BMP3XX bmp; // Example sensor object
BaroAutoQNH qnhCalculator(500); // Station elevation = 500m, default offset = 0.0

void setup() {
  // Initialize the BMP390 sensor
  Serial.begin(115200);
  bmp.begin_I2C(0X77, &Wire); //Change accordingly to I2C pin selection.
  bmp.setTemperatureOversampling(BMP3_OVERSAMPLING_8X);
  bmp.setPressureOversampling(BMP3_OVERSAMPLING_4X);
  bmp.setIIRFilterCoeff(BMP3_IIR_FILTER_COEFF_3);
  bmp.setOutputDataRate(BMP3_ODR_50_HZ);
  Serial.println("Setup done");

  // Set a custom pressure offset (optional)
  qnhCalculator.setPressureOffset(0.0);

  // Read pressure and calculate QNH (only once)
  float pressure = bmp.readPressure() / 100.0; // Convert to millibars
  qnhCalculator.calculateQNH(pressure);

  // Print the static QNH value
  Serial.print("Static QNH: ");
  Serial.print(qnhCalculator.getQNH());
  Serial.println(" hPa");
}

void loop() {
  // Read current pressure
  float pressure = bmp.readPressure() / 100.0; // Convert to hPa
  
  // Retrieve the static QNH value
  float qnh = qnhCalculator.getQNH();

  // Calculate altitude based on current pressure and QNH (optional)
  float altitude = bmp.readAltitude(qnh); // Assumes your sensor library supports altitude calculation

  // Print the values
  Serial.print("Pressure: ");
  Serial.print(pressure);
  Serial.print(" hPa, QNH: ");
  Serial.print(qnh);
  Serial.print(" hPa");
  
  Serial.print(" Altitude: ");
  Serial.print(altitude);
  Serial.println(" meters");

  delay(1000);
}

