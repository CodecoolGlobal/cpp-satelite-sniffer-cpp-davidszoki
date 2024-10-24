import ephem


def get_satellite_coordinates(tle_name, tle_line1, tle_line2):
    satellite = ephem.readtle(tle_name, tle_line1, tle_line2)
    observer = ephem.Observer()
    observer.date = ephem.now()
    satellite.compute(observer)

    latitude = satellite.sublat  # Latitude in radians
    longitude = satellite.sublong  # Longitude in radians
    altitude = satellite.elevation  # Altitude in meters

    latitude_deg = float(latitude) * 180.0 / ephem.pi
    longitude_deg = float(longitude) * 180.0 / ephem.pi

    return latitude_deg, longitude_deg, altitude
