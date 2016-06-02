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

#ifndef SAA_APPLICATION_VALIDATOR_H
#define SAA_APPLICATION_VALIDATOR_H


#include <iosfwd>
#include <test-server/TestCase.h>
#include <common/sockets/ClientSocket.h>
#include <thread>
#include "TestCaseResult.h"
#include "test-server/Validation/errors/TestCaseError.h"
#include "VerificationTest.h"

/**
 * The Validator takes in a test case, and a socket to accept
 * client results on. the validator waits for all results,
 * and then performs a final verification step.
 */
class Validator
{
public:
   Validator(const TestCase  tc, std::shared_ptr<ClientSocket> receptionSocket);
   ~Validator();
   /**
    * End the current simulation, wait for all results from the socket, and
    * perform the verification step
    */
   void endSimulation();
   const std::vector<std::shared_ptr<TestCaseError>> & getErrors()const;
   bool hasReceivedResults() const;
   bool hasErrors()const;

    static void addTester(std::shared_ptr<VerificationTest> tester);

private:

   std::thread reportThread;
   //Results sorted by timestamp
   const TestCase tc;
   std::vector<TestCaseResult> results;
    static std::vector<std::shared_ptr<VerificationTest>> testers;
   std::vector<std::shared_ptr<TestCaseError> > errors;
   bool gotResults;
   static void ValidatorThreadRoutine(Validator * v, std::shared_ptr<ClientSocket> sock);

};


#endif //SAA_APPLICATION_VALIDATOR_H
