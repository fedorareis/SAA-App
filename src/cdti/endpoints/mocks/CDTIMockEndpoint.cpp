//
// Created by Kyle Piddington on 11/30/15.
//

#include <iostream>
#include "CDTIMockEndpoint.h"


CDTIPlane* makeOwnship()
{
    Vector *planeVelocity;
    planeVelocity = new Vector();

    planeVelocity->set_x(0);
    planeVelocity->set_y(0);
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
    report = new CDTIReport();
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
    report->set_allocated_ownship(makeOwnship());
    CDTIPlane* otherPlane = report->add_planes();
    makePlane(otherPlane,"Plane 1",position1,CDTIPlane_Severity_TRAFFIC);
    otherPlane = report->add_planes();
    makePlane(otherPlane,"Plane 2",position2,CDTIPlane_Severity_RESOLUTION);
    otherPlane = report->add_planes();
    makePlane(otherPlane,"Plane 3",position3,CDTIPlane_Severity_PROXIMATE);

}

void CDTIMockEndpoint::step()
{
    CDTIReport* newReport = new CDTIReport();
    newReport->set_timestamp(++time);
    newReport->set_allocated_ownship(makeOwnship());
    std::cout << time << std::endl;
    for(int i = 0; i < report->planes_size(); i++)
    {
        CDTIPlane plane = report->planes(i);
        Vector planeVelocity = plane.velocity();
        std::cout << planeVelocity.x() << std::endl;
        Vector ownshipVelocity = report->ownship().velocity();
        Vector* newPosition = new Vector();
        Vector* newVelocity = new Vector();
        //todo this is assumiong a 1-second timestep, where the equation simplifies itself.
        newPosition->set_x(plane.position().x() + planeVelocity.x() - ownshipVelocity.x());
        newPosition->set_y(plane.position().y() + planeVelocity.y() - ownshipVelocity.y());
        newPosition->set_z(plane.position().z() + planeVelocity.z() - ownshipVelocity.z());

        newVelocity->set_x(plane.velocity().x());
        newVelocity->set_y(plane.velocity().y());
        newVelocity->set_z(plane.velocity().z());

        //plane.clear_position();
        //plane.set_allocated_position(newPosition);

        CDTIPlane* newPlane = newReport->add_planes();
        newPlane->set_id(plane.id());
        newPlane->set_allocated_position(newPosition);
        newPlane->set_allocated_velocity(newVelocity);
        newPlane->set_severity(plane.severity());
    }

    report = newReport;
}

const CDTIEndpoint& CDTIMockEndpoint::operator >> (::google::protobuf::Message & msg) const
{
    CDTIReport& myreport = *report;
    msg.CopyFrom(myreport);
    return *this;
}

bool CDTIMockEndpoint::isRunning() const
{
    return true;
}
