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


#include "BaroAutoQNH.h"

// Constructor: Initialize station elevation and optional pressure offset
BaroAutoQNH::BaroAutoQNH(float stationElevation, float offset) {
    stationElevationMeters = stationElevation;
    pressureOffset = offset;
    qnh = 0.0;               // Initialize QNH to 0
    qnhCalculated = false;   // QNH has not been calculated yet
}

// Function to calculate QNH (only once, with valid pressure)
void BaroAutoQNH::calculateQNH(float pressureMillibars) {
    if (qnhCalculated) {
        return; // Do nothing if QNH is already calculated
    }

    // Ignore invalid or zero pressure readings
    if (pressureMillibars <= 0) {
        return; // Wait for the first valid pressure reading
    }

    const float standardPressure = 1013.25; // Standard sea-level pressure in mb
    const float lapseRate = 0.0065;         // Temperature lapse rate in K/m
    const float seaLevelTemp = 288.15;      // Standard temperature at sea level in K
    const float exponent = 0.190284;        // Gravitational constant/R specific

    // Apply the user-defined offset to the pressure reading
    float adjustedPressure = pressureMillibars + pressureOffset - 0.3;

    // Calculate QNH using the provided formula
    qnh = adjustedPressure * pow(1 + (pow(1013.25, 0.190284) * 0.0065 / 288.0) * (stationElevationMeters / pow(adjustedPressure, 0.190284)), 1 / 0.190284);

    // Mark QNH as calculated
    qnhCalculated = true;
}

// Function to retrieve the static QNH value
float BaroAutoQNH::getQNH() {
    return qnh;
}

// Function to dynamically update the station elevation
void BaroAutoQNH::setStationElevation(float stationElevation) {
    stationElevationMeters = stationElevation;
}

// Function to set the pressure offset
void BaroAutoQNH::setPressureOffset(float offset) {
    pressureOffset = offset;
}
