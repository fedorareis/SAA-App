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
// Created by Kyle Piddington on 1/20/16.
//

#include "ValidationWriter.h"
#include "Validator.h"
#include <iostream>
#include <fstream>

void ValidationWriter::writeErrors(std::ostream &str, const Validator &v) {
   std::ofstream out;
   char *outName = "validation.csv";
   out.open(outName);
   out << "Time Stamp, Result Type,Expected X/Num,Actual X/Num,Expected Y,Actual Y,Expected Z,Actual Z\n";
   if (!out.is_open()) {
      str << "well shit...\n";
   }
   if(v.hasErrors())
   {
      if(!v.hasReceivedResults())
      {
         str << "No correlations recieved!";
      }
      else {
         for (auto error : v.getErrors()) {
            if (error->isError()) {
               str << "Correlation error: [" << error->getTimestamp() << "] : "
               << error->description() << std::endl;
            }
            out << error->csvString();
         }
      }
   }
   else
   {
      str << "Correlation is perfect, no errors detected!" << std::endl;
   }
   out.close();
   str << "\nclosed validation csv file '" << outName << "'\n";
}
