/*
	filename: XMLToken.h
	author: Kevin P. Black (C) 2009
	date created: 11.17.09

	Defines the XMLToken class.
*/

#if !defined( XML_TOKEN_H )
#define XML_TOKEN_H

#include <string>
#include "XMLTokenType.h"
//#include "UnitTest.h"

//------------------------------------------------------------------------------

class XMLToken {
public:
	///Performs Unit Tests on the XMLToken class.
	///@param os -- a reference to an ostream to write messages to
	///@param debug -- a boolean value indicating whether debugging messages
	///		   should be displayed
//	static bool Test (std::ostream & os, bool debug = false);


private:
	///The content of the token
	std::string my_content;


	///The type of the token.
	XMLTokenType my_type;


public:
	///Constructs a generic xml token.
	///@param content -- the content that this XMLToken should contain.
	XMLToken (const std::string & content, XMLTokenType type = generic);


	///@param other -- the XMLToken to copy.
	//XMLToken (const XMLToken & other);


	///@param other -- the XMLToken to copy.
	//XMLToken & operator = (const XMLToken & other);


	virtual ~XMLToken ();


	///@param content -- the content that this XMLToken should contain.
	void SetContent (const std::string & content);


	///@return the content of this XMLToken.
	virtual std::string GetContent () const;


	///@return the type of this XMLToken.
	XMLTokenType GetType () const;


protected:
	///@param type -- the new type of this token, only for subclass copying
	///convenience
	void SetType (XMLTokenType type);


private:
	///Preconditions: the member fields are properly initialized
	///@param other -- the XMLToken to be copied.
	//void Copy (const XMLToken & other);
};

#endif
