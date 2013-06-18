#include <stdint.h>
#include <stddef.h>
#ifndef __SD_FILE_SYSTEM_LIBRARY_H__
#define __SD_FILE_SYSTEM_LIBRARY_H__
namespace wiselib
{
template<typename OsModel_P>
class File
{
	public:
		typedef OsModel_P OsModel;
		typedef typename OsModel_P::size_t size_t;
		typedef typename OsModel_P::block_data_t block_data_t;
		File(const char *n);
		File(void);
		//Write data to the file. Here template is used so that
		//user can write data of any datatype.
		size_t write(block_data_t *buf, size_t size);
		//Read a byte from the file and return the next byte.
		size_t read();
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
		char *name();
	private:
		char name_[13];
		//friend class SdFileSystemLibrary;
		int file_open_mode;
};

template<typename OsModel_P> class SdFileSystemLibrary
{
	public:
		typedef OsModel_P OsModel;
		//Initializes the SD library and card.
		bool begin();
		//Open a file on the SD card.Return object of File type.
		File<OsModel> open(const char *filename, uint8_t mode)
		{
		File<OsModel> f(filename);
		//f.file_open_mode= mode;//as SdFileSystemLibrary is friend class for File class.
		//Here only for now,I have created a new file,later this method  
		//will open the supplied file path for reading or writing(append also).
		//If the file does not exist and it is opened for writing,the file
		//will be created.
		return f;	
		}
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
		// File<OsModel> file_;
};
}		
#endif
