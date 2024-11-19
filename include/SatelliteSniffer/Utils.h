#pragma once
#include <GPS.h>
#include <chrono>

inline const auto current = std::chrono::system_clock::now();

namespace Utils {
    std::string getTimeString(const int &milliseconds = 0);

    void printLine(const std::string &message);

    void printGPS(const GPS &gps);

    tm *getLocalTime(const int &milliseconds = 0);
}
