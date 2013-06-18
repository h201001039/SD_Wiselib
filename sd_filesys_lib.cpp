#include "sd_filesys_lib.h"
namespace wiselib
{
template <typename OsModel_P> bool SdFileSystemLibrary<OsModel_P>::begin()
{
	//Code goes here...
	//Initializes the SD library and card.
	//Will return true for success and false for failure.
	return false;
}
// --------------------------------------------------------------------
template <typename OsModel_P> bool SdFileSystemLibrary<OsModel_P>::exists(const char *filepath)
{
	//Code goes here...
	//Test if file or directory exists on SD card.
	//Will return true for success and false for failure.
	return true;
}
// --------------------------------------------------------------------
template <typename OsModel_P> bool SdFileSystemLibrary<OsModel_P>::mkdir(const char *filepath)
{
	//Code goes here...
	//Create a directory on SD card.
	//Will return true for success and false for failure.
	return true;
}
// --------------------------------------------------------------------
template <typename OsModel_P> bool SdFileSystemLibrary<OsModel_P>::remove(const char *filepath)
{
	//Code goes here...
	//Remove a file from SD card.
	//Will return true for success and false for failure.
	return true;
}
// --------------------------------------------------------------------
template <typename OsModel_P> bool SdFileSystemLibrary<OsModel_P>::rmdir(const char *filepath)
{
	//Code goes here...
	//Remove a directory from SD card.
	//Will return true for success and false for failure.
	return true;
}
template class SdFileSystemLibrary< PCOsModel >;
}
