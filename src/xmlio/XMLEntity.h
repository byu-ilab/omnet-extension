/*
	filename: XMLEntity.h
	author: Kevin P. Black (C) 2009
	date created: 11.17.09

	Defines the XMLEntity class.  Inherets from XMLToken.
*/

#if !defined( XML_ENTITY_H )
#define XML_ENTITY_H

#include <string>
#include "XMLToken.h"
#include "XMLTokenType.h"

//------------------------------------------------------------------------------
///@todo limit the possible input to just valid xml entity characters?
class XMLEntity : public XMLToken {
//public:
//	///Performs Unit Tests on the XMLEntity class.
//	///@param os -- a reference to an ostream to write messages to
//	///@param debug -- a boolean value indicating whether debugging messages
//	///		   should be displayed
//	static bool Test (std::ostream & os, bool debug = false);


public:
	///Constructs an entity xml token.  Any xml entity characters in
	///the content will be converted to the appropriate xml entity.
	///@param content -- the content that this XMLEntity should contain.
	XMLEntity (const std::string & content);


	///@param other -- the XMLEntity to copy.
	XMLEntity (const XMLToken & other);


	virtual ~XMLEntity ();


	///@param other -- the XMLEntity to copy.
	XMLEntity & operator = (const XMLToken & other);


	///Returns the content of this XMLEntity with the xml entities
	///properly encoded as long as the type of this XMLEntity is
	///entity, otherwise, just returns the plain content
	std::string GetContentEncoded () const;

private:
	///Given the specified XMLTokenType sets this XMLEntity's type to
	///entity or generic
	///@param type -- the type value to be checked
	void SetType (XMLTokenType type);


	///Encodes the content of this XMLEntity to xml if its type is
	///entity
	//void XMLEntity::ConvertContentToXMLEntity ();
};

#endif
