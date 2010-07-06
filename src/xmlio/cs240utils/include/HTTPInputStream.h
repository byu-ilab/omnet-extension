#ifndef HTTP_INPUT_STREAM_H
#define HTTP_INPUT_STREAM_H

#include <string>
#include "InputStream.h"

enum tHTTPResponse
{
	kHTTPSuccess,
	kHTTPRedirect,
	kHTTPUnknown
};

//!@ingroup io
//!handles downloading HTTP URLS
class HTTPInputStream : public InputStream {
public:
	HTTPInputStream(const std::string & url);
	virtual ~HTTPInputStream();

	virtual char Peek();
	virtual char Read();
	virtual void Close();

	virtual bool IsOpen() const;
	virtual bool IsDone() const;
	virtual std::string GetLocation() const
	{
		return location;
	}

private:
	void Init();
	void ParseURL(const std::string & url);
	void OpenConnection();
	void SendRequest();
	tHTTPResponse ParseHTTPStatusLine(std::string & reasonPhrase);
	void ParseHTTPHeaders();
	void ParseContentLength(const std::string & line);
	void ParseLocation(const std::string & line);
	void ReadHeaderLine(std::string & line);
	void ReadByte();
	bool IsSuccessfulResponse(int statusCode);
	bool IsRedirectResponse(int statusCode);
	void DumpResponse();

	std::string host;
	int port;
	std::string path;
	int sockfd;
	int contentLength;
	std::string location;
	int numRead;
	bool done;
	char nextByte;
};


#endif
