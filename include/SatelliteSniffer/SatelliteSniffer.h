#pragma once
#include <Satellite.h>
#include <ISatelliteSniffer.h>
#include <UI.h>

class SatelliteSniffer : public ISatelliteSniffer {
public:
    SatelliteSniffer(const std::string &source, const int &width, const int &height);

    ~SatelliteSniffer() = default;

    void run(const int &speed = 1);

    void updatePositions(const int &width, const int &height, const int &updateTime) override;

private:
    std::vector<Satellite> createSatellites() const;

    UI ui;
    std::string source;
};
