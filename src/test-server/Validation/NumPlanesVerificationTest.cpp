//
// Created by lejonmcgowan on 2/3/16.
//

#include "NumPlanesVerificationTest.h"

#include "errors/NumPlanesTestCaseError.h"
std::vector<std::shared_ptr<TestCaseError>> NumPlanesVerificationTest::verify(TestCaseResult &result)
{
    bool correct = tc->getPlanes().size() == result.getPlanes().size();
    std::vector<std::shared_ptr<TestCaseError>> errors;
    NumPlanesTestCaseError error = NumPlanesTestCaseError(result.getTime(),
          tc->getPlanes().size(),
          result.getPlanes().size());
    error.setError(!correct);
    errors.push_back(std::make_shared<NumPlanesTestCaseError>(error));

    return errors;
}
