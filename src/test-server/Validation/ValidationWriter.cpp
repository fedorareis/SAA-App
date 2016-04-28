//
// Created by Kyle Piddington on 1/20/16.
//

#include "ValidationWriter.h"
#include "Validator.h"
#include <iostream>
#include <fstream>

void ValidationWriter::writeErrors(std::ostream &str, const Validator &v) {
   std::ofstream out;
   out.open("errors.csv");
   out << "Time Stamp,Expected,Actual\n";

   if(v.hasErrors())
   {
      if(!v.hasReceivedResults())
      {
         str << "No correlations recieved!";
      }
      else {
         for (auto error : v.getErrors()) {
            str << "Correlation error: [" << error->getTimestamp() << "] : "
            << error->description() << std::endl;
            out << error->getTimestamp() << "," << "\n";
         }
      }
   }
   else
   {
      str << "Correlation is perfect, no errors detected!" << std::endl;
   }
   out.close();
}
