//------------------------------------------------------------------------------
/*
	filename: XMLEntity.cpp
	author: Kevin P. Black (C) 2009
	date created: 11.23.09

	Implements the XMLEntity class defined in XMLEntity.h
*/
//------------------------------------------------------------------------------
//	INCLUSIONS

#include "XMLEntity.h"
#include "XMLTokenType.h"
#include "StringUtil.h"
#include <string>

#include "Debug.h"
#include "UnitTest.h"
#include <iostream>
using namespace std;

//------------------------------------------------------------------------------
//	CONSTANTS

//------------------------------------------------------------------------------
//	STATIC FUNCTIONS

//bool XMLEntity::Test (ostream & os, bool debug) {
//	bool success = true;
//
//	// Test the constructors
//	string greaterthan(">");
//	string greaterthan_encoded("&gt;");
//	string lessthan("<");
//	string lessthan_encoded("&lt;");
//	XMLEntity t_1(greaterthan);
//
//	TEST( t_1.GetContent().compare(greaterthan) == 0 );
//	TEST( t_1.GetContentEncoded().compare(greaterthan_encoded) == 0 );
//	TEST( t_1.GetType() == entity );
//
//	XMLEntity t_2(t_1);
//
//	TEST( t_2.GetContent().compare(greaterthan) == 0 );
//	TEST( t_2.GetContentEncoded().compare(greaterthan_encoded) == 0 );
//	TEST( t_1.GetType() == entity );
//
//	// Test the uniqueness of XMLEntitys
//	t_2.SetContent(lessthan);
//
//	TEST( t_2.GetContent().compare(lessthan) == 0 );
//	TEST( t_1.GetContent().compare(greaterthan) == 0 ); //notice it is called on t_1
//
//	// Test the assignment operator
//	t_1 = t_2;
//
//	TEST( t_1.GetContent().compare(lessthan) == 0 );
//	TEST( t_1.GetType() == entity );
//
//	// Test the creation of an XMLEntity object without a type of entity
//	XMLToken gt_1(greaterthan, generic);
//
//	t_1 = gt_1;
//
//	TEST( t_1.GetContent().compare(greaterthan) == 0 );
//	TEST( t_1.GetContentEncoded().compare(greaterthan) == 0 );
//	TEST( t_1.GetType() == generic );
//
//	XMLEntity t_3(gt_1);
//
//	TEST( t_3.GetContent().compare(greaterthan) == 0 );
//	TEST( t_3.GetContentEncoded().compare(greaterthan) == 0 );
//	TEST( t_3.GetType() == generic );
//
//
//	os << "\tXMLEntity tests: " << ( success ? "OK" : "FAIL" ) << endl;
//	return success;
//}

//------------------------------------------------------------------------------
//	PUBLIC FUNCTIONS

XMLEntity::XMLEntity (const std::string & content)
	: XMLToken(content, entity) {
}



XMLEntity::XMLEntity (const XMLToken & other)
	: XMLToken(other) {
	bool debug = false;
	DEBUG("XMLEntity: generic token copy constructor called");
	SetType(other.GetType());
}


XMLEntity::~XMLEntity () {
}



XMLEntity & XMLEntity::operator = (const XMLToken & other) {
	bool debug = false;
	DEBUG("XMLEntity: generic token assignment operator called");
	if ( this != &other ) {
		SetContent( other.GetContent() );
		SetType( other.GetType() );
	}
	return ( *this );
}


string XMLEntity::GetContentEncoded () const {
	string content = GetContent();
	if ( GetType() == entity ) {
		StringUtil::EncodeToXml( content );
	}

	return ( content );
}

//------------------------------------------------------------------------------
//	PROTECTED FUNCTIONS

//------------------------------------------------------------------------------
//	PRIVATE FUNCTIONS

void XMLEntity::SetType (XMLTokenType type ) {
	if ( type != entity ) {
		XMLToken::SetType( generic );
	}
	else {
		XMLToken::SetType( entity );
	}
}

