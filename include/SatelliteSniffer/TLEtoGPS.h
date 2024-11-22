#pragma once
#include <GPS.h>
#include <TLE.h>

namespace TLEtoGPS {
    TLE readTLEData(const std::string &filename);

    GPS convertTLEToGPS(const std::string &filename);

    GPS convertTLEToGPSAtTimeWindow(const TLE &tle, const int &millisecs = 0);
}
