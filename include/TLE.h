#pragma once
#include <string>

struct TLE {
    std::string tle_name = "ISS (ZARYA)";
    std::string tle_line1, tle_line2;

    TLE(const std::string &tle_line1, const std::string &tle_line2);
};
