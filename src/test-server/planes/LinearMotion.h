//
// Created by Kyle Piddington on 12/1/15.
//

#ifndef SAA_APPLICATION_LINEARMOTION_H
#define SAA_APPLICATION_LINEARMOTION_H


#include "Motion.h"

class LinearMotion : public Motion {
   public:
   LinearMotion(Vector3d initialPos, Vector3d velocity);
   LinearMotion(const LinearMotion & other);

   virtual ~LinearMotion();

   virtual Vector3d getInitialPosition() override;

   virtual Vector3d getVelocityAtTick(float tick) override;

   virtual LinearMotion * clone() const;

   virtual Vector3d getMotionAtTick(float tick);

   private:
      Vector3d initialPos;
      Vector3d velocity;
};


#endif //SAA_APPLICATION_LINEARMOTION_H
