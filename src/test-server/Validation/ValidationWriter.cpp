//
// Created by Kyle Piddington on 1/20/16.
//

#include "ValidationWriter.h"
#include "Validator.h"

void ValidationWriter::writeErrors(std::ostream &str, const Validator & v) {
   if(v.hasErrors())
   {
      if(!v.recievedResults())
      {
         str << "No correlations recieved!";
      }
      else {
         for (auto error : v.getErrors()) {
            str << "Correlation error: [" << error->getTimestamp() << "] : "
            << error->description() << std::endl;
         }
      }
   }
   else
   {
      str << "Correlation is perfect, no errors detected!" << std::endl;
   }


}
