/*
	filename: XMLText.h
	author: Kevin P. Black (C) 2009
	date created: 11.17.09

	Defines the XMLText class.  Inherits from XMLToken.
*/

#if !defined( XML_TEXT_H )
#define XML_TEXT_H

#include <string>
#include "XMLToken.h"
#include "XMLTokenType.h"

//------------------------------------------------------------------------------

class XMLText : public XMLToken {
//public:
//	///Performs Unit Tests on the XMLText class.
//	///@param os -- a reference to an ostream to write messages to
//	///@param debug -- a boolean value indicating whether debugging messages
//	///		   should be displayed
//	static bool Test (std::ostream & os, bool debug = false);


public:
	///Constructs a text xml token.
	///@param content -- the content that this XMLText should contain.
	XMLText (const std::string & content);


	///@param other -- the XMLText to copy.
	XMLText (const XMLToken & other);


	virtual ~XMLText ();


	///@param other -- the XMLText to copy.
	XMLText & operator = (const XMLToken & other);


private:
	///Given the specified XMLTokenType sets this XMLText's type to
	///text or generic
	///@param type -- the type value to be checked
	void SetType (XMLTokenType type);
};

#endif
