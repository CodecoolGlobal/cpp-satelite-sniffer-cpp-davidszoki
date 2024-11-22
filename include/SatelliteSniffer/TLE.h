#pragma once
#include <string>

struct TLE {
    TLE(const std::string &tle_name, const std::string &tle_line1, const std::string &tle_line2);

    ~TLE() = default;

    std::string name, line1, line2;
};
