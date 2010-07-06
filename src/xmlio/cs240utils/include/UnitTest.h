#ifndef UNIT_TEST_H
#define UNIT_TEST_H

//!@defgroup unittest Unit Test
//!The CS 240 Utilities include a very simple framework for creating unit test cases.
//!Each class in your program should have a public method with the following (or similar) signature
//!@code
//!static bool Test(ostream & os);
//!@endcode
//!that automatically verifies that the class works correctly. 
//!The Test method on a class usually creates one or more instances of the class,
//!calls methods on those objects, and automatically checks that the results returned
//!by the methods are correct. If all tests succeed, Test should return true.
//!If one or more tests fail, Test should return false. For each test that fails,
//!an informative error message that describes the test that failed should be written 
//!to the passed-in output stream. This will tell you which tests failed so that you can
//!fix the problems.
//!
//!You should also write a test driver program that runs all of your automated test cases.
//!This program will be very simple, consisting only of a main function that calls all of
//!the Test methods on your classes. Whenever you add new classes and methods to your program,
//!you should write new tests cases for the new code. Whenever you modify existing code,
//!you should always run your automated tests to make sure you haven't broken anything.
//!@section The TEST Macro
//!The file UnitTest.h defines a preprocessor macro named TEST that makes it easy to write automated test cases. When TEST is called, it is passed the value of a boolean expression that should be true at the point of the call, like this:
//!@code
//!TEST(temperature > 32 && temperature < 212);
//!@endcode
//!If the expression is true (as it should be), TEST does nothing. If the expression is false, TEST prints a message indicating the location (i.e., file name and line number) of the failed test.
//!
//!In order to do its job, TEST makes some fairly strong assumptions about the structure of your Test methods. A Test method that calls the TEST macro must:
//!
//!@li Have a parameter named os of type ostream &
//!@li Declare boolean local variable named success that is initialized to true
//!@li Call the TEST macro once for each condition that is to be verified
//!@li Return the value of the success variable 
//!
//!The following code example shows how to write Test methods using the TEST macro, as well as how to write a test driver program that calls the Test methods.
//!@include unit_test.cpp

//!@def TEST
//!@ingroup unittest
#define TEST(cond) \
do {\
	if (!(cond)) {\
		success = false; os << "Test Failed [" << __FILE__ << ", " << __LINE__ << "]" << endl;\
	}\
}while(false)


#endif

