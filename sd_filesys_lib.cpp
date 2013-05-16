#include "sd_filesys_lib.h"
bool SdFileSystemLibrary::begin()
{
	//Code goes here...
	//Initializes the SD library and card.
	//Will return true for success and false for failure.
	return false;
}
// --------------------------------------------------------------------
File SdFileSystemLibrary::open(const char *filename, uint8_t mode)
{
	File f(filename);
	f.file_open_mode= mode;//as SdFileSystemLibrary is friend class for File class.
	//Here only for now,I have created a new file,later this method  
	//will open the supplied file path for reading or writing(append also).
	//If the file does not exist and it is opened for writing,the file
	//will be created.
    return f;
}
// --------------------------------------------------------------------
bool SdFileSystemLibrary::exists(const char *filepath)
{
	//Code goes here...
	//Test if file or directory exists on SD card.
	//Will return true for success and false for failure.
	return true;
}
// --------------------------------------------------------------------
bool SdFileSystemLibrary::mkdir(const char *filepath)
{
	//Code goes here...
	//Create a directory on SD card.
	//Will return true for success and false for failure.
	return true;
}
// --------------------------------------------------------------------
bool SdFileSystemLibrary::remove(const char *filepath)
{
	//Code goes here...
	//Remove a file from SD card.
	//Will return true for success and false for failure.
	return true;
}
// --------------------------------------------------------------------
bool SdFileSystemLibrary::rmdir(const char *filepath)
{
	//Code goes here...
	//Remove a directory from SD card.
	//Will return true for success and false for failure.
	return true;
}
