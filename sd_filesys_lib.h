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
		File(const char *n) {
		//strncpy(name_, n, 12);
		int i=0;
		while(i<12 && n[i]!=0) {
			name_[i]=n[i];
			i++;
			}
		name_[i]='\0';	
		}
		File(void){
		name_[0]=0;	
		}
		size_t write(block_data_t *buf, size_t size) {
		size_t s=size;
		//Code goes here...
		return s;	
		}
		size_t read() {
		//Code goes here...
		//This function will return the next byte.
		return 1;
		}
		
		int peek() {
			//Code goes here...
			//It will return the next byte.This will be differ from  
			//read function as it will read a byte from the file  
			//without advancing to the next one.
			return 1;
			
			}
		int available() {
			//Code goes here...
			//it will check if there are any bytes available for 
			//reading from the file and return the the number of 
			//bytes available
			return 1; 
			}
		bool seek(unsigned int pos) {
			//Code goes here...
			//Seek to a new position in the file, which must be 
			//between 0 and the size of the file
			//Will return true for success and false for failure.
			return true;
			}
		unsigned int position() {
			//Code goes here...
			//It will give the current position within the file.
			return 1;	
			}
		
		unsigned int size() {
			//Code goes here...
			//It will give the size of the file in bytes.
			return 10;
			}
		void close() {
			//Code goes here...
			//Close the file, and ensure that any data 
			// written to it is physically saved to theSD card.
			}
		bool is_directory(void){
			//Code goes here...
			//Return true if file is directory otherwise false.
			return false;
			}
		File* open_next_file(uint8_t mode) {
			//Code goes here...
			//This function will reports the next file or folder 
			//in a directory.This would be done by iterating through 
			//directory entries and reporting the next file or 
			//folder in the directory.
			return this;
	
			}
		
		void rewind_directory(void) {
			//Code goes here...
			//This will bring back to the first file in the directory.
			}
		char *name(){
			return name_;
			}
	private:
		char name_[13];
		//friend class SdFileSystemLibrary;
		int file_open_mode;
};

template<typename OsModel_P> class SdFileSystemLibrary
{
	public:
		typedef OsModel_P OsModel;
		bool begin() {
			//Code goes here...
			//Initializes the SD library and card.
			//Will return true for success and false for failure.
			return false;
			}
		
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
	private:
		int file_open_mode_;		
		// File<OsModel> file_;
};
}		
#endif
