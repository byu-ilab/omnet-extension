#ifndef CS240_EXCEPTION_H
#define CS240_EXCEPTION_H

//!@defgroup exception CS240 Exceptions
//!The CS 240 Utilities provide some classes that help you handle exceptions in your programs. The most important of these classes is CS240Exception. CS240Exception serves as the base class for all other exception classes that you might create. When you throw a CS240Exception object, you can initialize it with a std::string message that provides more information about the error that has occurred. CS240Exception also provides a method for retrieving the message stored in an exception object. The code below shows how a program can handle exceptions of type CS240Exception.
//!@code
//!int foo(int x)
//!{
//!	if (x < 0)
//!	{
//!		throw CS240Exception("negative numbers are illegal");
//!	}
//!
//!	return x * 10;
//!}
//!
//!void main()
//!{
//!	try
//!	{
//!		foo(-5);
//!	}
//!	catch (CS240Exception & e)
//!	{
//!		cout << e.GetMessage() << endl;
//!	}
//!}
//!@endcode
//!	The CS240Exception class can be used anywhere in your code where you need to throw an exception. Placing a descriptive message in an exception object helps to provide additional information about the error to the code that handles the exception. Usually, the message is printed out for the benefit of the user. While the message in the exception object is useful for providing information to the user, it is not very useful to any code in the program that might want to handle the exception and recover from the error.
//!
//!	One way to provide more information to the code handling the exception is to create an exception class for each different type of error that might occur in a program. When an error occurs, the program throws an exception that is specific to the type of error that has occurred rather than throwing an object of the generic CS240Exception class. This allows the code that handles the exception to determine specifically what kind of error has occurred, hopefully making it possible to recover from the error. For example, the CS 240 Utilities provide several exceptions classes that are useful for certain types of errors.
//!
//!@li Class NetworkException is used for network-related exceptions
//!@li Class FileException is used for file-related exceptions
//!@li Class IOException is used for other input/output exceptions
//!@li Class InvalidURLException is used to indicate that a URL is invalid
//!@li Class InvalidArgumentException is used when an invalid parameter is passed to a method
//!@li Class IllegalStateException is used when a method is called at the inappropriate time, or when an object finds itself in a corrupted state 
//!
//!	Each of these error-specific exception classes is a subclass of CS240Exception. Objects of these types can be initialized with an informative message, and they also inherit the GetMessage method from CS240Exception for retrieving the message from the exception object. The following code shows how to use these exception classes.
//!@code
//!void bar()
//!{
//!	// code that might throw many different kinds of exceptions goes here 
//!}
//!
//!void main()
//!{
//!	try
//!	{
//!		bar();
//!	}
//!	catch (NetworkException & e)
//!	{
//!		// handle network exception
//!	}
//!	catch (FileException & e)
//!	{
//!		// handle file exception
//!	}
//!	catch (IOException & e)
//!	{
//!		// handle i/o exception
//!	}
//!	catch (InvalidURLException & e)
//!	{
//!		// handle invalid URL exception
//!	}
//!	catch (InvalidArgumentException & e)
//!	{
//!		// handle invalid argument exception
//!	}
//!	catch (IllegalStateException & e)
//!	{
//!		// handle illegal state exception
//!	}
//!	catch (CS240Exception & e)
//!	{
//!		// handle unknown exception
//!	}
//!}
//!@endcode
//!	Some of the methods on the CS 240 Utilities classes throw the exception types listed above. When calling methods that might throw exceptions, you need to write code to handle the exceptions, or your program will terminate abnormally when exceptions are thrown. You may also throw these exceptions from methods that you write. You are encouraged to create new subclasses of CS240Exception that apply to new kinds of errors that are not covered by the classes listed above. Consult the code for NetworkException, FileException, etc. for examples of how to properly subclass CS240Exception. Of course, any new exception subclasses that you create can have other constructor parameters and methods in addition to those supported by CS240Exception. These subclasses can store any information that needs to be passed from the point where an exception occurs to the point where the exception is handled.

#include <string>

//!@ingroup exception
class CS240Exception
{
public:
	CS240Exception() : message("Unknown Error")
	{
	}

	CS240Exception(const std::string & msg) : message(msg)
	{
	}

	CS240Exception(const CS240Exception & e) : message(e.message)
	{
	}

	virtual ~CS240Exception()
	{
	}

	const std::string & GetMessage()
	{
		return message;
	}

protected:
	std::string message;
};


//!@ingroup exception
class InvalidArgumentException : public CS240Exception
{
public:
	InvalidArgumentException() : CS240Exception("Invalid Argument")
	{
		return;
	}

	InvalidArgumentException(const std::string & msg) : CS240Exception(std::string("Invalid Argument: ") + msg)
	{
		return;
	}
};


//!@ingroup exception
class InvalidURLException : public CS240Exception
{
public:
	InvalidURLException() : CS240Exception("Invalid URL")
	{
	}

	InvalidURLException(const std::string & msg) : CS240Exception(std::string("Invalid URL: ") + msg)
	{
	}
};


//!@ingroup exception
class IllegalStateException : public CS240Exception
{
public:
	IllegalStateException() : CS240Exception("Illegal State")
	{
	}

	IllegalStateException(const std::string & msg) : CS240Exception(std::string("Illegal State: ") + msg)
	{
	}
};


//!@ingroup exception
class IOException : public CS240Exception
{
public:
	IOException() : CS240Exception("I/O Error")
	{
	}

	IOException(const std::string & msg) : CS240Exception(std::string("I/O Error: ") + msg)
	{
	}
};


//!@ingroup exception
class NetworkException : public CS240Exception
{
public:
	NetworkException() : CS240Exception("Network Error")
	{
	}

	NetworkException(const std::string & msg) : CS240Exception(std::string("Network Error: ") + msg)
	{
	}
};


//!@ingroup exception
class FileException : public CS240Exception
{
public:
	FileException() : CS240Exception("File Error")
	{
	}

	FileException(const std::string & msg) : CS240Exception(std::string("File Error: ") + msg)
	{
	}
};


#endif
