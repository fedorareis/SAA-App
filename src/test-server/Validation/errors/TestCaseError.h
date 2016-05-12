//
// Created by Kyle Piddington on 1/19/16.
//

#ifndef SAA_APPLICATION_TESTCASEERROR_H
#define SAA_APPLICATION_TESTCASEERROR_H

#include <string>

class TestCaseError {
   public:
   TestCaseError(long timestamp) : timestamp(timestamp){};
   TestCaseError(const TestCaseError & other):
      timestamp(other.timestamp),
      isError_(other.isError_){}
   long getTimestamp(){return timestamp;}
   bool isError(){return isError_;}
   void setError(bool is){isError_ = is;}
   virtual std::string description() = 0;
   virtual std::string csvString() = 0;

   private:
   long timestamp;
   bool isError_;
};


#endif //SAA_APPLICATION_TESTCASEERROR_H
