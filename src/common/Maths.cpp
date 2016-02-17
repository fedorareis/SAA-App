//
// Created by jacrushar on 12/1/15.
//

#include "Maths.h"

float toRadians(float lat) {
    return (float)(lat * M_PI / 180);
}

/*
 * Calculates the distance between two latitude/longitude coordinates and returns the distance in nautical miles.
 */
float calcDistance(float lat1, float lon1, float lat2, float lon2) {
    float phi1 = toRadians(lat1);
    float phi2 = toRadians(lat2);
    float deltaPhi = toRadians(lat2 - lat1);
    float deltaLambda = toRadians(lon2 - lon1);
    double a = sin(deltaPhi/2) * sin(deltaPhi/2) + cos(phi1) * cos(phi2) * sin(deltaLambda/2) * sin(deltaLambda/2);
    double c = 2 * atan2(sqrt(a), sqrt(1 - a));
    double d = EARTH_RADIUS * c;
    return (float)d;
}

float fpsToNmph(float fps) {
    return fps * KNOT_CONVERSION;
}

float bearingToRadians(float bearing) {
    return -bearing * M_PI / 180;
}


bool operator==(const Vector3d& lhs, const Vector3d& rhs)
{
    return lhs.x == rhs.x &&
           lhs.y == rhs.y &&
           lhs.z == rhs.z;
}

Vector3d getDifference(Vector3d plane, Vector3d ownship)
{
    float positionX = calcDistance(plane.latitude(), ownship.latitude(), ownship.latitude(),
                                   ownship.longitude()) * (plane.latitude() < ownship.latitude() ? -1 : 1);
    float positionY = calcDistance(ownship.latitude(), plane.longitude(), ownship.latitude(),
                                   ownship.longitude()) * (plane.longitude() < ownship.longitude() ? -1 : 1);

    float positionZ = plane.altitude() - ownship.altitude();

   return Vector3d(positionX,positionY,positionZ);


}
