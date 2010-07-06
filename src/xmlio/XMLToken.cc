//------------------------------------------------------------------------------
/*
	filename: XMLToken.cpp
	author: Kevin P. Black (C) 2009
	date created: 11.23.09

	Implements the XMLToken class defined in XMLToken.h
*/
//------------------------------------------------------------------------------
//	INCLUSIONS

#include "XMLToken.h"
#include "XMLTokenType.h"

#include "Debug.h"
#include "UnitTest.h"
#include <iostream>
using namespace std;

//------------------------------------------------------------------------------
//	CONSTANTS

//------------------------------------------------------------------------------
//	STATIC FUNCTIONS

//bool XMLToken::Test (ostream & os, bool debug) {
//	bool success = true;
//
//	// Test the constructors
//	string firstname("Kevin");
//	string lastname("Black");
//	XMLToken t_1(firstname, generic);
//
//	TEST( t_1.GetContent().compare(firstname) == 0 );
//	TEST( t_1.GetType() == generic );
//
//	XMLToken t_2(t_1);
//
//	TEST( t_2.GetContent().compare(firstname) == 0 );
//	TEST( t_1.GetType() == generic );
//
//	// Test the uniqueness of XMLTokens
//	t_2.SetContent(lastname);
//
//	TEST( t_2.GetContent().compare(lastname) == 0 );
//	TEST( t_1.GetContent().compare(firstname) == 0 ); //notice it is called on t_1
//
//	// Test the assignment operator
//	t_1 = t_2;
//
//	TEST( t_1.GetContent().compare(lastname) == 0 );
//
//
//	os << "\tXMLToken tests: " << ( success ? "OK" : "FAIL" ) << endl;
//	return success;
//}

//------------------------------------------------------------------------------
//	PUBLIC FUNCTIONS

XMLToken::XMLToken (const std::string & content, XMLTokenType type)
	: my_content(content), my_type(type) {
}


XMLToken::~XMLToken () {
}



/*XMLToken::XMLToken (const XMLToken & other)
	: my_content(), my_type(generic) {
	Copy(other);
}



XMLToken & XMLToken::operator = (const XMLToken & other) {
	if ( this != &other ) {
		Copy(other);
	}
	return ( *this );
}
*/


void XMLToken::SetContent (const std::string & content) {
	my_content = content;
}



std::string XMLToken::GetContent () const {
	return ( my_content );
}



XMLTokenType XMLToken::GetType () const {
	return ( my_type );
}


//------------------------------------------------------------------------------
//	PROTECTED FUNCTIONS

void XMLToken::SetType (XMLTokenType type) {
	my_type = type;
}

//------------------------------------------------------------------------------
//	PRIVATE FUNCTIONS
/*
void Copy (const XMLToken & other) {
	SetContent( other.GetContent() );
	SetType( other.GetType() );
}*/
