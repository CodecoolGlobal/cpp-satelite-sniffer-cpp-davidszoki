#pragma once
#include <string>
#include <TLE.h>
#include <GPS.h>

class Satellite {
public:
    explicit Satellite(const std::string &filename);

    ~Satellite() = default;

    TLE getTLE() { return tle; }
    std::pair<float, float> getXY() { return xy; }

    GPS convertTLEToGPSAtTimeWindow(const TLE &tle, const int &milliseconds) const;

    std::pair<float, float> convertGPStoPixels(const GPS &gps, const int &windowWidth, const int &windowHeight);

    void calculatePosition(Satellite &satellite, const int &windowWidth, const int &windowHeight,
                           const int &updateTime);

private:
    TLE tle;
    std::pair<float, float> xy;
};
