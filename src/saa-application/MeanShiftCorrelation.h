//
// Created by Kyle Piddington on 2/29/16.
//

#ifndef SAA_APPLICATION_MEANSHIFTCORRELATION_H
#define SAA_APPLICATION_MEANSHIFTCORRELATION_H


#include <mlpack/core.hpp>
#include <common/IMeanShift.h>
#include <common/MeanShiftImpl.h>
#include "SensorData.h"
#include "CorrelationStrategy.h"
#include "CorrelatedData.h"

enum CorrelationFlags
{
   COR_POS = 0x1,
   COR_VEL = 0x2
};
class MeanShiftCorrelation : public CorrelationStrategy {
   public:
      MeanShiftCorrelation(double window = 0, int flags = COR_POS);
      virtual std::vector<CorrelatedData> correlate(std::vector<SensorData> planes);

   private:
      double cWindow;
      int currFlags;
      arma::Col<size_t> prevAssignments;
      std::shared_ptr<IMeanShift> meanshift;




};


#endif //SAA_APPLICATION_MEANSHIFTCORRELATION_H
