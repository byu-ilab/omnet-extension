#include <cctype>
#include "StringUtil.h"



namespace StringUtil
{


bool IsPrefix(const std::string & str, const std::string & prefix)
{
#if (__GNUC__ > 2)
	return (str.length() >= prefix.length() &&
		str.compare(0, prefix.length(), prefix) == 0);
#else
	return (str.length() >= prefix.length() &&
		str.compare(prefix, 0, prefix.length()) == 0);
#endif
}


bool IsSuffix(const std::string & str, const std::string & suffix)
{
#if (__GNUC__ > 2)
	return (str.length() >= suffix.length() &&
		str.compare(str.length() - suffix.length(), suffix.length(), suffix) == 0);
#else
	return (str.length() >= suffix.length() &&
		str.compare(suffix, str.length() - suffix.length(), suffix.length()) == 0);
#endif
}


void ToLower(std::string & str)
{
	ToLower(str.begin(), str.end());
}

void ToLower(std::string::iterator start, std::string::iterator end)
{
	std::string::iterator p = start;
	for (;p != end; ++p)
	{
		*p = tolower(*p);
	}
}

std::string ToLowerCopy (const std::string & str)
{
	std::string local(str);
	ToLower(local);
	return local;
}

void Trim(std::string & str)
{
	if (str.empty())
		return;
	
	int count = 0;
	std::string::size_type pos = 0;
	while (pos < str.length() && isspace(str[pos]))
	{
		++count;
		++pos;
	}
	
	if (0 < count)
		str.erase(0, count);
	
	if (str.empty())
		return;
	
	count = 0;
	pos = str.length() - 1;
	while (isspace(str[pos]))
	{
		++count;
		if (pos == 0)
			break;
		else
			--pos;
	}

	if (0 < count)
		str.erase(str.length() - count);
}

std::string TrimCopy (const std::string & str)
{
	std::string local(str);
	Trim(local);
	return local;
}



void EncodeToXml (std::string & str)
{
	str = EncodeToXmlCopy(str);
	return;
}

std::string EncodeToXmlCopy (const std::string & str)
{
	std::string convertedString;
	
	int length = str.length();
	for(int i=0;i<length;i++)
	{
		switch(str.at(i))
		{
			case '&':
				convertedString.append("&amp;");
				break;
			case '\'':
				convertedString.append("&apos;");
				break;
			case '\"':
				convertedString.append("&quot;");
				break;
			case '<':
				convertedString.append("&lt;");
				break;
			case '>':
				convertedString.append("&gt;");
				break;
			default:
				convertedString.push_back(str.at(i));
		}
	}
	return convertedString;

}

}




