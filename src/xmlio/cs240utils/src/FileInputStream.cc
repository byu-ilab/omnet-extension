#include <sys/types.h>
#include <sys/stat.h>

#include "FileInputStream.h"
#include "CS240Exception.h"




FileInputStream::FileInputStream(const std::string & url)
{
	fileSize = 0;
	numRead = 0;

	ParseURL(url);
	OpenFile();
}

FileInputStream::~FileInputStream()
{
	Close();
}

bool FileInputStream::IsOpen() const
{
	return file.is_open();
}

bool FileInputStream::IsDone() const
{
	return (numRead == fileSize);
}

char FileInputStream::Read()
{
	if (!IsOpen())
		throw IllegalStateException("stream is not open");
	else if (IsDone())
		throw IllegalStateException("stream is done");
	else
	{
		char c;
		file.get(c);

		if (file.fail())
			throw FileException(std::string("error reading from file ") + fileName);

		++numRead;
		return c;
	}
}

char FileInputStream::Peek() 
{
	if (!IsOpen())
		throw IllegalStateException("stream is not open");
	else if (IsDone())
		throw IllegalStateException("stream is done");
	else
	{
		char c=file.peek();

		if (file.fail())
			throw FileException(std::string("error reading from file ") + fileName);

		return c;
	}
}

void FileInputStream::Close()
{
	if (IsOpen())
		file.close();
}

void FileInputStream::ParseURL(const std::string & url)
{
	const std::string prefix = "file:";
	fileName = url.substr(prefix.length());
}

void FileInputStream::OpenFile()
{
	struct stat buf;
	if (stat(fileName.c_str(), &buf) < 0)
		throw FileException(std::string("could not determine size of file ") + fileName);
	fileSize = buf.st_size;

	file.open(fileName.c_str());
	if (!IsOpen() || file.fail())
		throw FileException(std::string("could not open file ") + fileName);
}

