#include <sstream>
#include <iostream>
#include <cctype>
#include <cstdlib>
#include <cstring>
#include <unistd.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netdb.h>
#include <netinet/in.h>
#include "CS240Exception.h"
#include "StringUtil.h"

#include "HTTPInputStream.h"

using namespace std;


namespace
{
	bool IsSuccessfulResponse(int statusCode)
	{
		static const int SC_OK = 200;
		static const int SC_NON_AUTHORITATIVE_INFORMATION = 203;
	
		return (statusCode == SC_OK ||
			statusCode == SC_NON_AUTHORITATIVE_INFORMATION);
	}

	bool IsRedirectResponse(int statusCode)
	{
		static const int SC_MOVED_PERMANENTLY = 301;
		static const int SC_FOUND = 302;
		static const int SC_SEE_OTHER = 303;
		static const int SC_TEMPORARY_REDIRECT = 307;
	
		return (statusCode == SC_MOVED_PERMANENTLY ||
				statusCode == SC_FOUND ||
				statusCode == SC_SEE_OTHER ||
				statusCode == SC_TEMPORARY_REDIRECT);
	}

	tHTTPResponse ConvertHTTPStatus (int statuscode)
	{
		if (IsSuccessfulResponse(statuscode))
			return kHTTPSuccess;
		else if (IsRedirectResponse(statuscode))
			return kHTTPRedirect;
		else
			return kHTTPUnknown;
	}
}

HTTPInputStream::HTTPInputStream(const std::string & url)
{
	
	// NOTE: Good test cases for redirect handling:
	//			http://www.visio.com
	//			http://www.byu.edu
	//			http://www.utahjazz.com

	const int MAX_REDIRECTS = 5;

	// following HTTP redirects requires us to connect more than once,
	// thus the need for the loop below

	string currentURL(url);
	int redirects = 0;

	bool stillRedirecting = true;
	while (stillRedirecting)
	{
		string reasonPhrase;

		Init();

		ParseURL(currentURL);
		//***cout << "[host=" << host << ", port=" << port << ", path=" << path << "]" << endl;
	
		OpenConnection();
		//***cout << "[connection established]" << endl;
	
		SendRequest();
		
		tHTTPResponse response = ParseHTTPStatusLine(reasonPhrase);
		//cout << "[status-code=" << statusCode << ", reason-phrase=" << reasonPhrase << "]" << endl;
		
		ParseHTTPHeaders();

		switch (response)
		{
			case kHTTPSuccess:
				stillRedirecting = false;
				break;

			case kHTTPRedirect:
				if (location.empty())
					throw NetworkException("no Location for HTTP redirect: " + reasonPhrase);
				if (++redirects <= MAX_REDIRECTS)
				{
					currentURL = location;
					Close();
				}
				else
					throw NetworkException("HTTP redirect limit exceeded");
				break;

			case kHTTPUnknown:
				throw NetworkException(string("HTTP request failed: ") + reasonPhrase);
				break;
		}
	}
	location = currentURL;

	ReadByte(); 
}

void HTTPInputStream::Init() {
	host = "";
	port = 80;
	path = "/";
	sockfd = -1;
	contentLength = -1;
	location = "";
	numRead = 0;
	done = false;
	nextByte = 0;	
}

HTTPInputStream::~HTTPInputStream()
{
	Close();
}

bool HTTPInputStream::IsOpen() const
{
	return (0 <= sockfd);
}

bool HTTPInputStream::IsDone() const
{
	return done;
}

void HTTPInputStream::ReadByte()
{
	char c;
	int nread = read(sockfd, &c, 1);
	if (nread == 1)
	{
		++numRead;
		nextByte = c;
	}
	else if (nread == 0)
	{
		//***cout << "[end of stream - contentLength: " << contentLength << ", numRead: " << numRead << "]" << endl;
		done = true;
		nextByte = 0;
		if (0 <= contentLength && numRead != contentLength)
		{
			throw NetworkException("number of bytes read differs from content length");
		}
	}
	else
	{
		throw NetworkException("error occurred reading HTTP response");
	}
}

char HTTPInputStream::Peek()
{
	if (!IsOpen())
		throw IllegalStateException("stream is not open");
	else if (IsDone())
		throw IllegalStateException("stream is done");
	else
	{
		return nextByte;
			 
	}
}

char HTTPInputStream::Read()
{
	if (!IsOpen())
		throw IllegalStateException("stream is not open");
	else if (IsDone())
		throw IllegalStateException("stream is done");
	else
	{
		char c = nextByte;
		ReadByte();
		return c;	 
	}
}


void HTTPInputStream::Close()
{
	if (IsOpen())
	{
		close(sockfd);
		sockfd = -1;
	}
}

void HTTPInputStream::ParseURL(const std::string & url)
{
	const string prefix = "http://";

	string::const_iterator p = url.begin() + prefix.length();

	for (; p != url.end() && *p != ':' && *p != '/'; ++p)
		host.push_back(*p);

	if (host.empty())
		throw InvalidURLException(url);
	else if (p == url.end())
		return;

	if (*p == ':')
	{
		++p;
		string portStr = "";
		for (; p != url.end() && isdigit(*p); ++p)
			portStr.push_back(*p);
		port = atoi(portStr.c_str());
	}

	if (p == url.end())
		return;
	else if (*p != '/')
		throw InvalidURLException(url);

	int idx = p - url.begin();
	path = url.substr(idx); 
}

void HTTPInputStream::OpenConnection()
{
	struct hostent *hostData = gethostbyname(host.c_str());
	if (hostData == NULL || hostData->h_addr == NULL)
	{
		throw NetworkException(string("could not resolve host name ") + host);
	}
	
	struct sockaddr_in hostAddr;
	bzero(&hostAddr, sizeof(hostAddr));
	hostAddr.sin_family = AF_INET;
	hostAddr.sin_port = htons(port);
	memcpy(&hostAddr.sin_addr, hostData->h_addr, hostData->h_length);

	int s = socket(AF_INET, SOCK_STREAM, 0);
	if (s < 0)
	{
		throw NetworkException("could not create socket");
	}

	if (connect(s, (struct sockaddr *)&hostAddr, sizeof(hostAddr)) < 0)
	{
		close(s);
		throw NetworkException(string("could not connect to host ") + host);
	}

	sockfd = s;
}

void HTTPInputStream::SendRequest()
{
	
	ostringstream request;
	request << "GET " << path;
	request << " HTTP/1.0\r\n";
	request << "Host: " << host << ":" << port << "\r\n\r\n";
	
	string completeRequest = request.str();

	if (write(sockfd, completeRequest.c_str(), completeRequest.length()) != (int)completeRequest.length())
		throw NetworkException("could not send HTTP request");
}

tHTTPResponse HTTPInputStream::ParseHTTPStatusLine(std::string & reasonPhrase)
{
	string line;
	ReadHeaderLine(line);

	unsigned int firstSpacePos = line.find(' ', 0);
	if (firstSpacePos == string::npos)
		throw NetworkException(string("invalid HTTP status line: ") + line);

	unsigned int secondSpacePos = line.find(' ', firstSpacePos + 1);
	if (secondSpacePos == string::npos)
		throw NetworkException(string("invalid HTTP status line: ") + line);

	unsigned int statusCodePos = firstSpacePos + 1;
	string statusCodeStr = line.substr(statusCodePos, (secondSpacePos - statusCodePos)); 
	int statusCode = atoi(statusCodeStr.c_str());
	if (statusCode < 100)
		throw NetworkException(string("invalid HTTP status line: ") + line);

	unsigned int reasonPhrasePos = secondSpacePos + 1;
	reasonPhrase = line.substr(reasonPhrasePos);

	return ConvertHTTPStatus (statusCode);
}

void HTTPInputStream::ParseHTTPHeaders()
{
	while (true)
	{
		string line;
		ReadHeaderLine(line);

		if (line.empty())
			break;
 		else if (line.find("Content-Length:") == 0)
 			ParseContentLength(line);
		else if (line.find("Location:") == 0)
 			ParseLocation(line);
	}
}

void HTTPInputStream::ParseContentLength(const std::string & line)
{
	contentLength = -1;

	const string prefix = "Content-Length:";

	string::const_iterator p = line.begin() + prefix.length();
	for (; p != line.end() && isspace(*p); ++p)
		;
	if (p == line.end())
		throw NetworkException(string("invalid HTTP content length header: ") + line);

	string length;
	for (; p != line.end() && isdigit(*p); ++p)
		length.push_back(*p);
	if (p != line.end())
		throw NetworkException(string("invalid HTTP content length header: ") + line);

	contentLength = atoi(length.c_str());
}

void HTTPInputStream::ParseLocation(const std::string & line)
{
	const string prefix = "Location:";

	string::const_iterator p = line.begin() + prefix.length();
	for (; p != line.end() && isspace(*p); ++p)
		;
	if (p == line.end())
		throw NetworkException(string("invalid HTTP location header: ") + line);

	location = "";
	std::copy(p, line.end(), std::back_inserter(location));

	if (!StringUtil::IsPrefix(location, "http:"))
		throw NetworkException(string("Unsupported redirect location: ") + location);
}

void HTTPInputStream::ReadHeaderLine(std::string & line)
{

	/*** temporary proxy server bug work-around ***/

	while (true)
	{
		char c;
		int nread = read(sockfd, &c, 1);
		if (nread == 1)
		{
			switch (c)
			{
				case '\r':
					// skip carriage returns
					break;

				case '\n':
					// line feed indicates end of header
					return;

				default:
					line.push_back(c);
					break;
			}
		}
		else
			throw NetworkException("invalid HTTP header");
	}

	/*** this is the real code ***/

	/***
	bool gotCR = false;
	while (true) {
		char c;
		int nread = read(sockfd, &c, 1);
		if (nread == 1) {
			if (gotCR) {
	if (c == '\n') {
		return;
	}
	else {
		throw NetworkException("invalid HTTP header");
	}
			}
			else if (c == '\r') {
	gotCR = true;
			}
			else if (c == '\n') {
	throw NetworkException("invalid HTTP header");	
			}
			else {
	line.push_back(c);
			}
		}
		else {
			throw NetworkException("invalid HTTP header");
		}
	}
	***/
}

void HTTPInputStream::DumpResponse()
{
	while (!IsDone()) {
		char c = Read();
		cout << (char)c;
	}
}

