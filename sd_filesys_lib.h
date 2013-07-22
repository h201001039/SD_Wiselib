	#include <stdint.h>
#include <stddef.h>
//#include "file_block_memory.h"
#define IsUpper(c)	(((c)>='A')&&((c)<='Z'))
#define IsLower(c)	(((c)>='a')&&((c)<='z'))
#define	LD_INT(ptr)		(unsigned int)(*(unsigned int*)(unsigned char*)(ptr))
#define	LD_LONG(ptr)	(unsigned long)(*(unsigned long*)(unsigned char*)(ptr))
#define	LD_SHORT(ptr)	(unsigned short)(*(unsigned short*)(unsigned char*)(ptr))
#define LD_CLUST(dir)	LD_SHORT(dir+26)
#ifndef __SD_FILE_SYSTEM_LIBRARY_H__
#define __SD_FILE_SYSTEM_LIBRARY_H__
#include "pc_os_model.h"
namespace wiselib
{
unsigned char fs_type;	/* FAT sub type */
unsigned char csize;	/* Number of sectors per cluster */
unsigned int n_rootdir;	/* Number of root directory entries (0 on FAT32) */
unsigned long n_fatent;	/* Number of FAT entries (= number of clusters + 2) */
unsigned long fatbase;	/* FAT start sector */
unsigned long dirbase;	/* Root directory start sector (Cluster# on FAT32) */
unsigned long database;	/* Data start sector */
unsigned long bps;
 unsigned long RootDirSectors;
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
unsigned long FirstRootDirSecNum;

template<typename OsModel_P,typename BlockMemory_P = typename OsModel_P::BlockMemory>
class File
{
    public:
                typedef OsModel_P OsModel;
                typedef typename OsModel::size_t size_t;
                typedef typename OsModel::block_data_t block_data_t;
                typedef BlockMemory_P BlockMemory;
                unsigned long fptr; 		/* File R/W pointer */
                unsigned long fsize;		/* File size */
                unsigned long org_clust;	/* File start cluster */
                unsigned long curr_clust;	/* File current cluster */
                unsigned long dsect; 		/* File current data sector */
                unsigned char flag;			/* File status flags */

                File(char* n, unsigned int cluster_no, BlockMemory& bm) : fd(bm) {
                //strncpy(name_, n, 12);
                int i=0;
                while(i<12 && n[i]!=0) {
                        name_[i]=n[i];
                        i++;
                        }
                name_[i]='\0';
                file_cluster_no=cluster_no;     
                }
                File(BlockMemory& bm) : fd(bm) {
                name_[0]=0;
                }
                size_t write(block_data_t *buf, size_t size) {
                size_t s=size;
                //Code goes here...need some changes
                return s;       
                }
                size_t read(block_data_t *buf, size_t size) {
                
                return size;
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
//-----------------------------------------------------------------------
                        //Given any valid data cluster number N, the sector number of 
                        //the first sector of that cluster (againrelative to sector 0 of the FAT volume) 
                        //is computed as follows:
                unsigned int first_sector_of_cluster(unsigned int N )
                {
					printf("database=%ld\n",database);
                return ((N - 2) * csize) + database;
                }
//-----------------------------------------------------------------------
 
                unsigned int get_fat_entry(int N) 
                {
                        block_data_t *buffer1;
                if(fat_type() == 16)
                        FATOffset = N * 2;
                else if (fat_type() == 32)
                        FATOffset = N * 4;
 
                 ThisFATSecNum = fatbase + (FATOffset / bps);
                 ThisFATEntOffset = fatbase % bps;
                fd.read(buffer1,ThisFATSecNum);
                return LD_SHORT(buffer1+ThisFATEntOffset);//change into word. eg 16 bit or 32 bit.
                //changes needed for 32 bit
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
//----------------------------------------------------------------------------------------                 
                long pf_read (
					block_data_t* buff,
					int btr
				)
				{
					//SdFileSystemLibrary<OsModel> s;
					int dr;
					int clst;
					long sect, remain;
					int rcnt,i;
					block_data_t cs, *rbuff = buff;



					remain = fsize - fptr;
					if (btr > remain) btr = (int)remain;			/* Truncate btr by remaining bytes */
					//printf("fptr=%ld btr=%d fsize=%ld org_clust=%d\n",fptr,btr,fsize,org_clust);
					while (btr)	{									
						if ((fptr % 512) == 0) {				
							cs = (unsigned char)(fptr / 512 & (csize - 1));	
							if (!cs) {								
								clst = (fptr == 0) ?			
									org_clust : get_fat_entry(curr_clust);
								if (clst <= 1) printf("error123");
								curr_clust = clst;				
							}
							printf("curr_clust=%ld\n",curr_clust);
							sect = first_sector_of_cluster(curr_clust);		
							printf("sect=%ld\n",sect);
							if (!sect) printf("error234");
							dsect = sect + cs;
						}
						rcnt = (unsigned int)(512 - (fptr % 512));		
						if (rcnt > btr) rcnt = btr;
						dr = fd.read(rbuff, dsect);
						//for(i=0;i<700;i++)
						//printf("%d ",buff[i]);
						if (!dr) printf("error\n");
						fptr += rcnt; rbuff += rcnt;			
						btr -= rcnt; 
					}

					return remain;

				}

//----------------------------------------------------------------------------------------
        private:
                char name_[13];
                //friend class SdFileSystemLibrary;
                int file_open_mode;
                BlockMemory& fd;
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
                unsigned long BPB_RootClus;
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
//-------------------------------------------------------------------------------------
				/* Fill memory */
				
				void mem_set (void* dst, int val, int cnt) {
					char *d = (char*)dst;
					while (cnt--) *d++ = (char)val;
				}

//-------------------------------------------------------------------------------------
				/* Compare memory to memory */
				
				int mem_cmp (const void* dst, const void* src, int cnt) {
					const char *d = (const char *)dst, *s = (const char *)src;
					int r = 0;
					while (cnt-- && (r = *d++ - *s++) == 0) ;
					//printf("r=%d\n",r);
					return r;
				}


 
//-----------------------------------------------------------------------                       

				/* length */
				
				int len(char *name)
				{
				int i=0;
					while(*name!=0)
					{
					i++;
					name++;
					}
					return i;
					}

//-------------------------------------------------------------------------------------
                void init() {
                        CountofClusters=0;
                        TotSec=0;
                        DataSec=0;
                        int i=0;
                        fd.init("/home/mindfuck/test.img");
                        for(i=0;i<512;i++)
                        buffer[i]=0;
                         int a=fd.read(buffer,0);
                        for(i=0;i<512;i++)
                        {
                        printf("%x  ",buffer[i]);
                        if(i%16==0 && i!=0 &&i!=16 || i==15)
                        printf("\n");
                }
                        if(a==1)
                        {
                        printf("\nsuccesfull read\n");
                        sclust=0;
                        b1.BPB_BytsPerSec=LD_INT(buffer+11);
                        bps=b1.BPB_BytsPerSec;
                        printf("b1.BPB_BytsPerSec=%d\n",b1.BPB_BytsPerSec);
                        b1.BPB_SecPerClus=buffer[13];
                        csize=b1.BPB_SecPerClus;
                        printf("b1.BPB_SecPerClus=%d\n",b1.BPB_SecPerClus);
                        b1.BPB_RsvdSecCnt=LD_INT(buffer+14);;
                        printf("b1.BPB_RsvdSecCnt=%d\n",b1.BPB_RsvdSecCnt);
                        fatbase=b1.BPB_RsvdSecCnt;
                        b1.BPB_NumFATs=buffer[16];
                        printf("b1.BPB_NumFATs=%d\n",b1.BPB_NumFATs);
                        b1.BPB_RootEntCnt=LD_INT(buffer+17);
                        n_rootdir=b1.BPB_RootEntCnt;
                        printf("b1.BPB_RootEntCnt=%d\n",b1.BPB_RootEntCnt);
                        b1.BPB_TotSec16=LD_INT(buffer+19);
                        printf("b1.BPB_TotSec16=%d\n",b1.BPB_TotSec16);
                        b1.BPB_FATSz16=LD_INT(buffer+22);
                        printf("b1.BPB_FATSz16=%d\n",b1.BPB_FATSz16);
                        b1.BPB_TotSec32=LD_INT(buffer+32);
                        printf("b1.BPB_TotSec32=%d\n  ",b1.BPB_TotSec32);
                        b3.BPB_FATSz32=LD_INT(buffer+36);
                        printf("b3.BPB_FATSz32=%d\n ",b3.BPB_FATSz32);
                        b3.BPB_RootClus=LD_INT(buffer+44);
                        printf("b3.BPB_RootClus=%ld\n",b3.BPB_RootClus);
                        if(b1.BPB_FATSz16 != 0)
                        FATSz = b1.BPB_FATSz16;
                        else
                        FATSz = b3.BPB_FATSz32;
                        printf("FATSz=%d\n",FATSz);
                        int totsec;
                        if(b1.BPB_TotSec16 != 0)
                        totsec = b1.BPB_TotSec16;
                        else
                        totsec = b1.BPB_TotSec32;
                        printf("totsec=%d\n",totsec);
                        RootDirSectors = ((b1.BPB_RootEntCnt * 32) + (b1.BPB_BytsPerSec - 1)) / b1.BPB_BytsPerSec;
                        printf("RootDirSectors=%ld\n",RootDirSectors);
                        database=fatbase+(b1.BPB_NumFATs*FATSz)+RootDirSectors;
                        printf("database=%ld\n",database);
                        DataSec = totsec - (fatbase + (b1.BPB_NumFATs * FATSz) + RootDirSectors);
                        printf("DataSec=%ld\n",DataSec);
                        CountofClusters = DataSec / csize;
                        printf("CountofClusters=%ld\n",CountofClusters);
                        n_fatent=CountofClusters;
                        if(fat_type()==16)
                        FirstRootDirSecNum = fatbase + (b1.BPB_NumFATs * FATSz);
                        else 
                        FirstRootDirSecNum = b3.BPB_RootClus;
                        dirbase=FirstRootDirSecNum;
                        printf("FirstRootDirSecNum=%ld\n",FirstRootDirSecNum);
                        }
                        else
                        {
                                int y=1;    
                        }
                        }
//-----------------------------------------------------------------------
                        //Given any valid data cluster number N, the sector number of 
                        //the first sector of that cluster (againrelative to sector 0 of the FAT volume) 
                        //is computed as follows:
                unsigned int first_sector_of_cluster(unsigned int N )
                {
                return ((N - 2) * csize) + database;
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
                return LD_SHORT(buffer1+ThisFATEntOffset);//change into word. eg 16 bit or 32 bit.
                //changes needed for 32 bit
//-----------------------------------------------------------------------
                }
                void set_fat_entry(int N,unsigned int value) 
                {
                //block_data_t buffer1[512];
                //unsigned int x=get_fat_entry(N,buffer1);
                
                }
//----------------------------------------------------------------------------                
                /* Directory handling - Move directory index next                        */

                int dir_next ()
				{
				unsigned long clst;
				 unsigned short i;
				block_data_t buffer1[512];
				i = index + 1;
				if (!i || !sect)	
					return 0;

				if (!(i % 16)) {		/* Sector changed? */
					sect++;			/* Next sector */

					if (clust == 0) {	
						if (i >= n_rootdir)	
							return 0;
					}
					else {					
						if (((i / 16) & (csize-1)) == 0) {	/* Cluster changed? */
							clst = get_fat_entry(clust,buffer1);		
							if (clst <= 1) return 0;
							if (clst >= n_fatent)		
								return 0;			
							clust = clst;				
							sect = first_sector_of_cluster(clst);
						}
					}
				}

					index = i;
				//printf("sect=%ld clust=%ld index=%d\n",sect,clust,index);
					return 1;
				}
//----------------------------------------------------------------------------

/* Directory handling - Rewind directory index */
				int dir_rewind ()
				{
					unsigned long clst;//may be need change
					

					index = 0;
					clst = sclust;
					//printf("sclust=%ld\n",sclust);
					if (clst == 1 || clst >= n_fatent)	/* Check start cluster range */
					{
					printf("hello sir\n");
						return 0;//change
					}
					if ( !clst && fat_type()==32)//need changeds 
					/* Replace cluster# 0 with root cluster# if in FAT32 */
						clst = (unsigned long)dirbase;
					clust = clst;						/* Current cluster */
					sect = clst ? first_sector_of_cluster(clst) : dirbase;	/* Current sector */
					//printf("sect=%ld clust=%ld index=%d\n",sect,clust,index);
					return 1;	
				}

//-------------------------------------------------------------------------------------
/* Directory handling - Find an object in the directory                  */

				int dir_find (char *name,int len)
				{
					
					//printf("harsh\n");
					
					int res,i,c;

					res = dir_rewind();			/* Rewind directory object */
					//printf("res=%d\n",res);
				if (res != 1) return res;

					do {
						res=fd.read(buffer2,sect);
						dir1 =(buffer2+((index % 16) * 32));
						c = dir1[0];	/* First character */
						//printf("c=%d\n",c);
						if (c == 0) {  break; }	
						if(c==0xE5)
						{
						res = dir_next();
						continue;
					}
							for(i=0;i<11;i++)
							printf("%c",dir1[i]);
							printf("\n");
							//break;
							if(!mem_cmp(dir1, name, len))
							{
							for(i=0;i<5;i++)
							printf("%c ",dir1[i]);
							printf("\n");
							break;
						}
						res = dir_next();					/* Next entry */
					} while (res == 1);

					return res;
				}
//--------------------------------------------------------------------------------
				File<OsModel> open(char* name)
                {
                //search for the file in root entries and if found create file object 
                //pointing to that clusture otherwise create new file and return file object
                //pointing to new clusture
				int res,i;
				block_data_t buf;
				//block_data_t *dir;
				dir1=&buf;
                File<OsModel> f(name,0, fd);
                					f.flag = 0;
                	int len1=len(name);				
					res=dir_find(name,len1);	
					//dir =(buffer2+((index % 16) * 32));
					//printf("buffer2=%u index=%ld\n",buffer2,index);
					if (res ==0 ) printf("res=%d\n",res);		
					f.org_clust = LD_CLUST(dir1);			
					printf("f.org_clust=%ld\n",f.org_clust);
					for(i=0;i<5;i++)
					printf("%c ",dir1[i]);
					f.fsize = LD_INT(dir1+28);	
					printf("f.fsize=%ld\n",f.fsize);
					f.fptr = 0;						
					f.flag = 1;

                return f;
                }
//-----------------------------------------------------------------------                
							   
				
               private:
                        block_data_t buffer[512];
                        BPB b1;
                        BS_16 b2;
                        BS_32 b3;
                        BlockMemory fd;
                        block_data_t buffer2[512];
                        unsigned int index; 		/* Current read/write index number */
                        unsigned long sclust;		/*start cluster	*/
                        unsigned long clust; 		/* Current cluster */
                        unsigned long sect;			/* Current sector */
                        block_data_t *dir1;
};
 
}
                
#endif
