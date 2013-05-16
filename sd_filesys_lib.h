#include <stdint.h>
#include <stddef.h>
#ifndef __SD_FILE_SYSTEM_LIBRARY_H__
#define __SD_FILE_SYSTEM_LIBRARY_H__

class File
{
	public:
		File(const char *n);
		File(void);
		//Write data to the file. Here template is used so that
		//user can write data of any datatype.
		template<typename T> size_t write(T *buf, size_t size);
		//Read a byte from the file and return the next byte.
		int read();
		//Read a byte from the file without advancing to the next one
		int peek();
		//Check if there are any bytes available for reading from the file. 
		int available();
		//Seek to a new position in the file, 
		//which must be between the start and end of the file.
		bool seek(unsigned int pos);
		//Get the current position within the file.
		unsigned int position();
		//Get the size of the file. 
		unsigned int size();
		//Close the file, and ensure that any data written 
		//to it is physically saved to theSD card.
		void close();
		//Report if current file is directory or not.
		bool is_directory(void);
		//Reports the next file or folder in a directory.
		File* open_next_file(uint8_t mode);
		//Bring back to the first file in the directory.
		void rewind_directory(void);
		
	private:
		char name_[13];
		friend class SdFileSystemLibrary;
		int file_open_mode;
};

class SdFileSystemLibrary
{
	public:
		//Initializes the SD library and card.
		bool begin();
		//Open a file on the SD card.Return object of File type.
		File open(const char *filename, uint8_t mode);
		//Test if file or directory exists on SD card
		bool exists(const char *filepath);
		//Create a directory on SD card.
		bool mkdir(const char *filepath);
		//Remove a file from SD card.
		bool remove(const char *filepath);
		//Remove a directory from SD card.
		bool rmdir(const char *filepath);
	private:
		int file_open_mode_;		
		File file_;
};		
#endif
