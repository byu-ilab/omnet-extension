#ifndef INPUT_STREAM_H
#define INPUT_STREAM_H

#include <string>


//!@defgroup io IO: Local and Remote
//!The Local/Remote IO Module is a set of classes that make accessing local files and
//!remote files (through HTTP) transparent.
//!They provide support for reading one byte at a time (InputStream::Read), one character 
//!look ahead (InputStream::Peek) and for retrieving
//!the absolute location of the inpout source (InputStream::GetLocation)
//!
//!The URLInputStream class takes care of creating the correct type of input stream 
//!(FileInputStream or HTTPInputStream)for you.
//!For Example, the following code will print all data from a URL, wether it is
//!a file:// or http:// URL.
//!@code
//!
//!	URLInputStream stream (url);
//!  
//! while(! stream).IsDone()) 
//!		std::cout << stream.Read() << std::endl;
//!
//!@endcode
//!
//!There are many kinds of error conditions that can occur when a program 
//!accesses documents on the web. The methods on the web access classes 
//!throw exceptions when errors occur. Examples of exceptions that might be thrown are:
//!InvalidURLException, FileException, NetworkException, and IllegalStateException.
//!Your code must be prepared to handle these exceptions when they occur, or your 
//!program will terminate abnormally.
//!
//!The following is a more in depth example of using the URLInputSteam class.
//!@include printer.cpp

//!@example printer.cpp
//!An example for ::URLInputStream of the @link io IO @endlink module.


//!@ingroup io
//!InputStream is an abstract interface for reading data from a stream. 
class InputStream {
public:
	virtual ~InputStream() {}

	
	//!@return The next byte of data from the document without advancing the stream.
	//!throws IllegalStateException - If the stream is closed
	//!throws IllegalStateException - If the last byte has already been read from the stream
	//!throws FileException, NetworkException, IllegalStateException - Implementation Specific
	virtual char Peek() = 0;
	
	//!@return The next byte of data from the document and advances the stream.
	//!throws IllegalStateException - If the stream is closed
	//!throws IllegalStateException - If the last byte has already been read from the stream
	//!throws FileException, NetworkException, IllegalStateException - Implementation Specific
	virtual char Read() = 0;

	//!Closes the stream if it is not already closed. All system resources used by the stream are released.
	virtual void Close() = 0;

	//!@return true if the stream is open, and false if it is closed.
	virtual bool IsOpen() const = 0;

	//!@return true if the end of the stream has been reached, and false if there are still more bytes to be read.
	virtual bool IsDone() const = 0;

	//!@return An identifier for the source of this input stream.
	virtual std::string GetLocation() const = 0;
};


#endif
