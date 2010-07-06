#include <sstream>
#include <iostream>

#include "FileSystem.h"
#include "CS240Exception.h"
#include "UnitTest.h"

using namespace std;

namespace FileSystem
{

namespace
{
	bool ReadFileInfo(const string & path, struct stat * info)
	{
		return (::stat(path.c_str(), info) == 0);
	}
	
	string FileDoesNotExistErrorMessage(const string & path)
	{
		return string("file does not exist: ")+path;
	}
}

bool FileExists(const string & path)
{
	struct stat info;
	return (ReadFileInfo(path, &info) && S_ISREG(info.st_mode));
}

bool DirectoryExists(const string & path)
{
	struct stat info;	
	return (ReadFileInfo(path, &info) && (info.st_mode & S_IFDIR));
}

int CompareFileTimestamps(const string & path1, const string & path2)
{
	struct stat info1;
	struct stat info2;
	
	if (!ReadFileInfo(path1, &info1))
		throw CS240Exception(FileDoesNotExistErrorMessage(path1));
	
	if (!ReadFileInfo(path2, &info2))
		throw CS240Exception(FileDoesNotExistErrorMessage(path2));
	
	if (info1.st_mtime < info2.st_mtime)
		return -1;
	else if (info1.st_mtime > info2.st_mtime)
		return 1;
	else
		return 0;
}

}

