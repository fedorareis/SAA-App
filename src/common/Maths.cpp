//
// Created by jacrushar on 12/1/15.
//

#include "Maths.h"

float toRadians(float lat) {
    return (float)(lat * M_PI / 180);
}

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

