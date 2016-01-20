//
// Created by Kyle Piddington on 1/19/16.
//

#ifndef SAA_APPLICATION_VALIDATOR_H
#define SAA_APPLICATION_VALIDATOR_H


#include <iosfwd>
#include <test-server/TestCase.h>
#include <common/sockets/ClientSocket.h>
#include <thread>

class Validator {
   public:

   Validator(TestCase tc, std::shared_ptr<ClientSocket> receptionSocket);
   ~Validator();
   void endSimulation(); //Called right before the report is written, think of it as a join();
   void writeReport(std::ostream & out);

   private:

   std::thread reportThread;
   //Results sorted by timestamp
   std::vector<TestCaseResult> results;


};


#endif //SAA_APPLICATION_VALIDATOR_H
