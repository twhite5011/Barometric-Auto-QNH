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
*/

#ifndef BaroAutoQNH_h
#define BaroAutoQNH_h

#include <Arduino.h>

class BaroAutoQNH {
  public:
    // Constructor: Initialize station elevation and optional pressure offset
    BaroAutoQNH(float stationElevation, float pressureOffset = 0.0);

    // Function to calculate QNH (Altimeter Setting) only once
    void calculateQNH(float pressureMillibars);

    // Function to retrieve the static QNH value
    float getQNH();

    // Function to dynamically update the station elevation
    void setStationElevation(float stationElevation);

    // Function to set the pressure offset
    void setPressureOffset(float offset);

  private:
    float stationElevationMeters; // Station elevation in meters
    float qnh;                    // Stored QNH value
    float pressureOffset;         // User-defined pressure offset
    bool qnhCalculated;           // Flag to ensure QNH is calculated only once
};

#endif




