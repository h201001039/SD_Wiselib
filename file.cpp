#include "sd_filesys_lib.h"
//#include <string.h>
File::File(const char *n)
{
    //strncpy(name_, n, 12);
    name_[12]=0;	
}
// --------------------------------------------------------------------
File::File(void)
{
	name_[0]=0;
}
// --------------------------------------------------------------------
template <typename T > size_t File::write(T *buf, size_t size)
{
	size_t s=size;
	//Code goes here...
	return s;
}
// --------------------------------------------------------------------
int File::read()
{
	//Code goes here...
	//This function will return the next byte.
	return 1;	
}
// --------------------------------------------------------------------
int File::peek()
{
	//Code goes here...
	//It will return the next byte.This will be differ from  
	//read function as it will read a byte from the file  
	//without advancing to the next one.
	return 1;
}
// --------------------------------------------------------------------
int File::available()
{
	//Code goes here...
	//it will check if there are any bytes available for 
	//reading from the file and return the the number of 
	//bytes available
	return 1; 
}
// --------------------------------------------------------------------
bool File::seek(unsigned int pos)
{
	//Code goes here...
	//Seek to a new position in the file, which must be 
	//between 0 and the size of the file
	//Will return true for success and false for failure.
	return true;
}
// --------------------------------------------------------------------
unsigned int File::position()
{
	//Code goes here...
	//It will give the current position within the file.
	return 1;
}
// --------------------------------------------------------------------
unsigned int File::size()
{
	//Code goes here...
	//It will give the size of the file in bytes.
	return 10;
}
// --------------------------------------------------------------------
void File::close()
{
	//Code goes here...
	//Close the file, and ensure that any data 
	// written to it is physically saved to theSD card.
}
// --------------------------------------------------------------------
bool File::is_directory(void)
{
	//Code goes here...
	//Return true if file is directory otherwise false.
	return false;
}
// --------------------------------------------------------------------
File* File::open_next_file(uint8_t mode)
{
	//Code goes here...
	//This function will reports the next file or folder 
	//in a directory.This would be done by iterating through 
	//directory entries and reporting the next file or 
	//folder in the directory.
	return this;
}
// --------------------------------------------------------------------
void File::rewind_directory(void)
{
	//Code goes here...
	//This will bring back to the first file in the directory.
}
