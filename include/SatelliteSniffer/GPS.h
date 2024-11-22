#pragma once

struct GPS {
    GPS(double latitude, double longtitude, double altitude);

    ~GPS() = default;

    double latitude, longitude, altitude;
};
