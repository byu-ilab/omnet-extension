#ifndef FILE_INPUT_STREAM_H
#define FILE_INPUT_STREAM_H

#include <string>
#include <fstream>
#include "InputStream.h"

//!@ingroup io
//!Handles loading files from the local filesystem
class FileInputStream : public InputStream
{
public:
	FileInputStream(const std::string & url);
	virtual ~FileInputStream();

	virtual char Peek();
	virtual char Read();
	virtual void Close();

	virtual bool IsOpen() const;
	virtual bool IsDone() const;
	virtual std::string GetLocation() const
	{
		return "file:"+fileName;
	}

private:
	std::string fileName;
	std::ifstream file;
	off_t fileSize;
	off_t numRead;

	void ParseURL(const std::string & url);
	void OpenFile();
};


#endif
