#ifndef STRING_UTIL_H
#define STRING_UTIL_H

#include <string>


//!@defgroup string String Utils
//!Helper functions for std::string's
//!@li StringUtil::IsPrefix
//!@li StringUtil::IsSuffix
//!@li StringUtil::ToLower
//!@li StringUtil::Trim
//!@li StringUtil::EncodeToXml


//!@ingroup std::string
namespace StringUtil
{
	//!@return true if prefix is a prefix of str, and false if it is not.
	bool IsPrefix(const std::string & str, const std::string & prefix);

	//!@return true if suffix is a suffix of str, and false if it is not.
	bool IsSuffix(const std::string & str, const std::string & suffix);

	//!Inplace converts each character in str to lower-case.
	void ToLower(std::string & str);

	//!Inplace converts each character in substring [start, end) to lower-case.
	void ToLower(std::string::iterator start, std::string::iterator end);
	
	
	//!@return A copy of str in which each character in str is converted to lower-case.
	std::string ToLowerCopy (const std::string & str);
	
	//!Inplace converts each character in str which are considered
	//!an XML special character (&,<,>,',") will be converted to an XML entity( & -> &amp;amp;).
	void EncodeToXml (std::string & str);
	
	//!@return A copy of str in which each character in str which are considered
	//!an XML special character (&,<,>,',") will be converted to an XML entity( & -> &amp;amp;).
	std::string EncodeToXmlCopy (const std::string & str);

	//!Inplace removes all leading and trailing whitespace from str.
	void Trim(std::string & str);

	//!@return A copy of str which has removed all leading and trailing whitespace.
	std::string TrimCopy(const std::string & str);
}


#endif
