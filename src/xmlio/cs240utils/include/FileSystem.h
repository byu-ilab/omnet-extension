#ifndef FILE_SYSTEM_H
#define FILE_SYSTEM_H

#include <string>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>


//!@defgroup filesystem Filesystem Utils
//!Functions to assist in working with the file system
//!@li FileSystem::FileExists
//!@li FileSystem::DirectoryExists
//!@li FileSystem::CompareFileTimestamps


//!@ingroup filesystem
namespace FileSystem
{
	//!@return true if the specified file exists, and false otherwise.
	bool FileExists(const std::string & path);
	
	//!@return true if the specified directory exists, and false otherwise.
	bool DirectoryExists(const std::string & path);

	//!Compares the last modification times of file1 and file2. Returns one of the following values:
	//!@li If file1 has been modified more recently than file2, returns a value greater than zero (> 0)
	//!@li If file2 has been modified more recently than file1, returns a value less than zero (< 0)
	//!@li If file1 and file2 were last modified at the same time, returns zero (0)
	//!
	//!@throw CS240Exception if either file1 or file2 does not exist
	int CompareFileTimestamps(const std::string & path1, const std::string & path2);
}


#endif
