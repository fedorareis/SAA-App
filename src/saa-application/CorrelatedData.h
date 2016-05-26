//
// Created by Hae Ri Hwang on 2/3/16.
//

#ifndef SAA_APPLICATION_CORRELATEDDATA_H
#define SAA_APPLICATION_CORRELATEDDATA_H

#include "SensorData.h"
#include "common/protobuf/cdti.pb.h"
#include <algorithm>

class CorrelatedData {

public:
   // constructor that takes in position and velocity
   CorrelatedData (){
      position = new Vector();
      velocity = new Vector();
      position->set_x(0);
      position->set_y(0);
      position->set_z(0);
      velocity->set_x(0);
      velocity->set_y(0);
      velocity->set_z(0);

   }
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

   void addPosition(Vector3d pos)
   {
      position->set_x(position->x() + pos.x);
      position->set_y(position->y() + pos.y);
      position->set_z(position->z() + pos.z);
   }

   void setPosition(Vector3d pos)
   {
      position->set_x(pos.x);
      position->set_y(pos.y);
      position->set_z(pos.z);
   }

   // adds sensor and its planetag to the vector
   void addSensor(Sensor sensor, int planeId)
   {
      sensors.push_back(sensor);
      planeTags.push_back(planeId);
   }

   // setter for time stamp
   void setTimeStamp(double stamp)
   {
      timeStamp = stamp;
   }

   // gets the list of sensors
   std::vector<Sensor> getSensor()
   {
      return sensors;
   }

   // returns the CDTIPlane
   CDTIPlane* getCDTIPlane()
   {
      severity = CDTIPlane::AIR;
      auto radarIter = std::find(sensors.begin(), sensors.end(), Sensor::radar);
      if (radarIter != sensors.end())
      {
         auto radarIdIndex = std::distance(sensors.begin(), radarIter);
         tailNumber = planeTags[radarIdIndex];
      }
      auto tcasIter = std::find(sensors.begin(), sensors.end(), Sensor::tcas);
      if (tcasIter != sensors.end())
      {
         auto tcasIdIndex = std::distance(sensors.begin(), tcasIter);
         tailNumber = planeTags[tcasIdIndex];
      }
      auto adsbIter = std::find(sensors.begin(), sensors.end(), Sensor::adsb);
      if (adsbIter != sensors.end())
      {
         auto adsbIdIndex = std::distance(sensors.begin(), adsbIter);
         tailNumber = planeTags[adsbIdIndex];
      }
      plane->set_id(tailNumber);
      plane->set_severity(severity);
      plane->set_allocated_position(position);
      plane->set_allocated_velocity(velocity);


      for(int ndx = 0; ndx < planeTags.size(); ndx++) {
         plane->add_planetags(planeTags.at(ndx));
         //plane->set_planetags(ndx, planeTags.at(ndx));
      }

      return plane;
   }

   // returns the position
   Vector3d  getPosition()
   {
      return Vector3d(position->x(),position->y(),position->z());
   }

   // returns the velocity
   Vector3d  getVelocity()
   {
      return Vector3d(velocity->x(),velocity->y(),velocity->z());
   }

   void addVelocity(Vector3d vel)
   {
      velocity->set_x(std::abs(vel.x) > std::abs(velocity->x()) ? vel.x : velocity->x());
      velocity->set_y(std::abs(vel.y) > std::abs(velocity->y()) ? vel.y : velocity->y());
      velocity->set_z(std::abs(vel.z) > std::abs(velocity->z()) ? vel.z : velocity->z());
   }

   std::vector<int> getPlaneTags()
   {
      return planeTags;
   }

   double getTimeStamp()
   {
      return timeStamp;
   }

private:
   std::vector<Sensor> sensors; // list of sensors that were used to correlate this plane
   std::vector<int> planeTags; // list of planeTags from each of the sensors
   std::string tailNumber;
   Vector *velocity;
   Vector *position;
   CDTIPlane *plane = new CDTIPlane();
   CDTIPlane::Severity severity;
   double timeStamp;
};

#endif //SAA_APPLICATION_CORRELATEDDATA_H
