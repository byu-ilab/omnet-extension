//------------------------------------------------------------------------------
/*
	filename: XMLTag.cpp
	author: Kevin P. Black (C) 2009
	date created: 11.23.09

	Implements the XMLTag class defined in XMLTag.h
*/
//------------------------------------------------------------------------------
//	INCLUSIONS

#include "XMLTag.h"
#include "XMLTokenType.h"
#include "XMLConstants.h"
#include "XMLTagType.h"
#include <map>
#include <utility>
#include <sstream>

#include "CS240Exception.h"

#include "Debug.h"
#include "UnitTest.h"
#include <iostream>
using namespace std;

//------------------------------------------------------------------------------
//	CONSTANTS
const int CLOSE_TAG_INDEX = 1;

//------------------------------------------------------------------------------
//	STATIC FUNCTIONS

//bool XMLTag::Test (ostream & os, bool debug) {
//	bool success = true;
//
//	TEST( TestConstructorsAndOperators(os, debug) );
//
//	TEST( TestAttributeOperations(os, debug) );
//
//	TEST( TestTagTypeEffects(os, debug) );
//
//	os << "\tXMLTag tests: " << ( success ? "OK" : "FAIL" ) << endl;
//	return success;
//}
//
//
//bool XMLTag::TestConstructorsAndOperators (std::ostream & os, bool debug) {
//	bool success = true;
//
//	// Test the constructors
//	string tagname_firstname("firstname");
//	string tagname_lastname("lastname");
//	string tagcontent_firstname("<firstname>");
//	string tagcontent_lastname("<lastname>");
//
//	XMLTag t_1(tagname_firstname);
//
//	DEBUG("tag t_1 content: "<<t_1.GetContent());
//	TEST( t_1.GetType() == tag );
//	TEST( t_1.GetContent().compare(tagcontent_firstname) == 0 );
//	TEST( t_1.GetTagName().compare(tagname_firstname) == 0 );
//
//	XMLTag t_2(t_1);
//
//	DEBUG("tag t_2 content: "<<t_2.GetContent());
//	TEST( t_2.GetContent().compare(tagcontent_firstname) == 0 );
//	TEST( t_2.GetType() == tag );
//
//	// Test the uniqueness of XMLTags
//	t_2.SetContent(tagname_lastname);
//
//	DEBUG("tag t_2 content: "<<t_2.GetContent());
//	TEST( t_2.GetContent().compare(tagcontent_lastname) == 0 );
//
//	DEBUG("tag t_1 content: "<<t_1.GetContent());
//	TEST( t_1.GetContent().compare(tagcontent_firstname) == 0 ); //notice it is called on t_1
//
//	// Test the assignment operator
//	t_1 = t_2;
//
//	DEBUG("tag t_1 content: "<<t_1.GetContent());
//	TEST( t_1.GetContent().compare(tagcontent_lastname) == 0 );
//	TEST( t_1.GetType() == tag );
//
//	// Test the creation of an XMLTag object without a type of tag
//	XMLToken gt_1(tagname_firstname, generic);
//
//	t_1 = gt_1;
//
//	TEST( t_1.GetContent().compare(tagname_firstname) == 0 );
//	TEST( t_1.GetType() == generic );
//	TEST( t_1.IsModifiable() == false );
//
//	XMLTag t_3(gt_1);
//
//	TEST( t_3.GetContent().compare(tagname_firstname) == 0 );
//	TEST( t_3.GetType() == generic );
//	TEST( t_3.IsModifiable() == false );
//
//	return success;
//}
//
//
//bool XMLTag::TestAttributeOperations (ostream & os, bool debug) {
//	bool success = true;
//
//	string tagname("xmltag");
//
//	string attrib_1("author");
//	string attrib_2("date");
//
//	string value_1("kpbinc");
//	string value_2("11.23.09");
//
//	string tag_content_2(tagname+" "+attrib_1+"=\""+value_1+"\"");
//	string tag_content_3(tagname+" "+attrib_1+"=\""+value_1+"\""
//					+" "+attrib_2+"=\""+value_2+"\"");
//	string tag_content_4(tagname+" "+attrib_2+"=\""+value_2+"\"");
//
//	string expected_tag_1("<"+tagname+">");
//	string expected_tag_2("<"+tag_content_2+">");
//	string expected_tag_3("<"+tag_content_3+">");
//	string expected_tag_4("<"+tag_content_4+">");
//
//	XMLTag tag_1(tagname);
//
//	TEST( tag_1.GetType() == tag );
//	TEST( tag_1.GetContent().compare(expected_tag_1) == 0 );
//
//	tag_1.DefineAttribute(attrib_1, value_1);
//
//	TEST( tag_1.GetAttributeValue(attrib_1).compare(value_1) == 0 );
//	TEST( tag_1.GetContent().compare(expected_tag_2) == 0 );
//
//	tag_1.DefineAttribute(attrib_2, value_2);
//
//	TEST( tag_1.GetAttributeValue(attrib_2).compare(value_2) == 0 );
//	TEST( tag_1.GetContent().compare(expected_tag_3) == 0 );
//
//	tag_1.RemoveAttribute(attrib_1);
//
//	TEST( tag_1.GetAttributeValue(attrib_1).compare("") == 0 );
//	TEST( tag_1.GetContent().compare(expected_tag_4) == 0 );
//
//	tag_1.RemoveAttribute(attrib_2);
//
//	TEST( tag_1.GetAttributeValue(attrib_2).compare("") == 0 );
//	TEST( tag_1.GetContent().compare(expected_tag_1) == 0 );
//
//	// Test the effects of copying
//	XMLTag tag_2(tag_1);
//
//	TEST( tag_2.GetContent().compare(expected_tag_1) == 0 );
//
//	tag_2.DefineAttribute(attrib_1, value_1);
//
//	TEST( tag_2.GetAttributeValue(attrib_1).compare(value_1) == 0 );
//	TEST( tag_2.GetContent().compare(expected_tag_2) == 0 );
//
//	string tagname_2("xmlsubtag");
//	string expected_tag_5("<"+tagname_2+" "+attrib_1+"=\""+value_1+"\">");
//
//	tag_2.SetContent(tagname_2);
//
//	TEST( tag_2.GetContent().compare(expected_tag_5) == 0 );
//
//	// Test the effects of casting
//	XMLToken token_1 = tag_1;
//
//	TEST( token_1.GetContent().compare(tagname) == 0 );
//
//	XMLTag tag_3 = token_1;
//
//	TEST( tag_3.GetType() == tag );
//	TEST( tag_3.GetContent().compare(expected_tag_1) == 0 );
//
//	tag_3.DefineAttribute(attrib_1, value_1);
//
//	TEST( tag_3.GetContent().compare(expected_tag_2) == 0 );
//
//	// Test the effects of using pointers
//	XMLToken * token_ptr_1 = &tag_1;
//
//	TEST( token_ptr_1->GetType() == tag );
//	TEST( token_ptr_1->GetContent().compare(expected_tag_1) == 0 );
//
//	XMLTag * tag_ptr_1 = (XMLTag *) token_ptr_1;
//	tag_ptr_1->DefineAttribute(attrib_1, value_1);
//
//	TEST( token_ptr_1->GetContent().compare(expected_tag_2) == 0 );
//
//	return success;
//}
//
//bool XMLTag::TestTagTypeEffects (std::ostream & os, bool debug) {
//	bool success = true;
//
//	string tagname("xmltag");
//
//	string attrib_1("author");
//
//	string value_1("kpbinc");
//
//	string tag_with_attrib(tagname+" "+attrib_1+"=\""+value_1+"\"");
//
//	string expected_open_tag_1("<"+tagname+">");
//	string expected_open_tag_2("<"+tag_with_attrib+">");
//	string expected_close_tag_1("</"+tagname+">");
//	string expected_self_close_tag_1("<"+tag_with_attrib+"/>");
//
//	XMLTag tag_1(tagname);
//
//	TEST( tag_1.GetContent().compare(expected_open_tag_1) == 0 );
//
//	tag_1.DefineAttribute(attrib_1, value_1);
//
//	TEST( tag_1.GetContent().compare(expected_open_tag_2) == 0 );
//
//	tag_1.SetTagType(xmltag_close);
//
//	TEST( tag_1.GetContent().compare(expected_close_tag_1) == 0 );
//
//	tag_1.SetTagType(xmltag_self_close);
//
//	TEST( tag_1.GetContent().compare(expected_self_close_tag_1) == 0 );
//
//	return success;
//}


//------------------------------------------------------------------------------
//	PUBLIC FUNCTIONS

XMLTag::XMLTag (const std::string & tag_name, XMLTagType tag_type)
	: XMLToken(tag_name, tag), attrib_value_map(), my_tag_type(tag_type) {
	//FormatTagContent();
	//ExtractAttributeValuePairs();
}


XMLTag::~XMLTag () {
	attrib_value_map.clear();
}


XMLTag::XMLTag (const XMLToken & other)
	: XMLToken(other), attrib_value_map(), my_tag_type(xmltag_open) {
	bool debug = false;
	DEBUG("XMLTag: generic token copy constructor called");
	Copy(other);
	//FormatTagContent();
	//ExtractAttributeValuePairs();
}


XMLTag & XMLTag::operator = (const XMLToken & other) {
	bool debug = false;
	DEBUG("XMLTag: generic token assignment operator called");
	if ( this != &other ) {
		Copy(other);
		//FormatTagContent();
		//ExtractAttributeValuePairs();
	}
	return ( *this );
}


string XMLTag::GetAttributeValue (const std::string & attribute) const {
	if ( GetType() != tag || GetTagType() == xmltag_close )
		return string();

	// It is expensive to entirely copy the object, but it ensures that this
	// function is constant.
	XMLTag copy(*this);

	map<string, string>::iterator attrib_loc_iter = copy.attrib_value_map.find(attribute);

	string value;
	if ( attrib_loc_iter != copy.attrib_value_map.end() ) {
		value = attrib_loc_iter->second;
	}
	return value;

}


void XMLTag::DefineAttribute (const std::string & attribute,
				const std::string & value) {
	if ( GetType() != tag || GetTagType() == xmltag_close )
		return;

	attrib_value_map.insert( make_pair(attribute, value) );
}


string XMLTag::RemoveAttribute (const std::string & attribute) {
	if ( GetType() != tag || GetTagType() == xmltag_close )
		return string();

	string value = GetAttributeValue(attribute);
	attrib_value_map.erase(attribute);
	return ( value );
}


string XMLTag::GetContent () const {
	if ( GetType() != tag )
		return ( XMLToken::GetContent() );

	stringstream content;
	content << TAG_BEGIN;

	if ( GetTagType() == xmltag_close ) {
		content << TAG_CLOSE << XMLToken::GetContent() << TAG_END;
		return ( content.str() );
	}

	//add the tag name
	content << XMLToken::GetContent();

	//add the attributes

	// It is expensive to entirely copy the object, but it is necessary
	// in order to have this function be considered constant and be
	// polymorphic with XMLToken::GetContent
	XMLTag copy(*this);
	map<string, string>::iterator map_iter = copy.attrib_value_map.begin();

	while ( map_iter != copy.attrib_value_map.end() ) {
		content << SPACE << map_iter->first << EQUALS_SIGN <<
			DBL_QUOTES << map_iter->second << DBL_QUOTES;
		map_iter++;
	}

	if ( GetTagType() == xmltag_self_close ) {
		content << TAG_CLOSE;
	}
	content << TAG_END;
	return ( content.str() );
}

string XMLTag::GetTagName () const {
	return ( XMLToken::GetContent() );
}


void XMLTag::SetTagType (XMLTagType tag_type) {
	my_tag_type = tag_type;
}


XMLTagType XMLTag::GetTagType () const {
	return ( my_tag_type );
}


bool XMLTag::IsModifiable () const {
	return ( GetType() == tag ? true : false );
}


//------------------------------------------------------------------------------
//	PROTECTED FUNCTIONS
/*
void XMLTag::FormatTagContent () {
	if ( GetType() != tag )
		return;

	string content = XMLToken::GetContent();

	int tag_name_end_index = content.find_first_of( SPACE + TAG_END );

	string name = content.substr(1, tag_name_end_index);
}

void XMLTag::ExtractAttributeValuePairs () {
	if ( GetType() != tag )
		return;


}
*/


//------------------------------------------------------------------------------
//	PRIVATE FUNCTIONS

void XMLTag::Copy (const XMLToken & other) {
	SetContent( other.GetContent() );
	SetType( other.GetType() );
	SetTagType(xmltag_open);

	if ( GetType() == tag ) {
		string content = GetContent();
		int close_delim_index = content.find(TAG_CLOSE);

		if ( close_delim_index ==  CLOSE_TAG_INDEX ) {
			SetTagType(xmltag_close);
		}
		else if ( close_delim_index == (int) content.size() - CLOSE_TAG_INDEX ) {
			SetTagType(xmltag_self_close);
		}
	}
}


void XMLTag::SetType (XMLTokenType type ) {
	if ( type != tag ) {
		XMLToken::SetType( generic );
	}
	else {
		XMLToken::SetType( tag );
	}
}

