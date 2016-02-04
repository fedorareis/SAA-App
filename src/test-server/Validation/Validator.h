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
