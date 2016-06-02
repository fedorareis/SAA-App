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
// Created by Kyle Piddington on 1/21/16.
//
/**
 * MockTest: An example of how to use Google mock, and a few features
 *
 */
#include <gtest/gtest.h>
#include <gmock/gmock.h>
using ::testing::Return;
using ::testing::_;

/**
 * Foo is our target interface. We'll be mocking it.
 * Note that Foo is pure virtual, and does not have any implemenation.
 */
struct Foo
{

   virtual void bar() = 0;
   virtual int baz(int a, int b) = 0;
};

/**
 * Bar is a test class that relies on the unimplemented class Foo.
 */
struct Bar
{
   int callFoo(Foo & f) { f.bar(); return f.baz(5, 10);}
};

/**
 * Foo_test is our mocking class. We'll use GoogleMock to supply a few functions.
 */
struct Foo_test : public Foo
{
   /**
    * Supply the first function. The method signiture of bar is void(), since it has no return value, and
    * takes no paramaters.
    */
   MOCK_METHOD0(bar , void());
   /**
    * Supply the second method. MOCK_METHOD2 is used as the method has two parameters
    * The signiture of baz is int (int, int). Baz returns an int, and takes two integers.
    */
   MOCK_METHOD2(baz , int (int , int));
};

/**
 * This test shows how to call google mock objects.
 */
TEST(Footest, testMocks)
{
   /**
    * Create the mock object
    */
   Foo_test foo;
   /**
    * We expect the method bar() to be called once during the object's lifetime.
    */
   EXPECT_CALL(foo,bar())
               .Times(1);

   /**
    * We expect Baz to be called with any number for the first parameter, and 10 for the second.
    * On return, baz will return 5.
    */
   EXPECT_CALL(foo, baz(_ , int(10)))
               .WillOnce(Return(5));



   Bar b;
   /**
    * the object Bar has no idea that Foo is a mock, but can still call foo.bar() and foo.baz()
    */
   int retVal = b.callFoo(foo);
   /**
    * 5 is returned from callFoo.
    */
   EXPECT_EQ(retVal,5);

}