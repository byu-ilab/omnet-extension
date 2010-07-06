/*
	filename: XMLTag.h
	author: Kevin P. Black (C) 2009
	date created: 11.17.09

	Defines the XMLTag class.  Inherits from XMLToken.
*/

#if !defined( XML_TAG_H )
#define XML_TAG_H

#include "XMLToken.h"
#include "XMLTokenType.h"
#include "XMLTagType.h"
#include <string>
#include <map>
#include <iostream>

//------------------------------------------------------------------------------
///@todo validate input data
class XMLTag : public XMLToken {
//public:
//	///Performs Unit Tests on the XMLTag class.
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
//	static bool TestConstructorsAndOperators (std::ostream & os, bool debug = false );
//
//
//	///@param os -- a reference to an ostream to write messages to
//	///@param debug -- a boolean value indicating whether debugging messages
//	///		   should be displayed
//	static bool TestAttributeOperations (std::ostream & os, bool debug = false);
//
//
//	///@param os -- a reference to an ostream to write messages to
//	///@param debug -- a boolean value indicating whether debugging messages
//	///		   should be displayed
//	static bool TestTagTypeEffects (std::ostream & os, bool debug = false);


private:
	///The mapping of attribute and value pairs.
	std::map<std::string, std::string> attrib_value_map;


	///The type of tag
	XMLTagType my_tag_type;


public:
	///Constructs a tag xml token.
	///Precondition: the content specifies a valid tag_name, or tag
	///content.  No verification will be performed on the data.
	///@param content -- the content that this XMLTag should contain.
	XMLTag (const std::string & tag_name, XMLTagType tag_type = xmltag_open);


	///@todo allow for casting to XMLTag
	///@param other -- the XMLToken to copy.
	XMLTag (const XMLToken & other);


	virtual ~XMLTag ();


	///@param other -- the XMLToken to copy
	XMLTag & operator = (const XMLToken & other);


	///@return the content of this XMLTag
	virtual std::string GetContent () const;


	///@param attribute -- a string with the attribute name to be accessed
	///@return a string with the value of the specified attribute, which
	///may be empty if the attribute is not defined or is empty.
	std::string GetAttributeValue (const std::string & attribute) const;


	///@param attribute -- the attribute name
	///@param value -- the value of the attribute
	void DefineAttribute (const std::string & attribute,
				const std::string & value);


	///@param attribute -- the attribute name
	///@return the value of the removed attribute
	std::string RemoveAttribute (const std::string & attribute);


	///@return the name of this tag
	std::string GetTagName () const;


	///@return the tag type of this XMLTag
	XMLTagType GetTagType () const;


	///Sets the type of this XMLTag
	///@param tag_type -- a value of the XMLTagType enum indicating
	///                   the type of this tag
	void SetTagType (XMLTagType tag_type = xmltag_open);


	///@return true if the contents of this XMLTag can be manipulated
	///and false if they can not.  Should only return true if the type
	///of this XMLTag is tag.  Note that the contents of the tag may
	///still be changed by using the SetContent function even if this
	///function returns false.
	bool IsModifiable () const;


protected:
	///Extracts the attribute value pairs specified in the content
	//void ExtractAttributeValuePairs ();


private:
	///Given the specified XMLTokenType sets this XMLTag's type to
	///tag or generic
	///@param type -- the type value to be checked
	void SetType (XMLTokenType type);


	///@param other -- the XMLToken to be copied
	void Copy (const XMLToken & other);
};

#endif
