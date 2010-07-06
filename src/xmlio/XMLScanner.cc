//------------------------------------------------------------------------------
/*
	filename: XMLScanner.cpp
	author: Kevin P. Black (C) 2009
	date created: 11.24.09

	Implements the XMLScanner class defined in XMLScanner.h
*/
//------------------------------------------------------------------------------
//	INCLUSIONS

#include "XMLScanner.h"
#include "XMLToken.h"
#include "XMLTag.h"
#include "XMLText.h"
#include "XMLEntity.h"
#include "XMLConstants.h"
#include "CS240Exception.h"
#include <string>
#include <list>
#include <fstream>
#include <sstream>
#include <cctype>

#include "Debug.h"
#include "UnitTest.h"
#include <iostream>
using namespace std;

//------------------------------------------------------------------------------
//	CONSTANTS
const char * OPEN_FILE_ERROR_MSG = "There was an error when opening the file: ";
const char * NOT_VALID_XML_MSG = "The file does not contain valid xml!";

const char NULL_CHAR = '\0';

//------------------------------------------------------------------------------
//	STATIC FUNCTIONS

//bool XMLScanner::Test (ostream & os, bool debug) {
//	bool success = true;
//
//	try {
//		TEST( TestBasicScan(os, debug ) );
//		TEST( TestBasicTagScan(os, debug) );
//		TEST( TestComplexTagScan(os, debug) );
//		TEST( TestComplexScan(os, debug) );
//	}
//	catch (IOException & e) {
//		cerr << e.GetMessage()<<endl;
//		TEST( false );
//	}
//	catch (FileException & e) {
//		cerr << e.GetMessage()<<endl;
//		TEST( false );
//	}
//	catch (IllegalStateException & e) {
//		cerr << e.GetMessage()<<endl;
//		TEST( false );
//	}
//	catch (...) {
//		cerr << "An unknown exception occurred!\n";
//		TEST( false );
//	}
//
//	os << "\tXMLScanner tests: " << ( success ? "OK" : "FAIL" ) << endl;
//	return success;
//}
//
//
//bool XMLScanner::TestBasicScan (ostream & os, bool debug) {
//	bool success = true;
//	DEBUG("Running basic scan test . . . ");
//	XMLScanner scanner; // can't use () when making the object
//	scanner.Scan("./input/scanner_test_one_tag.xml", debug);
//
//	const XMLToken * token_ptr = scanner.NextToken();
//	TEST( token_ptr->GetType() == tag );
//	DEBUG("value of token: "<<token_ptr->GetContent());
//	TEST( token_ptr->GetContent().compare("<xmltag>") == 0 );
//
//	token_ptr = scanner.NextToken();
//	TEST( token_ptr->GetType() == text );
//	DEBUG("value of token: "<<token_ptr->GetContent());
//	TEST( token_ptr->GetContent().compare("xml") == 0 );
//
//	token_ptr = scanner.NextToken();
//	TEST( token_ptr->GetType() == tag );
//	DEBUG("value of token: "<<token_ptr->GetContent());
//	TEST( token_ptr->GetContent().compare("</xmltag>") == 0 );
//
//	TEST( scanner.IsTokenStreamAtEnd() == true );
//
//	return success;
//}
//
//
//bool XMLScanner::TestBasicTagScan (ostream & os, bool debug) {
//	bool success = true;
//	DEBUG("Running basic tag scan test . . .");
//	XMLScanner scanner; // can't use () when making the object
//	scanner.Scan("./input/scanner_test_plain_tags.xml", debug);
//
//	string phonebook_open("<phonebook>");
//	string phonebook_close("</phonebook>");
//	string person_open("<person>");
//	string person_close("</person>");
//	string lastname_open("<lastname>");
//	string lastname_close("</lastname>");
//	string firstname_open("<firstname>");
//	string firstname_close("</firstname>");
//	string telephone_open("<telephone>");
//	string telephone_close("</telephone>");
//
//	const XMLToken * token_ptr = scanner.NextToken();
//	TEST( token_ptr->GetType() == tag );
//	DEBUG("value of token: "<<token_ptr->GetContent());
//	TEST( token_ptr->GetContent().compare(phonebook_open) == 0 );
//
//	token_ptr = scanner.NextToken();
//	TEST( token_ptr->GetType() == tag );
//	DEBUG("value of token: "<<token_ptr->GetContent());
//	TEST( token_ptr->GetContent().compare(person_open) == 0 );
//
//	token_ptr = scanner.NextToken();
//	TEST( token_ptr->GetType() == tag );
//	DEBUG("value of token: "<<token_ptr->GetContent());
//	TEST( token_ptr->GetContent().compare(lastname_open) == 0 );
//
//	token_ptr = scanner.NextToken();
//	TEST( token_ptr->GetType() == text );
//	DEBUG("value of token: "<<token_ptr->GetContent());
//	TEST( token_ptr->GetContent().compare("Black") == 0 );
//
//	token_ptr = scanner.NextToken();
//	TEST( token_ptr->GetType() == tag );
//	DEBUG("value of token: "<<token_ptr->GetContent());
//	TEST( token_ptr->GetContent().compare(lastname_close) == 0 );
//
//	token_ptr = scanner.NextToken();
//	TEST( token_ptr->GetType() == tag );
//	DEBUG("value of token: "<<token_ptr->GetContent());
//	TEST( token_ptr->GetContent().compare(firstname_open) == 0 );
//
//	token_ptr = scanner.NextToken();
//	TEST( token_ptr->GetType() == text );
//	DEBUG("value of token: "<<token_ptr->GetContent());
//	TEST( token_ptr->GetContent().compare("Kevin") == 0 );
//
//	token_ptr = scanner.NextToken();
//	TEST( token_ptr->GetType() == tag );
//	DEBUG("value of token: "<<token_ptr->GetContent());
//	TEST( token_ptr->GetContent().compare(firstname_close) == 0 );
//
//	token_ptr = scanner.NextToken();
//	TEST( token_ptr->GetType() == tag );
//	DEBUG("value of token: "<<token_ptr->GetContent());
//	TEST( token_ptr->GetContent().compare(telephone_open) == 0 );
//
//	token_ptr = scanner.NextToken();
//	TEST( token_ptr->GetType() == text );
//	DEBUG("value of token: "<<token_ptr->GetContent());
//	TEST( token_ptr->GetContent().compare("801-794-9273") == 0 );
//
//	token_ptr = scanner.NextToken();
//	TEST( token_ptr->GetType() == tag );
//	DEBUG("value of token: "<<token_ptr->GetContent());
//	TEST( token_ptr->GetContent().compare(telephone_close) == 0 );
//
//	token_ptr = scanner.NextToken();
//	TEST( token_ptr->GetType() == tag );
//	DEBUG("value of token: "<<token_ptr->GetContent());
//	TEST( token_ptr->GetContent().compare(person_close) == 0 );
//
//	token_ptr = scanner.NextToken();
//	TEST( token_ptr->GetType() == tag );
//	DEBUG("value of token: "<<token_ptr->GetContent());
//	TEST( token_ptr->GetContent().compare(phonebook_close) == 0 );
//
//	TEST( scanner.IsTokenStreamAtEnd() == true );
//
//	return success;
//}
//
//
//bool XMLScanner::TestComplexTagScan (ostream & os, bool debug) {
//	bool success = true;
//
//	DEBUG("Running complex tag scan test . . .");
//	XMLScanner scanner; // can't use () when making the object
//	scanner.Scan("./input/scanner_test_complex_tags.xml", debug);
//
//	string phonebook_open("<phonebook entries=\"1\">");
//	string phonebook_close("</phonebook>");
//	string person_open("<person id=\"1\">");
//	string person_close("</person>");
//	string lastname_open("<lastname>");
//	string lastname_close("</lastname>");
//	string firstname_open("<firstname>");
//	string firstname_close("</firstname>");
//	string telephone_open("<telephone>");
//	string telephone_close("</telephone>");
//
//	const XMLToken * token_ptr = scanner.NextToken();
//	TEST( token_ptr->GetType() == tag );
//	DEBUG("value of token: "<<token_ptr->GetContent());
//	TEST( token_ptr->GetContent().compare(phonebook_open) == 0 );
//
//	token_ptr = scanner.NextToken();
//	TEST( token_ptr->GetType() == tag );
//	DEBUG("value of token: "<<token_ptr->GetContent());
//	TEST( token_ptr->GetContent().compare(person_open) == 0 );
//
//	token_ptr = scanner.NextToken();
//	TEST( token_ptr->GetType() == tag );
//	DEBUG("value of token: "<<token_ptr->GetContent());
//	TEST( token_ptr->GetContent().compare(lastname_open) == 0 );
//
//	token_ptr = scanner.NextToken();
//	TEST( token_ptr->GetType() == text );
//	DEBUG("value of token: "<<token_ptr->GetContent());
//	TEST( token_ptr->GetContent().compare("Black") == 0 );
//
//	token_ptr = scanner.NextToken();
//	TEST( token_ptr->GetType() == tag );
//	DEBUG("value of token: "<<token_ptr->GetContent());
//	TEST( token_ptr->GetContent().compare(lastname_close) == 0 );
//
//	token_ptr = scanner.NextToken();
//	TEST( token_ptr->GetType() == tag );
//	DEBUG("value of token: "<<token_ptr->GetContent());
//	TEST( token_ptr->GetContent().compare(firstname_open) == 0 );
//
//	token_ptr = scanner.NextToken();
//	TEST( token_ptr->GetType() == text );
//	DEBUG("value of token: "<<token_ptr->GetContent());
//	TEST( token_ptr->GetContent().compare("Kevin") == 0 );
//
//	token_ptr = scanner.NextToken();
//	TEST( token_ptr->GetType() == tag );
//	DEBUG("value of token: "<<token_ptr->GetContent());
//	TEST( token_ptr->GetContent().compare(firstname_close) == 0 );
//
//	token_ptr = scanner.NextToken();
//	TEST( token_ptr->GetType() == tag );
//	DEBUG("value of token: "<<token_ptr->GetContent());
//	TEST( token_ptr->GetContent().compare(telephone_open) == 0 );
//
//	token_ptr = scanner.NextToken();
//	TEST( token_ptr->GetType() == text );
//	DEBUG("value of token: "<<token_ptr->GetContent());
//	TEST( token_ptr->GetContent().compare("801-794-9273") == 0 );
//
//	token_ptr = scanner.NextToken();
//	TEST( token_ptr->GetType() == tag );
//	DEBUG("value of token: "<<token_ptr->GetContent());
//	TEST( token_ptr->GetContent().compare(telephone_close) == 0 );
//
//	token_ptr = scanner.NextToken();
//	TEST( token_ptr->GetType() == tag );
//	DEBUG("value of token: "<<token_ptr->GetContent());
//	TEST( token_ptr->GetContent().compare(person_close) == 0 );
//
//	token_ptr = scanner.NextToken();
//	TEST( token_ptr->GetType() == tag );
//	DEBUG("value of token: "<<token_ptr->GetContent());
//	TEST( token_ptr->GetContent().compare(phonebook_close) == 0 );
//
//	TEST( scanner.IsTokenStreamAtEnd() == true );
//
//	return success;
//}
//
//
//bool XMLScanner::TestComplexScan (ostream & os, bool debug) {
//	bool success = true;
//
//	DEBUG("Running complex scan test . . .");
//	XMLScanner scanner; // can't use () when making the object
//	scanner.Scan("./input/scanner_test_complex.xml", debug);
//
//	string phonebook_open("<phonebook entries=\"1\">");
//	string phonebook_close("</phonebook>");
//	string person_open("<person id=\"1\">");
//	string person_close("</person>");
//	string lastname_open("<lastname>");
//	string lastname_close("</lastname>");
//	string firstname_open("<firstname>");
//	string firstname_close("</firstname>");
//	string telephone_open("<telephone>");
//	string telephone_close("</telephone>");
//	string age_self_close("<age yrs=\"21\"/>");
//
//	const XMLToken * token_ptr = scanner.NextToken();
//	TEST( token_ptr->GetType() == tag );
//	DEBUG("value of token: "<<token_ptr->GetContent());
//	TEST( token_ptr->GetContent().compare(phonebook_open) == 0 );
//
//	token_ptr = scanner.NextToken();
//	TEST( token_ptr->GetType() == tag );
//	DEBUG("value of token: "<<token_ptr->GetContent());
//	TEST( token_ptr->GetContent().compare(person_open) == 0 );
//
//	token_ptr = scanner.NextToken();
//	TEST( token_ptr->GetType() == tag );
//	DEBUG("value of token: "<<token_ptr->GetContent());
//	TEST( token_ptr->GetContent().compare(lastname_open) == 0 );
//
//	token_ptr = scanner.NextToken();
//	TEST( token_ptr->GetType() == text );
//	DEBUG("value of token: "<<token_ptr->GetContent());
//	TEST( token_ptr->GetContent().compare("B") == 0 );
//
//	token_ptr = scanner.NextToken();
//	TEST( token_ptr->GetType() == entity );
//	DEBUG("value of token: "<<token_ptr->GetContent());
//	TEST( token_ptr->GetContent().compare("\'") == 0 );
//
//	token_ptr = scanner.NextToken();
//	TEST( token_ptr->GetType() == text );
//	DEBUG("value of token: "<<token_ptr->GetContent());
//	TEST( token_ptr->GetContent().compare("lack") == 0 );
//
//	token_ptr = scanner.NextToken();
//	TEST( token_ptr->GetType() == tag );
//	DEBUG("value of token: "<<token_ptr->GetContent());
//	TEST( token_ptr->GetContent().compare(lastname_close) == 0 );
//
//	token_ptr = scanner.NextToken();
//	TEST( token_ptr->GetType() == tag );
//	DEBUG("value of token: "<<token_ptr->GetContent());
//	TEST( token_ptr->GetContent().compare(firstname_open) == 0 );
//
//	token_ptr = scanner.NextToken();
//	TEST( token_ptr->GetType() == text );
//	DEBUG("value of token: "<<token_ptr->GetContent());
//	TEST( token_ptr->GetContent().compare("Kevin") == 0 );
//
//	token_ptr = scanner.NextToken();
//	TEST( token_ptr->GetType() == tag );
//	DEBUG("value of token: "<<token_ptr->GetContent());
//	TEST( token_ptr->GetContent().compare(firstname_close) == 0 );
//
//	token_ptr = scanner.NextToken();
//	TEST( token_ptr->GetType() == tag );
//	DEBUG("value of token: "<<token_ptr->GetContent());
//	TEST( token_ptr->GetContent().compare(telephone_open) == 0 );
//
//	token_ptr = scanner.NextToken();
//	TEST( token_ptr->GetType() == text );
//	DEBUG("value of token: "<<token_ptr->GetContent());
//	TEST( token_ptr->GetContent().compare("801-794-9273") == 0 );
//
//	token_ptr = scanner.NextToken();
//	TEST( token_ptr->GetType() == tag );
//	DEBUG("value of token: "<<token_ptr->GetContent());
//	TEST( token_ptr->GetContent().compare(telephone_close) == 0 );
//
//	token_ptr = scanner.NextToken();
//	TEST( token_ptr->GetType() == tag );
//	DEBUG("value of token: "<<token_ptr->GetContent());
//	TEST( token_ptr->GetContent().compare(age_self_close) == 0 );
//
//	const XMLTag * tag_ptr = (const XMLTag *) token_ptr;
//	TEST( tag_ptr->GetTagName().compare("age") == 0 );
//	TEST( tag_ptr->GetAttributeValue("yrs").compare("21") == 0 );
//
//	token_ptr = scanner.NextToken();
//	TEST( token_ptr->GetType() == tag );
//	DEBUG("value of token: "<<token_ptr->GetContent());
//	TEST( token_ptr->GetContent().compare(person_close) == 0 );
//
//	token_ptr = scanner.NextToken();
//	TEST( token_ptr->GetType() == tag );
//	DEBUG("value of token: "<<token_ptr->GetContent());
//	TEST( token_ptr->GetContent().compare(phonebook_close) == 0 );
//
//	TEST( scanner.IsTokenStreamAtEnd() == true );
//
//	return success;
//}


//------------------------------------------------------------------------------
//	PUBLIC FUNCTIONS

XMLScanner::XMLScanner () : token_stream() {
	ResetTokenStreamToBegin();
}


XMLScanner::~XMLScanner () {
	ClearTokenStream();
	CloseInputFile();
}


void XMLScanner::Scan (const std::string & filename, bool debug) {
	// open the file
	// scan it character by character

	// a "<" indicates a tag (technically only if not processing an attribute value)
	//  the name of the tag must start with a letter or ":" or "_"
	//    (and other character entities)
	//  the name may include any of the previously mentioned characters
	//    as well as digits, "-", "." (and other character entities)
	// a "/" right after a "<" indicates a closing tag
	// a "/" right before a ">" indicates a self-closing/emptyelement tag

	// an attribute may start with a letter or ":" or "_" and be followed by those
	//   characters as well as digits, "-", and "."
	// then there may be whitespace before "=" more whitespace and then a single or
	//   double quote that delimits the attribute value
	// an attribute value may contain any character including the sinlge and double
	///  quotes

	// entities begin with "&" and end with ";" and are not split by whitespace

	// text is a tag's element data

	// technically (and for well-formedness) if there is any error in the xml format
	//   then it should not continue to be processed and an error reported

	DEBUG("scanning "<<filename<<" . . . ");
	ClearTokenStream();
	OpenInputFile(filename);

	char character = PeekNextCharacterFromInputFile();
	//int i = 0;
	while ( character != NULL_CHAR ) {
		//i++;
		//if ( 100 <= i )
		//	throw IllegalStateException("Scan: looping to many times");

		DEBUG("Scan: value of character: \""<<character<<"\"");
		if ( character == TAG_BEGIN ) {
			ExtractTag(debug); // may need to extract a comment
		}
		else if ( character == AMPERSAND ) {
			ExtractEntity(debug);
		}
		else if ( IsNameChar(character) ) {
			ExtractText(debug);
		}
		else if ( isspace(character) ) {
			character = GetNextCharacterFromInputFile();
		} else {
			NotValidXML("Scan driver");
		}
		character = PeekNextCharacterFromInputFile();
	}

	CloseInputFile();

	if ( !AreTagsBalanced() ) {
		NotValidXML("Scan: tag balance test");
	}

	ResetTokenStreamToBegin();
}


const XMLToken * XMLScanner::NextToken () {
	XMLToken * token_ptr = NULL;
	if ( stream_iterator != token_stream.end() ) {
		token_ptr = *stream_iterator;
		stream_iterator++;
	}

	return ( token_ptr );
}


const XMLToken * XMLScanner::PreviousToken () {
	XMLToken * token_ptr = NULL;
	if ( stream_iterator != token_stream.begin() ) {
		token_ptr = *stream_iterator;
		stream_iterator--;
	}

	return ( token_ptr );
}


bool XMLScanner::IsTokenStreamAtBegin () {
	return ( stream_iterator == token_stream.begin() ? true : false );
}


bool XMLScanner::IsTokenStreamAtEnd () {
	return ( stream_iterator == token_stream.end() ? true : false );
}


void XMLScanner::ResetTokenStreamToBegin () {
	stream_iterator = token_stream.begin();
}

void XMLScanner::ResetTokenStreamToEnd () {
	stream_iterator = token_stream.end();
}


//------------------------------------------------------------------------------
//	PROTECTED FUNCTIONS

//------------------------------------------------------------------------------
//	PRIVATE FUNCTIONS

void XMLScanner::NotValidXML(const string & error_source) {
	bool debug = false;
	DEBUG("The file is not valid xml.  Closing it and clearing the stream");
	ClearTokenStream();
	CloseInputFile();
	stringstream msg;
	msg << NOT_VALID_XML_MSG << "\n\tsource: " << error_source;
	throw IOException(msg.str());
}


void XMLScanner::OpenInputFile (const string & filename) {
	bool debug = true;
	in_file_ptr = new ifstream( filename.c_str() );

	if ( in_file_ptr->fail() ) {
		CloseInputFile();
		DEBUG(OPEN_FILE_ERROR_MSG<<filename);
		throw FileException(OPEN_FILE_ERROR_MSG + filename);
	}

}


void XMLScanner::CloseInputFile () {
	if ( in_file_ptr != NULL ) {
		in_file_ptr->close();
		delete in_file_ptr;
		in_file_ptr = NULL;
	}
}


char XMLScanner::GetNextCharacterFromInputFile () {
	char ch = NULL_CHAR;
	ch = (*in_file_ptr).get();

	if ( in_file_ptr->fail() || in_file_ptr->eof() ) {
		ch = NULL_CHAR;
	}
	return ch;
}

char XMLScanner::PeekNextCharacterFromInputFile () {
	char ch = NULL_CHAR;
	ch = (*in_file_ptr).peek();

	if ( in_file_ptr->fail() || in_file_ptr->eof() ) {
		ch = NULL_CHAR;
	}
	return ch;
}


void XMLScanner::ClearTokenStream () {
	ResetTokenStreamToBegin();

	while ( !IsTokenStreamAtEnd() ) {
		delete (*stream_iterator);
		stream_iterator++;
	}
	token_stream.clear();
	ResetTokenStreamToBegin();
}


void XMLScanner::AddToStream (XMLToken * token_ptr) {
	token_stream.insert( token_stream.end(), token_ptr );
}

///@todo check that the scanned xml file is balanced
bool XMLScanner::AreTagsBalanced () {
	return true;
}


bool XMLScanner::IsNameStartChar (char ch) {
	if ( isalpha(ch) || ch == COLON || ch == UNDERSCORE ) {
		return true;
	}
	return false;
}


bool XMLScanner::IsNameChar (char ch) {
	if ( isalpha(ch) || isdigit(ch) || ch == COLON || ch == UNDERSCORE ||
	 	ch == HYPHEN || ch == FULL_STOP ) {
		return true;
	}
	return false;
}


bool XMLScanner::IsStandardDelim (char ch ) {
	if ( isspace(ch) || ch == AMPERSAND || ch == TAG_END ||
		ch == TAG_BEGIN || ch == TAG_CLOSE || ch == EQUALS_SIGN ) {
		return true;
	}
	return false;
}


bool XMLScanner::IsQuote (char ch) {
	if ( ch == DBL_QUOTES || ch == SNGL_QUOTE ) {
		return true;
	}
	return false;
}


void XMLScanner::SkipWhiteSpace () {
	char ch = PeekNextCharacterFromInputFile();

	while ( isspace(ch) ) {
		GetNextCharacterFromInputFile();
		ch = PeekNextCharacterFromInputFile();
	}
}


void XMLScanner::ExtractTag (bool debug) {
	// read in the tag name and create an XMLTag with it
	// parse the attributes if the tag is an open/self-close tag
	// throw exception if the tag is close tag and has attributes
	// add pointer to token stream

	DEBUG("extracting tag . . . ");
	// see if the tag is a closing tag
	bool is_closing_tag = false;
	char character = GetNextCharacterFromInputFile(); // read the "<"
	character = PeekNextCharacterFromInputFile();

	if ( character == TAG_CLOSE) {
		is_closing_tag = true;
		character = GetNextCharacterFromInputFile(); // read the "/"
	}

	string tagname = ExtractName(debug);
	// break on whitespace, /, >, other punctuation
	// invalidate on ", ', &, <

	XMLTag * extracted_tag_ptr = new XMLTag( tagname );

	if ( is_closing_tag ) {
		DEBUG("making tag a clos tag");
		extracted_tag_ptr->SetTagType(xmltag_close);

		SkipWhiteSpace();
		character = GetNextCharacterFromInputFile();
		if ( character != TAG_END ) {
			delete extracted_tag_ptr;
			NotValidXML("ExtractTag: closing tag format"); // throws exception
		}
	}
	else {
		DEBUG("proecessing tag open or self close tag . . .");
		//int i = 0;
		do {
			//i++;
			//if ( 100 <= i ) {
			//	throw IllegalStateException("ExtractTag: looping too many times");
			//}

			SkipWhiteSpace();
			character = PeekNextCharacterFromInputFile();
			DEBUG("ExtractTag: value of character: "<<character);

			if ( character == TAG_END ) {
				GetNextCharacterFromInputFile(); // read the ">"
				break;
			}

			if ( character == TAG_CLOSE ) {
				extracted_tag_ptr->SetTagType(xmltag_self_close);
				character = GetNextCharacterFromInputFile(); // read the "/"
				character = GetNextCharacterFromInputFile(); // read the ">"
				if ( character != TAG_END ) {
					NotValidXML("ExtractTag: self closing tag format");
				}
				break;
			}

			if ( IsNameStartChar(character) ) {
				ExtractTagAttribute(extracted_tag_ptr, debug);
				continue;
			}
			// else invalidate xml document
			NotValidXML("ExtractTag: unrecognized character!");
		} while ( true );
	}
	AddToStream(extracted_tag_ptr);
	DEBUG("added tag: "<<extracted_tag_ptr->GetContent());
}


void XMLScanner::ExtractTagAttribute (XMLTag * tag_ptr, bool debug) {
	DEBUG("extracting tag attribute . . .");
	string attribute = ExtractName(debug);

	SkipWhiteSpace();

	char character = GetNextCharacterFromInputFile();
	if ( character != EQUALS_SIGN ) {
		delete tag_ptr;
		DEBUG("character found: " << character);
		NotValidXML("ExtractTagAttribute: missing equals sign"); // throws exception
	}

	SkipWhiteSpace();
	character = GetNextCharacterFromInputFile();

	if ( !IsQuote(character) ) {
		delete tag_ptr;
		DEBUG("character found: " << character);
		NotValidXML("ExtractTagAttribute: missing quote marks"); // throws exception
	}

	///@todo allow for entities or references in values
	string value;
	if ( character == DBL_QUOTES ) {
		value = ExtractStringUntil( DBL_QUOTES, true, debug );
	}
	else /* character == SNGL_QUOTE */ {
		value = ExtractStringUntil( SNGL_QUOTE, true, debug );
	}
	GetNextCharacterFromInputFile(); // read the quote mark
	tag_ptr->DefineAttribute(attribute, value);
	DEBUG("tag with extracted attribute: "<<tag_ptr->GetContent());
}


///@todo see comment below
void XMLScanner::ExtractText (bool debug) {
	// make it so that it will accept any punctuation (except &, ", '),
	// *numbers, etc. at the beggining
	// stop on whitespace, <, &
	// invalidate on >, ", ' (let the scan driver do that, just stop on these)
	DEBUG("extracting text . . . ");
	string text_str = ExtractStringUntil( NULL_CHAR, false, debug );
	XMLText * text_ptr = new XMLText( text_str );
	AddToStream(text_ptr);
	DEBUG("extracted text: "<<text_ptr->GetContent());
}


void XMLScanner::ExtractEntity (bool debug) {
	DEBUG("extracting entity . . .");
	char character = GetNextCharacterFromInputFile();

	if ( character != AMPERSAND ) {
		DEBUG("character found: "<<character);
		NotValidXML("ExtractEntity: no ampersand character");
	}

	stringstream entity_stream;
	entity_stream << (const char) character; // add the "&"
	entity_stream << ExtractStringUntil( SEMI_COLON, debug );
	// could use ExtractName until ";"
	// if ";" not found before whitespace, /, <, >, ", ', &,
	//   or unsupported punctuation then invalidate
	/*do {
		entity_stream << (const char) character;
		character = GetNextCharacterFromInputFile();

		if ( character == SEMI_COLON ) {
			entity_stream << (const char) character;
			break;
		}

		if ( !IsNameChar(character) ) {
			DEBUG("character found: "<<character);
			NotValidXML("ExtractEntity: invalid character");
		}
	} while ( true );
	*/

	character = GetNextCharacterFromInputFile();

	if ( character != SEMI_COLON ) {
		NotValidXML("ExtractEntity: no semi colon to terminate entity!");
	}
	entity_stream << character;

	string entity_str = entity_stream.str();

	XMLEntity * entity_ptr = NULL;

	if ( entity_str.compare("&lt;") == 0 ) {
		entity_ptr = new XMLEntity( "<" );
	}
	else if ( entity_str.compare("&gt;") == 0 ) {
		entity_ptr = new XMLEntity( ">" );
	}
	else if ( entity_str.compare("&amp;") == 0 ) {
		entity_ptr = new XMLEntity( "&" );
	}
	else if ( entity_str.compare("&apos;") == 0 ) {
		entity_ptr = new XMLEntity( "'" );
	}
	else if ( entity_str.compare("&quot;") == 0 ) {
		entity_ptr = new XMLEntity( "\"" );
	}
	else {
		entity_ptr = new XMLEntity( "?" );
	}

	AddToStream(entity_ptr);
	DEBUG("extracted entity: "<<entity_ptr->GetContent());
}

///@todo give parameters to extract until, and parameters to exclude (invalidate the xml document)


string XMLScanner::ExtractName (bool debug) {
	DEBUG("extracting name . . .");
	char character = GetNextCharacterFromInputFile();

	if ( !IsNameStartChar(character) ) {
		DEBUG("on start char check character found: "<< character);
		NotValidXML("ExtractName: invalid character");
	}

	stringstream name;
	name << (const char) character;
	name << ExtractStringUntil( NULL_CHAR, false, debug );
	/*
	do {
		name << (const char) character;
		character = PeekNextCharacterFromInputFile();

		if ( IsStandardDelim(character) || IsQuote(character) ) {
			break;
		}

		if ( !IsNameChar(character) ) {
			DEBUG("on mid char check character found: "<<character);
			NotValidXML("ExtractName: invalid character");
		}

		character = GetNextCharacterFromInputFile();
	} while ( true );
	*/
	DEBUG("extracted name: "<<name.str());

	return ( name.str() );
}


///@todo allow other punctuation to be accepted i.e. #, @, !, etc.
string XMLScanner::ExtractStringUntil (char extra_delim, bool include_quotes, bool debug) {
	DEBUG("extracting string until "<<extra_delim<<" . . .");

	stringstream extracted_string;
	char character = NULL_CHAR;
	do {
		character = PeekNextCharacterFromInputFile();

		if ( IsStandardDelim(character) || character == extra_delim ) {
			break;
		}

		// if the character is not a name character
		// and it is not a quote if quotes should be included
		if ( !IsNameChar(character) && ( !include_quotes && IsQuote(character) ) ) {
			DEBUG("ExtractStringUntil: on mid char check found: "<<character);
			NotValidXML("ExtractStringUntil: invalid character"); //throws exception
		}

		character = GetNextCharacterFromInputFile();
		extracted_string << (const char) character;
	} while ( true );

	DEBUG("extracted string: "<<extracted_string.str());

	return ( extracted_string.str() );
}

