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
  std::cout << "Final Results:  " << errors.size() << " Errors, " << numResults << " Results" << std::endl;
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
