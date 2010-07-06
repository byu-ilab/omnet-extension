#ifndef COMMAND_RUNNER_H
#define COMMAND_RUNNER_H

#include <string>

//!@defgroup cmdrunner Command Runner
//!CommandRunner::Run function that executes program for you

//!The CommandRunner class can be used to execute shell commands from a C++ program.
//!@ingroup cmdrunner
namespace CommandRunner {
	//!Executes the passed-in command string.
	//!@code
	//!CommandRunner::Run("g++ -o hello HelloWorld.cpp");
	//!@endcode
	//!@throw CS240Exception If the command fails (i.e., returns a non-zero value from main)
	void Run(const std::string & commandText);
}


#endif

