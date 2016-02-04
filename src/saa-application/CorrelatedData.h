//
// Created by Hae Ri Hwang on 2/3/16.
//

#ifndef SAA_APPLICATION_CORRELATEDDATA_H
#define SAA_APPLICATION_CORRELATEDDATA_H

#include "SensorData.h"
#include "common/protobuf/cdti.pb.h"

class CorrelatedData {

public:
   CorrelatedData (float positionX, float positionY, float positionZ,
                   float velocityX, float velocityY, float velocityZ)
   {
      position = new Vector();
      velocity = new Vector();
      position->set_x(positionX);
      position->set_y(positionY);
      position->set_z(positionZ);
      velocity->set_x(velocityX);
      velocity->set_y(velocityY);
      velocity->set_z(velocityZ);
   }

   void addSensor(Sensor sensor) {
      sensors.push_back(sensor);
   }

   void setPlanTag(int planeId)
   {
      planeTag=planeId;
   }

   std::vector<Sensor> getSensor()
   {
      return sensors;
   }

   CDTIPlane* getCDTIPlane()
   {
      severity = CDTIPlane::PROXIMATE;

      plane->set_id(tailNumber);
      plane->set_severity(severity);
      plane->set_allocated_position(position);
      plane->set_allocated_velocity(velocity);
      plane->set_planetags(0, planeTag);

      return plane;
   }

   Vector3d  getPosition()
   {
      return Vector3d(position->x(),position->y(),position->z());
   }

   Vector3d  getVelocity()
   {
      return Vector3d(velocity->x(),velocity->y(),velocity->z());
   }

   int getPlaneTag()
   {
      return planeTag;
   }

   double getTimeStamp()
   {
      return timeStamp;
   }

private:
   std::vector<Sensor> sensors; // list of sensor!
   std::string tailNumber;
   Vector *velocity;
   Vector *position;
   CDTIPlane *plane = new CDTIPlane();
   CDTIPlane::Severity severity;
   int planeTag;
   double timeStamp;
};

#endif //SAA_APPLICATION_CORRELATEDDATA_H
