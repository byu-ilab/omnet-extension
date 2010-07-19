/*
 * stdstringutils.h
 *
 *  Created on: Jul 16, 2010
 *      Author: Kevin Black
 */

#ifndef STDSTRINGUTILS_H_
#define STDSTRINGUTILS_H_

#include <string>

bool stdstring_contains(const std::string & source, const std::string & fragment, bool case_sensitive=true);

std::string & stdstring_tolower(std::string & str);

#endif /* STDSTRINGUTILS_H_ */
