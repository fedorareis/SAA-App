/**
 * Copyright (c) 2016 Cal Poly Capstone Team Rocket
 *
 * Permission is hereby granted, free of charge, to any person obtaining a copy of
 * this software and associated documentation files (the "Software"), to deal in the
 * Software without restriction, including without limitation the rights to use, copy,
 * modify, merge, publish, distribute, sublicense, and/or sell copies of the Software,
 * and to permit persons to whom the Software is furnished to do so, subject to
 * the following conditions:
 * The above copyright notice and this permission notice shall be included in all
 * copies or substantial portions of the Software.
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR IMPLIED,
 * INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, FITNESS FOR A
 * PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT
 * HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION
 * OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE
 * SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
 *
 */
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
   void addSensor(Sensor sensor, int planeTag, std::string planeId, Vector3d velocity, Vector3d
   pos)
   {
      sensors.push_back(sensor);
      planeTags.push_back(planeTag);
      tailNumbers.push_back(planeId);
      velocities.push_back(velocity);
      positions.push_back(pos);
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
    void setVelocity(Vector3d vel)
    {
       velocity->set_x(vel.x);
       velocity->set_y(vel.y);
       velocity->set_z(vel.z);
    }

   // returns the CDTIPlane
   CDTIPlane* getCDTIPlane()
   {
      plane->Clear();

      severity = CDTIPlane::AIR;
      auto radarIter = std::find(sensors.begin(), sensors.end(), Sensor::radar);
      if (radarIter != sensors.end())
      {
         auto radarIdIndex = std::distance(sensors.begin(), radarIter);
         tailNumber = tailNumbers[radarIdIndex];
         setVelocity(velocities[radarIdIndex]);
         setPosition(positions[radarIdIndex]);
      }
      auto tcasIter = std::find(sensors.begin(), sensors.end(), Sensor::tcas);
      if (tcasIter != sensors.end())
      {
         auto tcasIdIndex = std::distance(sensors.begin(), tcasIter);
         tailNumber = tailNumbers[tcasIdIndex];
         setPosition(positions[tcasIdIndex]);
      }
      auto adsbIter = std::find(sensors.begin(), sensors.end(), Sensor::adsb);
      if (adsbIter != sensors.end())
      {
         auto adsbIdIndex = std::distance(sensors.begin(), adsbIter);
         tailNumber = tailNumbers[adsbIdIndex];
         setVelocity(velocities[adsbIdIndex]);
         setPosition(positions[adsbIdIndex]);
      }
      plane->set_id(tailNumber);
      plane->set_severity(severity);
      plane->set_allocated_position(position);
      plane->set_allocated_velocity(velocity);
//      std::cout << "start planeTags" << std::endl;
      for(int ndx = 0; ndx < planeTags.size(); ndx++) {

         plane->add_planetags(planeTags[ndx]);
         std::string sensorName;
         switch(sensors[ndx]) {
            case Sensor::adsb:
               sensorName = "adsb";
                 break;
            case Sensor::radar:
               sensorName = "radar";
                 break;
            case Sensor::tcas:
               sensorName = "tcas";
                 break;
            default:
               sensorName ="???";
         }
         std::cout << "sensor type" << sensorName << std::endl;
         std::cout << "planeID " << planeTags[ndx] << std::endl;
//         std::cout << "pos n:" << positions[ndx].x << " e:" <<positions[ndx].y << " d:" << positions[ndx].z <<
//         std::endl;
//         *planeTag = planeTags.at(ndx);
//         plane->set_planetags(ndx, planeTags.at(ndx));
      }
//      std::cout << "end planeTags" << std::endl << std::endl << std::endl;
      std::cout << "planeTags.size() = " << plane->planetags_size() << std::endl;

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
    std::vector<std::string> tailNumbers;
    std::vector<Vector3d> velocities;
    std::vector<Vector3d> positions;
   std::string tailNumber;
   Vector *velocity;
   Vector *position;
   CDTIPlane *plane = new CDTIPlane();
   CDTIPlane::Severity severity;
   double timeStamp;
};

#endif //SAA_APPLICATION_CORRELATEDDATA_H
