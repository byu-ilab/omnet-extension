//------------------------------------------------------------------------------
/*
	filename: XMLText.cpp
	author: Kevin P. Black (C) 2009
	date created: 11.23.09

	Implements the XMLText class defined in XMLText.h
*/
//------------------------------------------------------------------------------
//	INCLUSIONS

#include "XMLText.h"
#include "XMLTokenType.h"

#include "Debug.h"
#include "UnitTest.h"
#include <iostream>
using namespace std;

//------------------------------------------------------------------------------
//	CONSTANTS

//------------------------------------------------------------------------------
//	STATIC FUNCTIONS

//bool XMLText::Test (ostream & os, bool debug) {
//	bool success = true;
//
//	// Test the constructors
//	string firstname("Kevin");
//	string lastname("Black");
//	XMLText t_1(firstname);
//
//	TEST( t_1.GetContent().compare(firstname) == 0 );
//	TEST( t_1.GetType() == text );
//
//	XMLText t_2(t_1);
//
//	TEST( t_2.GetContent().compare(firstname) == 0 );
//	TEST( t_1.GetType() == text );
//
//	// Test the uniqueness of XMLTexts
//	t_2.SetContent(lastname);
//
//	TEST( t_2.GetContent().compare(lastname) == 0 );
//	TEST( t_1.GetContent().compare(firstname) == 0 ); //notice it is called on t_1
//
//	// Test the assignment operator
//	t_1 = t_2;
//
//	TEST( t_1.GetContent().compare(lastname) == 0 );
//	TEST( t_1.GetType() == text );
//
//	// Test the creation of an XMLText object without a type of text
//	XMLToken gt_1(firstname, generic);
//
//	t_1 = gt_1;
//
//	TEST( t_1.GetContent().compare(firstname) == 0 );
//	TEST( t_1.GetType() == generic );
//
//	XMLText t_3(gt_1);
//
//	TEST( t_3.GetContent().compare(firstname) == 0 );
//	TEST( t_3.GetType() == generic );
//
//
//	os << "\tXMLText tests: " << ( success ? "OK" : "FAIL" ) << endl;
//	return success;
//}

//------------------------------------------------------------------------------
//	PUBLIC FUNCTIONS

XMLText::XMLText (const std::string & content)
	: XMLToken(content, text) {
}



XMLText::XMLText (const XMLToken & other)
	: XMLToken(other) {
	bool debug = false;
	DEBUG("XMLText: generic token copy constructor called");
	SetType(other.GetType());
}


XMLText::~XMLText () {
}



XMLText & XMLText::operator = (const XMLToken & other) {
	bool debug = false;
	DEBUG("XMLText: generic token assignment operator called");
	if ( this != &other ) {
		SetContent( other.GetContent() );
		SetType( other.GetType() );
	}
	return ( *this );
}


/*
void XMLText::SetContent (const std::string & content) {
	my_content = content;
}



std::string XMLText::GetContent () {
	return ( my_content );
}



XMLTokenType XMLText::GetType () {
	return ( my_type );
}
*/

//------------------------------------------------------------------------------
//	PROTECTED FUNCTIONS
/*
void XMLText::SetType (XMLTokenType type) {
	my_type = type;
}
*/
//------------------------------------------------------------------------------
//	PRIVATE FUNCTIONS

void XMLText::SetType (XMLTokenType type ) {//Copy (const XMLText & other) {
	//SetContent( other.GetContent() );
	if ( type != text ) {
		XMLToken::SetType( generic );
	}
	else {
		XMLToken::SetType( text );
	}
}
