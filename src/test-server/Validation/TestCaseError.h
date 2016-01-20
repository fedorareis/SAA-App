//
// Created by Kyle Piddington on 1/19/16.
//

#ifndef SAA_APPLICATION_TESTCASEERROR_H
#define SAA_APPLICATION_TESTCASEERROR_H


class TestCaseError {
   public:
   TestCaseError(long timestamp) : timestamp(timestamp){};
   virtual std::string description() = 0;

   private:
   long timestamp;
};


#endif //SAA_APPLICATION_TESTCASEERROR_H
