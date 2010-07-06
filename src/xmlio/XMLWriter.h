/*
	filename: XMLWriter.h
	author: Kevin P. Black (C) 2009
	date created: 11.17.09

	Defines the XMLWriter class.
*/

#if !defined( XML_WRITER_H )
#define XML_WRITER_H

#include "XMLToken.h"
#include <string>
#include <fstream>

//------------------------------------------------------------------------------

///@brief Facilitates writing xml files.
///@todo Add attribute format checking (i.e. double quotes)
///@todo Verify the xml file when it is closed or as it is being written
class XMLWriter {
//public:
//	///Performs Unit Tests on the XMLWriter class.
//	///@param os -- a reference to an ostream to write messages to
//	///@param debug -- a boolean value indicating whether debugging messages
//	///		   should be displayed
//	static bool Test (std::ostream & os, bool debug = false);
//
//
//private:
//	///@param os -- a reference to an ostream to write messages to
//	///@param debug -- a boolean value indicating whether debugging messages
//	///		   should be displayed
//	static bool TestStringWrite (std::ostream & os, bool debug = false);
//
//
//	///@param os -- a reference to an ostream to write messages to
//	///@param debug -- a boolean value indicating whether debugging messages
//	///		   should be displayed
//	static bool TestTokenWrite (std::ostream & os, bool debug = false);


private:
	///Indicates if there is an open file associated with this XMLWriter
	bool file_is_open;


	///The output file stream associated with the writer.
	std::ofstream file_to_write;


public:
	///Constructs an XMLWriter and associates it with the specified file.
	///Opens the file to write to; will overwrite previous file contents.
	///@param filename -- the name of the file to write to.
	XMLWriter (const std::string filename);


	///Encodes the specified string content to xml (i.e. entities) and
	///writes it to the associated file stream.
	///@param content -- the string to write to the file
	void Write (const std::string & content);


	///Writes the contents of the specified XMLToken to the associated
	///file.
	///@param token -- the XMLToken to be written to the file.
	void Write (const XMLToken & token);


	///Writes a space to the associated file stream.
	void WriteSpace ();


	///Writes a tab to the associated file stream
	void WriteTab ();


	///Writes a new line to the associated file stream
	void WriteNewLine ();


	///Writes a new line to the associated file stream, and then the
	///specified number of tabs.
	///@param indent -- the number of tabs to be written, the default
	///                 is zero
	void Align (int indent = 0);


	///Writes an xml opening tag to the specified file with the specified
	///tag contents (will braket it).
	///@param tag_content -- the contents of the tag to be written.
	void WriteOpenTag (const std::string & tag_content);


	///Writes an xml closing tag to the specified file with the specified
	///tag name (will braket it).
	///@param tag_name -- the name of the tag to be written.
	void WriteCloseTag (const std::string & tag_name);


	///Writes a self closing tag to the specified file with the specified
	///tag content (will braket it).
	///@param tag_contetn -- the content of the tag to be written.
	void WriteSelfClosingTag (const std::string & tag_content);


	///@param filename -- the name of the file to be opened and associated
	///                   with this XMLWriter for writing to.
	void Open (const std::string & filename);


	///@return true if the associate output filestream of this XMLWriter
	///is open
	bool IsOpen ();


	///Closes this XMLWriter's associated file output stream.
	void Close ();


private:
	///Checks if the file is open and ready to be written to
	///@throws an IllegalStateException if the file is not open
	void CheckOpenState ();


	///Checks if the associated filestream in in an error state,
	///if it is then it sets the file_is_open flag to false.
	void ValidateState ();
};

#endif
