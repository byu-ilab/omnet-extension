/*
 * stdstringutils.cc
 *
 *  Created on: Jul 16, 2010
 *      Author: Kevin Black
 */

#include "stdstringutils.h"
#include <cctype>

bool stdstring_contains(const std::string & source, const std::string & fragment, bool case_sensitive)
{
	if (case_sensitive)
	{
		return ( source.find(fragment, 0) != std::string::npos );
	}

	// convert both strings to lower case
	std::string lc_source = source;
	stdstring_tolower(lc_source);

	std::string lc_fragment = fragment;
	stdstring_tolower(lc_fragment);

	return ( lc_source.find(lc_fragment, 0) != std::string::npos );
}

std::string & stdstring_tolower(std::string & str)
{
	for (unsigned int i = 0; i < str.size(); i++)
	{
		char c = str.at(i);
		if ( !islower(c) )
		{
			str.replace(i, 1, 1, tolower(c));
		}
	}

	return str;
}
