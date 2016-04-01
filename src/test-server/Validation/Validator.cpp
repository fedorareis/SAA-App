//
// Created by Kyle Piddington on 1/19/16.
//

#include <iostream>
#include "Validator.h"

std::vector<std::shared_ptr<VerificationTest>> Validator::testers = {};

Validator::Validator(const TestCase tc, std::shared_ptr<ClientSocket> receptionSocket):
tc(tc)
{
   reportThread = std::thread(Validator::ValidatorThreadRoutine,this,receptionSocket);

}

Validator::~Validator() {

}

void Validator::endSimulation()
{
   reportThread.join();
   unsigned long expectedPlanes = tc.getPlanes().size();
   int numResults = results.size();
   int numSuccesses = 0;
   for (auto result : results)
   {
      for (auto tester: testers)
      {

         for(auto error: tester->verify(result))
         {
            errors.push_back(error);
         }
      }
   }
  std::cout << "Final Results:  " << errors.size() << "Errors, " << numResults << std::endl;
}

const std::vector<std::shared_ptr<TestCaseError>> & Validator::getErrors()const {
   return errors;
}

bool Validator::hasErrors()const {
   return errors.size() > 0 || !hasReceivedResults();
}

void Validator::ValidatorThreadRoutine(Validator * v, std::shared_ptr<ClientSocket> sock) {
   while(sock->hasData())
   {
      CDTIReport rept;
      try
      {
         (*sock) >> rept;
         v->results.push_back(TestCaseResult::fromGoogleProtobuf(rept));
         v->gotResults = true;

      }
      catch(std::exception) {
         //log that shit
      }
   }
}

bool Validator::hasReceivedResults() const
{
   return this->gotResults;
}

void Validator::addTester(std::shared_ptr<VerificationTest> tester)
{
   testers.push_back(tester);
}
