#include <PythonScriptExecutor.h>
#include <SatelliteSniffer.h>
#include <Utils.h>

using namespace std;

SatelliteSniffer::SatelliteSniffer(const std::string &source, const int &width, const int &height)
    : ui(width, height, *this), source(source) {
    if (getenv("USERNAME") && getenv("PASSWORD"))
        PythonScriptExecutor::executeGetTLEDataPythonScript(getenv("USERNAME"), getenv("PASSWORD"), source);
    satellites = createSatellites();
}

void SatelliteSniffer::run(const int &speed) {
    ui.run(speed);
}

std::vector<Satellite> SatelliteSniffer::createSatellites() const {
    std::vector<Satellite> satellites;
    Utils::fillSatellitesBySourceFile(source, satellites);
    return satellites;
}

void SatelliteSniffer::updatePositions(const int &width, const int &height, const int &updateTime) {
    for (auto &sat: satellites) {
        sat.calculatePosition(sat, width, height, updateTime);
    }
}
