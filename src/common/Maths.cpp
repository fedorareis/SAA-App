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

Vector3d getDifference(Vector3d latLongAlt1, Vector3d latLongAlt2) {
   float positionX = calcDistance(plane.getLatitude(), ownship.getLatitude(), ownship.getLatitude(),
                                  ownship.getLongitude()) * (plane.getLatitude() < ownship.getLatitude()? -1 : 1);
   float positionY = calcDistance(ownship.getLatitude(), plane.getLongitude(), ownship.getLatitude(),
                                  ownship.getLongitude()) * (plane.getLongitude() < ownship.getLongitude()? -1 : 1);

   float positionZ = plane.getAltitude()-ownship.getAltitude();

   return Vector3d(positionX,positionY,positionZ);


}
