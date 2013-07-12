#include <stdint.h>
#include <stddef.h>
//#include "file_block_memory.h"
#ifndef __SD_FILE_SYSTEM_LIBRARY_H__
#define __SD_FILE_SYSTEM_LIBRARY_H__
#include "pc_os_model.h"
namespace wiselib
{
template<typename OsModel_P,typename BlockMemory_P = typename OsModel_P::BlockMemory>
class File
{
	public:
		typedef OsModel_P OsModel;
		typedef typename OsModel::size_t size_t;
		typedef typename OsModel::block_data_t block_data_t;
		typedef BlockMemory_P BlockMemory;
		File(const char *n, unsigned int file_cluster_no) {
		//strncpy(name_, n, 12);
		int i=0;
		while(i<12 && n[i]!=0) {
			name_[i]=n[i];
			i++;
			}
		name_[i]='\0';
		file_cluster_no=cluster_no;	
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
		BlockMemory fd;
		unsigned int file_cluster_no;
		
};
template<typename OsModel_P,typename BlockMemory_P = typename OsModel_P::BlockMemory>
class SdFileSystemLibrary
{
	public:
		typedef OsModel_P OsModel;
		typedef typename OsModel::size_t size_t;
		typedef typename OsModel::block_data_t block_data_t;
		typedef BlockMemory_P BlockMemory;
		enum {
				BLOCK_SIZE = 512,
				SIZE = (1024UL * 1024UL * 1024UL / 512UL), ///< #blocks for 1GB 
			};
			
			enum {
				SUCCESS = OsModel::SUCCESS,
				ERR_UNSPEC = OsModel::ERR_UNSPEC
			};
			unsigned int RootDirSectors;
			unsigned int FATSz;
			unsigned int FirstDataSector;
			unsigned int TotSec;
			unsigned long DataSec;
			unsigned long CountofClusters;
			unsigned int BPB_TotSec16;
			unsigned int BPB_NumFATs;
			unsigned int BPB_SecPerClus;
			unsigned int FATOffset;
			unsigned int ThisFATSecNum;
			unsigned int ThisFATEntOffset;
			unsigned int FirstRootDirSecNum;
			
			typedef struct BPB_P
         {
		 unsigned char BS_jmpBoot[3];
		 unsigned char BS_OEMName[8];
		 unsigned short BPB_BytsPerSec;
		 unsigned char BPB_SecPerClus;
		 unsigned short BPB_RsvdSecCnt;
		 unsigned char BPB_NumFATs;
		 unsigned short BPB_RootEntCnt;
		 unsigned short BPB_TotSec16;
		 unsigned char BPB_Media;
		 unsigned short BPB_FATSz16;
		 unsigned short BPB_SecPerTrk;
		 unsigned short BPB_NumHeads;
		 unsigned int BPB_HiddSec;
		 unsigned int BPB_TotSec32;
		 } BPB;
		 
		typedef struct BS_16_P
		{
		unsigned char BS_DrvNum;
		unsigned char BS_Reserved1;
		unsigned char BS_BootSig;
		unsigned int BS_VolID;
		unsigned char BS_VolLab[11];
		unsigned char BS_FilSysType[8]; 	
		}BS_16;
		
		typedef struct BS_32_P
		{
		unsigned int BPB_FATSz32;
		unsigned short BPB_ExtFlags;
		unsigned short BPB_FSVer;
		unsigned int BPB_RootClus;
		unsigned short BPB_FSInfo;
		unsigned short BPB_BkBootSec;
		unsigned char BPB_Reserved[12];
		unsigned char BS_DrvNum;
		unsigned char BS_Reserved1;
		unsigned char BS_BootSig;
		unsigned int BS_VolID;
		unsigned char BS_VolLab[11];
		unsigned char BS_FilSysType[8]; 	
		}BS_32;
			
		void init() {
			CountofClusters=0;
			TotSec=0;
			DataSec=0;
			int i=0;
			fd.init("virtual_sd.img");
			for(i=0;i<512;i++)
			buffer[i]=0;
			//int a=fd.read(buffer,0);
			
			printf("harsh\n");
			 int a=fd.read(buffer,0);
			for(i=0;i<512;i++)
			{
			printf("%x  ",buffer[i]);
			if(i%16==0 && i!=0)
			printf("\n");
		}
			if(a==1)
			{
			printf("harsh\n");
			for(i=0;i<3;i++)
			b1.BS_jmpBoot[i]=buffer[i];
			for(i=3;i<11;i++)
			b1.BS_OEMName[i]=buffer[i];
			//std::cout<<"b1.BS_OEMName"<<b1.BS_OEMName<<std::endl;
			b1.BPB_BytsPerSec=buffer[12]*256+buffer[11];
			//std::cout<<"b1.BPB_BytsPerSec"<<b1.BPB_BytsPerSec<<std::endl;
			printf("b1.BPB_BytsPerSec=%d\n",b1.BPB_BytsPerSec);
			b1.BPB_SecPerClus=buffer[13];
			printf("b1.BPB_SecPerClus=%d\n",b1.BPB_SecPerClus);
			b1.BPB_RsvdSecCnt=buffer[15]*256+buffer[14];
			printf("b1.BPB_RsvdSecCnt=%d",b1.BPB_RsvdSecCnt);
			b1.BPB_NumFATs=buffer[16];
			printf("b1.BPB_NumFATs=%d\n",b1.BPB_NumFATs);
			b1.BPB_RootEntCnt=buffer[18]*256+buffer[17];
			printf("b1.BPB_RootEntCnt=%d\n",b1.BPB_RootEntCnt);
			b1.BPB_TotSec16=buffer[20]*256+buffer[19];
			printf("b1.BPB_TotSec16=%d\n",b1.BPB_TotSec16);
			b1.BPB_Media=buffer[21];
			printf("b1.BPB_Media=%d\n",b1.BPB_Media);
			b1.BPB_FATSz16=buffer[23]*256+buffer[22];
			printf("b1.BPB_FATSz16=%d\n",b1.BPB_FATSz16);
			b1.BPB_SecPerTrk=buffer[25]*256+buffer[24];
			printf("b1.BPB_SecPerTrk=%d \n ",b1.BPB_SecPerTrk);
			b1.BPB_NumHeads=buffer[27]*256+buffer[26];
			printf("b1.BPB_NumHeads=%d\n  ",b1.BPB_NumHeads);
			b1.BPB_HiddSec=((buffer[31]*256+buffer[30])*256+buffer[29])*256+buffer[28];
			printf("b1.BPB_HiddSec=%d\n  ",b1.BPB_HiddSec);
			b1.BPB_TotSec32=((buffer[35]*256+buffer[34])*256+buffer[33])*256+buffer[32];
			printf("b1.BPB_TotSec32=%d\n  ",b1.BPB_TotSec32);
			b2.BS_DrvNum=buffer[36];
			printf("b2.BS_DrvNum=%d\n  ",b2.BS_DrvNum);
			b2.BS_Reserved1=buffer[37];
			printf("b2.BS_Reserved1=%d \n",b2.BS_Reserved1);
			b2.BS_BootSig=buffer[38];
			printf("b2.BS_BootSig=%d\n",b2.BS_BootSig);
			b2.BS_VolID=((buffer[42]*256+buffer[41])*256+buffer[40])*256+buffer[39];
			printf("b2.BS_VolID=%d \n ",b2.BS_VolID);
			for(i=43;i<54;i++)
			b2.BS_VolLab[i]=buffer[i];
			for(i=54;i<62;i++)
			b2.BS_FilSysType [i]=buffer[i];
			
			b3.BPB_FATSz32=((buffer[39]*256+buffer[38])*256+buffer[37])*256+buffer[36];
			printf("b3.BPB_FATSz32=%d\n ",b3.BPB_FATSz32);
			b3.BPB_ExtFlags=buffer[41]*256+buffer[40];
			b3.BPB_FSVer=buffer[43]*256+buffer[42];
			b3.BPB_RootClus=((buffer[47]*256+buffer[46])*256+buffer[45])*256+buffer[44];
			printf("b3.BPB_RootClus=%d\n",b3.BPB_RootClus);
			b3.BPB_FSInfo=buffer[49]*256+buffer[48];
			printf("b3.BPB_FSInfo=%d\n",b3.BPB_FSInfo);
			b3.BPB_BkBootSec=buffer[51]*256+buffer[50];
			printf("b3.BPB_BkBootSec= %d\n",b3.BPB_BkBootSec);
			for(i=52;i<64;i++)
			b3.BPB_Reserved[i]=buffer[i];
			b3.BS_DrvNum=buffer[64];
			b3.BS_Reserved1=buffer[65];
			b3.BS_BootSig=buffer[66];
			b3.BS_VolID=((buffer[70]*256+buffer[69])*256+buffer[68])*256+buffer[67];
			for(i=71;i<82;i++)
			b3.BS_VolLab[i]=buffer[i];
			for(i=82;i<90;i++)
			b3.BS_FilSysType[i]=buffer[i];

			//count of sectors occupied by the root directory
			//RootDirSectors = ((b1.BPB_RootEntCnt * 32) + (b1.BPB_BytsPerSec - 1)) / b1.BPB_BytsPerSec;
			
			//The start of the data region, the first sector of cluster 2
			if(b1.BPB_FATSz16 != 0)
			FATSz = b1.BPB_FATSz16;
			else
			FATSz = b3.BPB_FATSz32;
			printf("FATSz=%d\n",FATSz);
			FirstDataSector = b1.BPB_RsvdSecCnt + (b1.BPB_NumFATs * FATSz) + RootDirSectors;
			printf("FirstDataSector=%d\n",FirstDataSector);
			if(b1.BPB_TotSec16 != 0)
			TotSec = b1.BPB_TotSec16;
			else
			TotSec = b1.BPB_TotSec32;
			printf("%d\n",TotSec);
			DataSec = TotSec - (b1.BPB_RsvdSecCnt + (BPB_NumFATs * FATSz) + RootDirSectors);
			printf("%ld\n",DataSec);
			CountofClusters = DataSec / BPB_SecPerClus;
			printf("%ld\n",CountofClusters );
			//FirstRootDirSecNum = b1.BPB_ResvdSecCnt + (b1.BPB_NumFATs * BPB_FATSz16);
			}
			else
			{
				int y=1;
			//return ERR_UNSPEC;	
			}
			}
//-----------------------------------------------------------------------
		unsigned int fat_type()
			{
				if(CountofClusters < 4085) {
				/* Volume is FAT12 */
				return 12;
				} 
				else if(CountofClusters < 65525) {
				/* Volume is FAT16 */
				return 16;
				} 
				else {
				/* Volume is FAT32 */
				return 32;
				}

			}
//-----------------------------------------------------------------------			
			//Given any valid data cluster number N, the sector number of 
			//the first sector of that cluster (againrelative to sector 0 of the FAT volume) 
			//is computed as follows:
		unsigned int first_sector_of_cluster(unsigned int N )
		{
		return ((N - 2) * b1.BPB_SecPerClus) + FirstDataSector;
		}
//-----------------------------------------------------------------------

		unsigned int get_fat_entry(int N,block_data_t *buffer1) 
		{
			
		if(fat_type() == 16)
			FATOffset = N * 2;
		else if (fat_type() == 32)
			FATOffset = N * 4;

		ThisFATSecNum = b1.BPB_RsvdSecCnt + (FATOffset / b1.BPB_BytsPerSec);
		ThisFATEntOffset = FATOffset % b1.BPB_BytsPerSec;
		fd.read(buffer1,ThisFATSecNum);
		return ThisFATEntOffset;
//-----------------------------------------------------------------------
		}
		void set_fat_entry(int N,unsigned int value) 
		{
		//block_data_t buffer1[512];
		//unsigned int x=get_fat_entry(N,buffer1);
		
		}
		char open(const char *name)
		{
		//search for the file in root entries and if found create file object 
		//pointing to that clusture otherwise create new file and return file object
		//pointing to new clusture
		
		File *f=new file(name,0);
		return f;
		}
		private:
			block_data_t buffer[512];
			BPB b1;
			BS_16 b2;
			BS_32 b3;
			BlockMemory fd;
			
};

}
		
#endif
