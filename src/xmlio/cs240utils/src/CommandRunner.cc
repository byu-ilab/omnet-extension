#include <sstream>
#include <cstdlib>

#include "CS240Exception.h"
#include "StringUtil.h"

#include "CommandRunner.h"

using namespace std;

namespace CommandRunner
{
namespace
{
	string InvalidCommandErrorMessage(const string & commandText) {
		return string("invalid command: ") + commandText;
	}

	string CommandFailedErrorMessage(const string & commandText) {
		return string("command failed: ") + commandText;
	}
}

void Run(const string & commandText)
{

	string commandTextCopy = commandText;
	StringUtil::Trim(commandTextCopy);
	
	if (commandTextCopy.empty())
	{
		throw CS240Exception(InvalidCommandErrorMessage(commandTextCopy));
	}

	if (::system(commandTextCopy.c_str()) != 0)
	{
		throw CS240Exception(CommandFailedErrorMessage(commandTextCopy));
	}
}

}

