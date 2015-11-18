//
// Created by Helen Hwang on 11/18/15.
//

#ifndef SAA_APPLICATION_TESTFILEPARSER_H
#define SAA_APPLICATION_TESTFILEPARSER_H
/**
 * Include library for XML parsing
 *
 * This class parses the XML file that may contain multiple testsuit
 * which may contain multiple testcases.
 */
class TestFileParser{
   // ALWAYS initialize data members in the same order they are declared
public:
   TestFileParser(std::string file) : testFile(file) { }; // constructor
   void load(); // read test suits to form test case
   // std::deque<TestCase> GetTestSuits(); // returns the list of TestCases

protected:
   std::string testFile;

private:
   void buildTestCase(); // builds each test case
   void getOwnship(); // handles parsing data for ownship
   void getPlanes(); // handles parsing data for other planes
};

#endif //SAA_APPLICATION_TESTFILEPARSER_H
