//
// Created by jacrushar on 12/1/15.
//

#include "Maths.h"


using namespace std;

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


bool operator==(const Vector3d lhs, const Vector3d rhs)
{
    return lhs.x == rhs.x &&
           lhs.y == rhs.y &&
           lhs.z == rhs.z;
}

Vector3d getDifference(Vector3d plane, Vector3d ownship)
{
    float positionX = calcDistance(plane.latitude(), ownship.longitude(), ownship.latitude(),
                                   ownship.longitude()) * (plane.latitude() < ownship.latitude() ? -1 : 1);
    float positionY = calcDistance(ownship.latitude(), plane.longitude(), ownship.latitude(),
                                   ownship.longitude()) * (plane.longitude() < ownship.longitude() ? -1 : 1);

    float positionZ = plane.altitude() - ownship.altitude();

   return Vector3d(positionX,positionY,positionZ);


}

double Vector3d::getMagnitude()
{
    return sqrt(x * x + y * y + z * z);
}

inline float feetToNauticalMiles(float feet)
{
    return feet * 1.0f / FEET_TO_NAUT_MILES;
}

inline float nauticalMilesToFeet(float miles)
{
    return miles * NAUT_MILES_TO_FEET;
}
Vector3d llaToXyz(Vector3d latLongAlt)
{
    auto lat = degToRad(latLongAlt.x);
    auto lng = degToRad(latLongAlt.y);
    auto alt = latLongAlt.z;
    //notation: latLongAlt.xyz = {latitude,longitude,altitude}
    double R = EARTH_RADIUS + alt;
    double h = R * std::cos(lat);
    double z = R * std::sin(lat);
    double x = h * std::cos(lng);
    double y = h * std::sin(lng);
    return Vector3d(x,y,z);
}
Vector3d xyzToLla(Vector3d vec)
{
    //notation: latLongAlt.xyz = {latitude,longitude,altitude}
    double R = EARTH_RADIUS + std::sqrt(vec.x * vec.x + vec.y * vec.y + vec.z + vec.z);
    double latRad = std::asin(vec.z / R);
    double lngRad = R * atan2(vec.y,vec.x);
    double alt = R - EARTH_RADIUS;
    return Vector3d(radToDeg(latRad),radToDeg(lngRad),alt);
}
NEDBases makeNEDBasis(Vector3d vec)
{
    double x = vec.x;
    double y = vec.y;
    double z = vec.z;
    Vector3d z_hat(0,0,1.0);

    Vector3d down = vec.normalized() * -1.0;
    Vector3d east = Vector3d::cross(z_hat,down).normalized();
    Vector3d north = Vector3d::cross(down,east).normalized();

    return NEDBases(north, east, down);
}

BodyBasis makeBodyBasis(Vector3d lla, Vector3d vel)
{
    vel = vel.normalized();
    Vector3d xyz = xyzToLla(lla);
    NEDBases velBasis = makeNEDBasis(vel);
    Vector3d forward = velBasis.north * vel.x + velBasis.east * vel.y  + velBasis.down * vel.z ;
    Vector3d right = Vector3d::cross(velBasis.down,forward);
    Vector3d down = Vector3d::cross(forward,right);
    return BodyBasis(forward,right,down);
}
