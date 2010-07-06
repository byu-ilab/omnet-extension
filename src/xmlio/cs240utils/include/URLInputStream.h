#ifndef URLINPUTSTREAM_H
#define URLINPUTSTREAM_H

#include <string>
#include "InputStream.h"

//!@ingroup io
//!InputStream that can handle both file and http url's.
class URLInputStream : public InputStream
{
	
	public:
		//!@param url A valid URL using the file: or http: scheme
		URLInputStream(const std::string & url);
		
		virtual ~URLInputStream();
		
		
		
		//!@return The next byte of data from the document without advancing the stream.
		//!throws IllegalStateException - If the stream is closed
		//!throws IllegalStateException - If the last byte has already been read from the stream
		//!throws FileException, NetworkException, IllegalStateException - Implementation Specific
		virtual char Peek();
		
		//!@return The next byte of data from the document.
		//!throws IllegalStateException - If the stream is closed
		//!throws IllegalStateException - If the last byte has already been read from the stream
		//!throws FileException, NetworkException, IllegalStateException - Implementation Specific
		virtual char Read();

		//!Closes the stream if it is not already closed. All system resources used by the stream are released.
		virtual void Close();

		//!@return true if the stream is open, and false if it is closed.
		virtual bool IsOpen()const;

		//!@return true if the end of the stream has been reached, and false if there are still more bytes to be read.
		virtual bool IsDone()const;

		virtual std::string GetLocation() const;

		
	private:
		InputStream * mStream;
		
		//!The ::StreamFactory is used to open an InputStream that can be used to read the contents of a web document.
		//!It takes the URL of the document to be acccessed, and returns an InputStream object that can be used to read
		//!the contents of the document. The URL can be either an HTTP URL or a file URL.
		//!Examples are "http://www.cnn.com/index.html" and "file:/public_html/index.html".
		//!
		//!
		//!The InputStream object returned by ::StreamFactory provides methods for reading the data stored in the web document,
		//!and to close the stream when the program has finished reading the document's data. The following code fragment shows 
		//!how to read a web document and print its contents to standard output.
		//!@code
		//!#include "InputStream.h"
		//!     
		//!InputStream * doc = StreamFactory("http://www.cnn.com/index.html");
		//!
		//!while (!doc->IsDone()) {
		//!	char c = doc->Read();
		//!	cout << c;
		//!}
		//!
		//!doc->Close();
		//!delete doc;
		//!@endcode
		//!
		//!
		//!@param url - URL of the document to be downloaded as its only parameter. The file must be either a file URL or an HTTP URL. The caller must call the Close method on the returned InputStream when they are finished reading data from the document, and then delete the object.
		//!@return An open InputStream object that can be used to read the contents of the document
		//!@return Transfers ownership of InputStream
		//!@throws InvalidURLException, FileException, NetworkException, IllegalStateException. 
		
		static InputStream * StreamFactory(const std::string & url);
				
		
		
	
	
};



#endif 
