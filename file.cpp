#include "sd_filesys_lib.h"
//#include <string.h>
namespace wiselib
{
template <typename OsModel_P> File<OsModel_P>::File(const char *n)
{
    //strncpy(name_, n, 12);
	int i=0;
	while(i<12 && n[i]!=0)
		{
		name_[i]=n[i];
		i++;
		}
	name_[i]='\0';
		
}
// --------------------------------------------------------------------
template <typename OsModel_P>File<OsModel_P>::File(void)
{
	name_[0]=0;
}
// --------------------------------------------------------------------
template <typename OsModel_P> typename File<OsModel_P>::size_t
File<OsModel_P>::write(File<OsModel_P>::block_data_t *buf,File<OsModel_P>::size_t size)
{
	size_t s=size;
	//Code goes here...
	return s;
}
// --------------------------------------------------------------------
template <typename OsModel_P> typename File<OsModel_P>::size_t File<OsModel_P>::read()
{
	//Code goes here...
	//This function will return the next byte.
	return 1;	
}
// --------------------------------------------------------------------
template <typename OsModel_P> int File<OsModel_P>::peek()
{
	//Code goes here...
	//It will return the next byte.This will be differ from  
	//read function as it will read a byte from the file  
	//without advancing to the next one.
	return 1;
}
// --------------------------------------------------------------------
template <typename OsModel_P> int File<OsModel_P>::available()
{
	//Code goes here...
	//it will check if there are any bytes available for 
	//reading from the file and return the the number of 
	//bytes available
	return 1; 
}
// --------------------------------------------------------------------
template <typename OsModel_P> bool File<OsModel_P>::seek(unsigned int pos)
{
	//Code goes here...
	//Seek to a new position in the file, which must be 
	//between 0 and the size of the file
	//Will return true for success and false for failure.
	return true;
}
// --------------------------------------------------------------------
template <typename OsModel_P> unsigned int File<OsModel_P>::position()
{
	//Code goes here...
	//It will give the current position within the file.
	return 1;
}
// --------------------------------------------------------------------
template <typename OsModel_P> unsigned int File<OsModel_P>::size()
{
	//Code goes here...
	//It will give the size of the file in bytes.
	return 10;
}
// --------------------------------------------------------------------
template <typename OsModel_P> void File<OsModel_P>::close()
{
	//Code goes here...
	//Close the file, and ensure that any data 
	// written to it is physically saved to theSD card.
}
// --------------------------------------------------------------------
template <typename OsModel_P> bool File<OsModel_P>::is_directory(void)
{
	//Code goes here...
	//Return true if file is directory otherwise false.
	return false;
}
// --------------------------------------------------------------------
template <typename OsModel_P> File<OsModel_P>* File<OsModel_P>::open_next_file(uint8_t mode)
{
	//Code goes here...
	//This function will reports the next file or folder 
	//in a directory.This would be done by iterating through 
	//directory entries and reporting the next file or 
	//folder in the directory.
	return this;
}
// --------------------------------------------------------------------
template <typename OsModel_P> void File<OsModel_P>::rewind_directory(void)
{
	//Code goes here...
	//This will bring back to the first file in the directory.
}
// --------------------------------------------------------------------
template <typename OsModel_P> char* File<OsModel_P>::name()
{
	return name_;
}
 template class File< PCOsModel >;
}
