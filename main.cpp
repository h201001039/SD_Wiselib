#include <iostream>
#include "sd_filesys_lib.h"
int main()
{
	std::cout  << std::endl;
	SdFileSystemLibrary sd;
	File f=sd.open("harsh",1);
	std::cout << "Name of created file is " << f.name() <<std::endl;
	if(sd.mkdir("/Home"))
	std::cout << "Hurrey!! I have created a directory.;)" << std::endl;
	std::cout << "Size of file harsh is "<<f.size()  << std::endl;
	File *x=f.open_next_file(1);
	if((x->is_directory()))
	std::cout << "next file of harsh is a directory "  << std::endl;
	else 
	std::cout << "next file of harsh is not a directory "  << std::endl;
	std::cout << "... "  << std::endl;
	std::cout << "... "  << std::endl;
	return 0;

}
