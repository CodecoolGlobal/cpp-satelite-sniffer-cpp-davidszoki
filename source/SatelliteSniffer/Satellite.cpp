#include <PythonScriptExecutor.h>
#include <Satellite.h>
#include <Utils.h>

using namespace std;

Satellite::Satellite(const string &filename): tle(Utils::readTLEData(filename)) {
}

GPS Satellite::convertTLEToGPSAtTimeWindow(const TLE &tle, const int &milliseconds) const {
    const auto timeString = Utils::getTimeString(milliseconds);
    return PythonScriptExecutor::executeGetSatelliteGPSPAtTimeWindowPythonScript(tle, timeString);
}

void Satellite::calculatePosition(Satellite &satellite, const int &windowWidth, const int &windowHeight,
                                  const int &updateTime) {
    const auto tle = satellite.getTLE();
    const auto gps = satellite.convertTLEToGPSAtTimeWindow(tle, updateTime);
    satellite.xy = convertGPStoPixels(gps, windowWidth, windowHeight);
}

pair<float, float> Satellite::convertGPStoPixels(const GPS &gps, const int &windowWidth, const int &windowHeight) {
    pair<float, float> xy = {0, 0};
    const auto radius = windowWidth / (2 * M_PI);

    auto latRad = gps.latitude;
    auto lonRad = gps.longitude + M_PI;
    auto yFromEquator = radius * log(tan(M_PI / 4 + latRad / 2));

    xy.first = lonRad * radius;
    xy.second = windowHeight / 2 - yFromEquator;
    return xy;
}
