//
// Created by Kyle Piddington on 11/30/15.
//

#include <iostream>
#include "CDTIMockEndpoint.h"


CDTIPlane* makeOwnship()
{
    Vector *planeVelocity;
    planeVelocity = new Vector();

    planeVelocity->set_x(10);
    planeVelocity->set_y(10);
    planeVelocity->set_z(0);


    CDTIPlane* myPlane = new CDTIPlane();
    myPlane->set_id("ownshipPlane");
    myPlane->set_allocated_velocity(planeVelocity);

    return myPlane;
}

CDTIPlane* makePlane(CDTIPlane* otherPlane,std::string name,Vector* position,CDTIPlane_Severity severity)
{
    Vector* velocity = new Vector();

    velocity->set_x(2);
    velocity->set_y(0);
    velocity->set_z(0);


    otherPlane->set_id(name);
    otherPlane->set_allocated_position(position);
    otherPlane->set_allocated_velocity(velocity);
    otherPlane->set_severity(severity);

    return otherPlane;
}

CDTIMockEndpoint::CDTIMockEndpoint()
{
    Vector *position1 = new Vector(), *position2 = new Vector(), *position3 = new Vector();

    position1->set_x(10);
    position1->set_y(10);
    position1->set_z(0);

    position2->set_x(-6);
    position2->set_y(-6);
    position2->set_z(0);

    position3->set_x(9);
    position3->set_y(-7);
    position3->set_z(0);
   //Initialize report
    report.set_allocated_ownship(makeOwnship());
    CDTIPlane* otherPlane = report.add_planes();
    makePlane(otherPlane,"Plane 1",position1,CDTIPlane_Severity_TRAFFIC);
    otherPlane = report.add_planes();
    makePlane(otherPlane,"Plane 2",position2,CDTIPlane_Severity_RESOLUTION);
    otherPlane = report.add_planes();
    makePlane(otherPlane,"Plane 3",position3,CDTIPlane_Severity_PROXIMATE);

}

void CDTIMockEndpoint::step()
{
    report.set_timestamp(++time);
    for(auto plane: report.planes())
    {
        Vector planeVelocity = plane.velocity();
        Vector ownshipVelocity = report.ownship().velocity();
        Vector*newPosition = new Vector();
        newPosition->set_x(plane.position().x() + planeVelocity.x() - ownshipVelocity.x());
        newPosition->set_y(plane.position().y() + planeVelocity.y() - ownshipVelocity.y());
        newPosition->set_z(plane.position().z() + planeVelocity.z() - ownshipVelocity.z());

        std::cout << newPosition->x() << " " << newPosition->y()
        << " " << newPosition->z() << std::endl;

        plane.clear_position();
        plane.set_allocated_position(newPosition);
    }

}

const CDTIEndpoint& CDTIMockEndpoint::operator >> (::google::protobuf::Message & msg) const
{
   msg.CopyFrom(report);
   return *this;
}

bool CDTIMockEndpoint::isRunning() const
{
    return true;
}
