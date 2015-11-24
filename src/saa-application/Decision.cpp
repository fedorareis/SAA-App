//
// Created by jacrushar on 11/17/15.
//

#include <iostream>
#include <fstream>
#include "common/protobuf/cdti.pb.h"
#include "Decision.h"
#include "Plane.h"

void Decision::report()
{
   std::cout << "We are making decisions here" << std::endl;
   CDTIPlane plane;
   Vector *vector = new Vector();
   Vector *vector2 = new Vector();
   CDTIPlane plane2;

   std::string id = "CF34X";
   plane.set_id(id);
   std::cout << "Plane ID: " << plane.id() << std::endl;
   vector->set_x(1);
   vector->set_y(1);
   vector->set_z(1);
   vector2->set_x(1);
   vector2->set_y(1);
   vector2->set_z(1);
   plane.set_allocated_velocity(vector);
   std::cout << "Plane volocity x: " << plane.velocity().x() << std::endl;
   plane.set_allocated_position(vector2);
   std::cout << "Plane position x: " << plane.position().x() << std::endl;
   plane.set_severity(CDTIPlane::PROXIMATE);
   std::cout << "Plane severity: " << plane.severity() << std::endl;

   // Write the new plane back to disk.
   std::fstream output("test", std::ios::out | std::ios::trunc | std::ios::binary);
   if (!plane.SerializeToOstream(&output))
   {
      std::cerr << "Failed to write plane." << std::endl;
   }

   output.close();

   std::fstream input("test", std::ios::in | std::ios::binary);
   if (!plane2.ParseFromIstream(&input))
   {
      std::cerr << "Failed to parse plane." << std::endl;
   }

   std::cout << "Plane2 ID: " << plane2.id() << std::endl;

   google::protobuf::ShutdownProtobufLibrary();

   Plane plane3 = Plane("X305C", 3, 4, 5, 6, 7, 8);
   CDTIPlane cdtiPlane = plane3.getCDTIPlane();

   std::cout << "Plane ID: " << cdtiPlane.id() << std::endl;
   std::cout << "Plane positionX: " << cdtiPlane.position().x() << std::endl;
   std::cout << "Plane positionY: " << cdtiPlane.position().y() << std::endl;
   std::cout << "Plane positionZ: " << cdtiPlane.position().z() << std::endl;
   std::cout << "Plane velocityX: " << cdtiPlane.velocity().x() << std::endl;
   std::cout << "Plane velocityY: " << cdtiPlane.velocity().y() << std::endl;
   std::cout << "Plane velocityZ: " << cdtiPlane.velocity().z() << std::endl;
   std::cout << "Plane severity: " << cdtiPlane.severity() << std::endl;
}