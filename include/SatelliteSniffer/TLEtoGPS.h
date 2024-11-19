#pragma once
#include <GPS.h>
#include <TLE.h>
#include <filesystem>

static const std::filesystem::path workingDirectory = std::filesystem::current_path().parent_path();

namespace TLEtoGPS {
    TLE readTLEData(const std::string &filename);

    GPS convertTLEToGPS(const std::string &filename);

    GPS convertTLEToGPSAtTimeWindow(const std::string &filename, const int &millisecs = 0);
}
