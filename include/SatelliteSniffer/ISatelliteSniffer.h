#pragma once
#include <Satellite.h>
#include <vector>

class ISatelliteSniffer {
public:
    ISatelliteSniffer() = default;

    virtual ~ISatelliteSniffer() = default;

    virtual void updatePositions(const int &width, const int &height, const int &updateTime) =0;

    std::vector<Satellite> getSatellites() { return satellites; }

protected:
    std::vector<Satellite> satellites;
};
