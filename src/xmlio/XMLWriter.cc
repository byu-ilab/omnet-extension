//------------------------------------------------------------------------------
/*
	filename: XMLWriter.cpp
	author: Kevin P. Black (C) 2009
	date created: 11.21.09

	Implements the XMLWriter class defined in XMLWriter.h
*/
//------------------------------------------------------------------------------
//	INCLUSIONS

// for functionality
#include "XMLWriter.h"
#include "XMLConstants.h"
#include "XMLToken.h"
#include "XMLTokenType.h"
#include <string>
#include <fstream>
#include "CS240Exception.h"
#include "StringUtil.h"

// for testing
#include "XMLTag.h"
#include "XMLText.h"
#include "XMLEntity.h"

#include "Debug.h"
#include "UnitTest.h"
#include <iostream>
using namespace std;

//------------------------------------------------------------------------------
//	CONSTANTS
/*const char TAG_BEGIN = '<';
const char TAG_END = '>';
const char TAG_CLOSE = '/';
const char TAB = '\t';
const char NEWLINE = '\n';*/

const char * FILE_NOT_OPEN_MSG = "There is no file open to write to!";

//------------------------------------------------------------------------------
//	STATIC FUNCTIONS

///@todo Make the XMLWriter tests automated!
//bool XMLWriter::Test (ostream & os, bool debug) {
//	bool success = true;
//
//	try {
//		TEST( TestStringWrite(os, debug) );
//		TEST( TestTokenWrite(os, debug) );
//	}
//	catch (IllegalStateException & e) {
//		TEST( false );
//	}
//	catch (...) {
//		TEST( false );
//	}
//
//	os << "\tXMLWriter tests: " << ( success ? "OK" : "FAIL" ) << endl;
//	return success;
//}
//
//
//bool XMLWriter::TestStringWrite (ostream & os, bool debug) {
//	bool success = true;
//	DEBUG("Testing string writing operations . . .");
//
//	string k_file("./output/xml_string_writer_test.xml");
//
//	XMLWriter writer(k_file);
//
//	string person = "person";
//	string person_attributes = " age=\"21\" major=\"CS\"";
//	string first_name = "first-name";
//	string middle_name = "middle-name";
//	string last_name = "last-name";
//	string website = "website link=\"students.cs.byu.edu\\kpbinc\"";
//	string equation = "equation";
//	string equation_value = "2 > 1";
//
//	// write normal tags
//	writer.WriteOpenTag(person + person_attributes);
//	writer.Align(1);
//
//	writer.WriteOpenTag(first_name);
//	writer.Write("Kevin");
//	writer.WriteCloseTag(first_name);
//	writer.Align(1);
//
//	writer.WriteOpenTag(middle_name);
//	writer.Write("Peter");
//	writer.WriteCloseTag(middle_name);
//	writer.Align(1);
//
//	writer.WriteOpenTag(last_name);
//	writer.Write("Black");
//	writer.WriteCloseTag(last_name);
//	writer.Align(0);
//
//	writer.WriteCloseTag(person);
//
//	// write self closing tag
//	writer.Align(2);
//	writer.WriteSelfClosingTag(website);
//	writer.Align(2);
//
//	// verify the xml entity encoding
//	writer.WriteOpenTag(equation);
//	writer.Write(equation_value);
//	writer.WriteCloseTag(equation);
//
//	writer.Close();
//
//	return success;
//}
//
//
//bool XMLWriter::TestTokenWrite (ostream & os, bool debug) {
//	bool success = true;
//
//	// define the tokens
//	XMLTag person_tag("person");
//	person_tag.DefineAttribute("age", "21");
//	person_tag.DefineAttribute("major", "CS");
//
//	XMLTag firstname_tag("first-name");
//	XMLTag lastname_tag("last-name");
//	XMLTag middlename_tag("middle-name");
//
//	XMLTag website_tag("website");
//	website_tag.DefineAttribute("link", "students.cs.byu.edu\\kpbinc");
//	website_tag.SetTagType(xmltag_self_close);
//
//	XMLTag equation_tag("equation");
//
//	XMLText fn_text("Kevin");
//	XMLText ln_text("Black");
//	XMLText mn_text("Peter");
//	XMLText eq_num_1_text("1");
//	XMLText eq_num_2_text("2");
//	XMLEntity eq_op_entity(">");
//
//	// open the writer
//	string k_file("./output/xml_token_writer_test.xml");
//
//	XMLWriter writer(k_file);
//
//	// write the tokens
//	writer.Write(person_tag);
//	writer.Align(1);
//
//	writer.Write(firstname_tag);
//	writer.Write(fn_text);
//	firstname_tag.SetTagType(xmltag_close);
//	writer.Write(firstname_tag);
//	writer.Align(1);
//
//	writer.Write(middlename_tag);
//	writer.Write(mn_text);
//	middlename_tag.SetTagType(xmltag_close);
//	writer.Write(middlename_tag);
//	writer.Align(1);
//
//	writer.Write(lastname_tag);
//	writer.Write(ln_text);
//	lastname_tag.SetTagType(xmltag_close);
//	writer.Write(lastname_tag);
//	writer.Align(0);
//
//	person_tag.SetTagType(xmltag_close);
//	writer.Write(person_tag);
//
//	// write self closing tag
//	writer.Align(2);
//	writer.Write(website_tag);
//	writer.Align(2);
//
//	// verify the xml entity encoding
//	writer.Write(equation_tag);
//	writer.Write(eq_num_2_text);
//	writer.WriteSpace();
//	writer.Write(eq_op_entity);
//	writer.WriteSpace();
//	writer.Write(eq_num_1_text);
//	equation_tag.SetTagType(xmltag_close);
//	writer.Write(equation_tag);
//
//	writer.Close();
//
//	return success;
//}

//------------------------------------------------------------------------------
//	PUBLIC FUNCTIONS

XMLWriter::XMLWriter (const std::string filename)
	: file_is_open(false), file_to_write(filename.c_str()) {
	ValidateState();
	if ( !file_to_write.fail() )
		file_is_open = true;
}


void XMLWriter::Write (const string & content) {
	CheckOpenState();
	string copy = StringUtil::EncodeToXmlCopy(content);
	file_to_write << copy;
	ValidateState();
}


void XMLWriter::Write (const XMLToken & token) {
	if ( token.GetType() == entity ) {
		file_to_write << StringUtil::EncodeToXmlCopy(token.GetContent());
	}
	else {
		file_to_write << token.GetContent();
	}
}


void XMLWriter::WriteSpace () {
	CheckOpenState();
	file_to_write << SPACE;
	ValidateState();
}


void XMLWriter::WriteTab () {
	CheckOpenState();
	file_to_write << TAB;
	ValidateState();
}


void XMLWriter::WriteNewLine () {
	CheckOpenState();
	file_to_write << NEWLINE;
	ValidateState();
}


void XMLWriter::Align (int indent) {
	WriteNewLine();
	for (int i = 0; i < indent; i++) {
		WriteTab();
	}
}


void XMLWriter::WriteOpenTag (const string & tag_content) {
	CheckOpenState();
	file_to_write << TAG_BEGIN << tag_content << TAG_END;
	ValidateState();
}


void XMLWriter::WriteCloseTag (const string & tag_name) {
	CheckOpenState();
	file_to_write << TAG_BEGIN << TAG_CLOSE << tag_name << TAG_END;
	ValidateState();
}


void XMLWriter::WriteSelfClosingTag (const string & tag_content) {
	CheckOpenState();
	file_to_write << TAG_BEGIN << tag_content << TAG_CLOSE << TAG_END;
	ValidateState();
}


void XMLWriter::Open (const string & filename) {
	if ( IsOpen() )
		Close();

	file_to_write.open(filename.c_str());

	ValidateState();
}


bool XMLWriter::IsOpen () {
	return file_is_open;
}


void XMLWriter::Close () {
	file_to_write.close();
	file_is_open = false;
}

//------------------------------------------------------------------------------
//	PROTECTED FUNCTIONS

//------------------------------------------------------------------------------
//	PRIVATE FUNCTIONS

void XMLWriter::CheckOpenState () {
	if ( !IsOpen() )
		throw IllegalStateException(FILE_NOT_OPEN_MSG);
}

void XMLWriter::ValidateState () {
	if ( !file_to_write.fail() )
		file_is_open = true;
}


