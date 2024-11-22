#pragma once
#include <GPS.h>
#include <chrono>
#include <string>
#include <vector>
#include <Satellite.h>

inline const auto current = std::chrono::system_clock::now();

namespace Utils {
    std::string getTimeString(const int &milliseconds = 0);

    void printLine(const std::string &message);

    void printGPS(const GPS &gps);

    tm *getLocalTime(const int &milliseconds = 0);

    void fillSatellitesBySourceFile(const std::string &filename, std::vector<Satellite> &satellites);
}
