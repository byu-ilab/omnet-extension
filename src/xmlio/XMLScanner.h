/*
	filename: XMLScanner.h
	author: Kevin P. Black (C) 2009
	date created: 11.17.09

	Defines the XMLScanner class.
*/

#if !defined( XML_SCANNER_H )
#define XML_SCANNER_H

#include "XMLToken.h"
#include "XMLTag.h"
#include <string>
#include <list>

//------------------------------------------------------------------------------
///@todo make it a more robust xml scanner, but it should be sufficient for chess
///@todo make it check that the tags are balanced
///@todo make the XMLScanner copiable
class XMLScanner {
//public:
//	///Performs Unit Tests on the XMLScanner class.
//	///@param os -- a reference to an ostream to write messages to
//	///@param debug -- a boolean value indicating whether debugging messages
//	///		   should be displayed
//	static bool Test (std::ostream & os, bool debug = false);


//private:
//	///Performs Unit Tests on the XMLScanner class.
//	///@param os -- a reference to an ostream to write messages to
//	///@param debug -- a boolean value indicating whether debugging messages
//	///		   should be displayed
//	static bool TestBasicScan (std::ostream & os, bool debug = false);
//
//
//	///Performs Unit Tests on the XMLScanner class.
//	///@param os -- a reference to an ostream to write messages to
//	///@param debug -- a boolean value indicating whether debugging messages
//	///		   should be displayed
//	static bool TestBasicTagScan (std::ostream & os, bool debug = false);
//
//
//	///Performs Unit Tests on the XMLScanner class.
//	///@param os -- a reference to an ostream to write messages to
//	///@param debug -- a boolean value indicating whether debugging messages
//	///		   should be displayed
//	static bool TestComplexTagScan (std::ostream & os, bool debug = false);
//
//
//	///Performs Unit Tests on the XMLScanner class.
//	///@param os -- a reference to an ostream to write messages to
//	///@param debug -- a boolean value indicating whether debugging messages
//	///		   should be displayed
//	static bool TestComplexScan (std::ostream & os, bool debug = false);


private:
	///The input file stream associated with this scanner
	std::ifstream * in_file_ptr;


	///The "stream" of XMLToken pointers
	std::list<XMLToken *> token_stream;


	///The iterator in the token stream
	std::list<XMLToken *>::iterator stream_iterator;


public:
	///@param filename -- the name of the file to read from
	//XMLScanner (const std::string & filename);

	XMLScanner ();

	~XMLScanner ();


	///@param filename -- the name of the file to read from
	// old->///@return true if the file was successfully read and scanned, otherwise
		///returns false to indicate an error.
	void Scan (const std::string & filename, bool debug = false);


	///@return a pointer to the next token in the token stream, or NULL if
	///there is no next token.
	const XMLToken * NextToken ();


	///@return a pointer to the previous token in the token stream, or NULL
	///if there is no previous token.
	const XMLToken * PreviousToken ();


	///@return true if the token stream is at the beginning of the stream
	bool IsTokenStreamAtBegin ();


	///@return true if the token stream is at the end of the stream
	bool IsTokenStreamAtEnd ();


	///Resets the token stream to the beggining.
	void ResetTokenStreamToBegin ();


	///Resets the token stream to the end.
	void ResetTokenStreamToEnd ();


private:
	///Clears the token stream, closes the associated input file
	///stream and throws an IOException because the xml file is
	///not valid.
	void NotValidXML (const std::string & error_source);


	///Opens the specified file and associates it with this scanner's
	///input file stream.
	///@param filename -- the name of the file to open
	void OpenInputFile (const std::string & filename);


	///Closes this scanner's associated input file stream.
	void CloseInputFile ();


	///@return the next character in the associated input file stream
	///or the null character if the input file stream fails or reaches
	///the end.
	char NextCharacterFromInputFile ();


	///@return the next character in the associated input file stream
	///or the null character if the input file stream fails or
	///reaches the end, without removing the character from the stream.
	char PeekNextCharacterFromInputFile ();


	///@return the next character in the associated input file stream
	///or the null character if the input file stream fails or
	///reaches the end, and removes the character from the stream.
	char GetNextCharacterFromInputFile ();


	///Clears the token stream (deletes the XMLTokens).
	void ClearTokenStream ();


	///Checks if the tags in the token stream are balanced.
	///@return true if the tags are balanced and false otherwise
	bool AreTagsBalanced ();


	///@param ch -- the character to check
	///@return true if the character is a starting character for a name
	bool IsNameStartChar (char ch);


	///@param ch -- the character to check
	///@return true if the character is a name character
	bool IsNameChar (char ch);


	///@param ch -- the character to check
	///@return true if the character is a quote mark
	bool IsQuote (char ch);


	///@param ch -- the character to check
	///@return true if the character is one of the standard xml delimiters
	///whitespace, &, <, >, /, =
	bool IsStandardDelim (char ch);


	///Skips the next chunk of whitespace in the associate file stream.
	void SkipWhiteSpace ();


	///@param token_ptr -- a pointer to the XMLToken to be added
	///                    to the token stream
	void AddToStream (XMLToken * token_ptr);


	///Extracts an XMLTag from the associated input file stream and
	///adds it to the token stream.
	///@param debug -- a boolean value indicating whether debugging messages
	///		   should be displayed
	void ExtractTag (bool debug = false);


	///Extracts a tag attribute from the associated input file stream.
	///Assumes that the first character read is the starting character
	///of the attribute.
	///@param tag_ptr -- a pointer to the XMLTag to add the attribute to
	///@param debug -- a boolean value indicating whether debugging messages
	///		   should be displayed
	void ExtractTagAttribute (XMLTag * tag_ptr, bool debug = false);


	///Extracts an XMLEntity from the associated input file stream
	///and adds it to the token stream.
	///@param debug -- a boolean value indicating whether debugging messages
	///		   should be displayed
	void ExtractEntity (bool debug = false);


	///Extracts an XMLText from the associated input file stream
	///and adds it to the token stream.
	///@param debug -- a boolean value indicating whether debugging messages
	///		   should be displayed
	void ExtractText (bool debug = false);


	///Extracts the next name token from the associated file stream.
	///Assumes that the first character read will be the first
	///character of the name.
	///@param debug -- a boolean value indicating whether debugging messages
	///		   should be displayed
	///@return the next name token from the associated file stream.
	std::string ExtractName (bool debug = false);


	///Extracts the next string token from the associated file stream.
	///Assumes that the first character read will be a valid name
	///character or perhaps a quote mark.  Will extract characters
	///until the specified delimiter or any of the standard delimiters.
	///@param extra_delim -- the character to read to
	///@param include_quotes -- a Boolean value indicating whether
	///                         quotes should be extracted or not
	///@param debug -- a boolean value indicating whether debugging messages
	///		   should be displayed
	std::string ExtractStringUntil ( char extra_delim, bool include_quotes,
					 bool debug = false );
};

#endif
