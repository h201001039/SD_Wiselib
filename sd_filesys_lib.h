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
//#include "pc_os_model.h"
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
                
                enum {
				SUCCESS = OsModel::SUCCESS,
				ERR_UNSPEC = OsModel::ERR_UNSPEC
			};

//------------------------------------------------------------------------
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
//-------------------------------------------------------------------------------------
				/* Fill memory */
				
				void mem_set (block_data_t* dst, block_data_t *src, int cnt) {
					while(cnt--)
					{
						*dst=*src;
						dst++;
						src++;
						}
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
                        //Given any valid data cluster number N, the sector number of 
                        //the first sector of that cluster (againrelative to sector 0 of the FAT volume) 
                        //is computed as follows:
                unsigned int first_sector_of_cluster(unsigned int N )
                {
					//printf("database=%ld\n",database);
                return ((N - 2) * csize) + database;
                }
//------------------------------------------------------------------------
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
 
                unsigned int get_fat_entry(int N) 
                {
                        block_data_t *buffer1=0;
                if(fat_type() == 16)
                        FATOffset = N * 2;
                else if (fat_type() == 32)
                        FATOffset = N * 4;
 
                 ThisFATSecNum = fatbase + (FATOffset / bps);
                 ThisFATEntOffset = FATOffset % bps;
                 printf("ThisFATEntOffset=%d\n",ThisFATEntOffset);
                fd.read(buffer1,ThisFATSecNum); 
                if(fat_type()==16)
                return LD_SHORT(buffer1+ThisFATEntOffset);//change into word. eg 16 bit or 32 bit.
                else if (fat_type() == 32)
                return  LD_INT(buffer1+ThisFATEntOffset) & 0x0FFFFFFF;
		else 
			return 0;			
			}
//-----------------------------------------------------------------------
					long read (
					block_data_t* buff,
					int btr
				)
				{
					//SdFileSystemLibrary<OsModel> s;
					int dr;
					int clst;
					long sect, remain;
					int rcnt,ret;
					block_data_t cs;
					block_data_t inter[bps];
					//printf("%ld\n",fptr);


					printf("csize =%d fsize=%ld\n",csize,fsize);
					remain = fsize - fptr;
					while(remain<=0)
					return -2;
					if (btr > remain) btr = (int)remain;			/* Truncate btr by remaining bytes */
					printf("fptr=%ld btr=%d fsize=%ld org_clust=%ld\n",fptr,btr,fsize,org_clust);
					ret=btr;
					//printf("%ld\n",bps);
					while (btr)	{									
						if ((fptr % bps) == 0) {				
							cs = (unsigned char)(fptr / bps & (csize - 1));	
							if (!cs) {								
								clst = (fptr == 0) ?			
									org_clust : get_fat_entry(curr_clust);
									printf("curr_clust=%d\n",clst);
								if (clst <= 1) return ERR_UNSPEC;
								curr_clust = clst;				
							}
							printf("curr_clust=%ld\n",curr_clust);
							printf("fptr=%ld btr=%d fsize=%ld org_clust=%ld\n",fptr,btr,fsize,org_clust);
							sect = first_sector_of_cluster(curr_clust);		
							printf("sect=%ld\n",sect);
							if (!sect) return ERR_UNSPEC;
							dsect = sect + cs;
						}
						rcnt = (unsigned int)(bps - (fptr % bps));		
						if (rcnt > btr) rcnt = btr;
						printf("rcnt=%d\n",rcnt);
						dr = fd.read(inter, dsect);
						mem_set(buff,inter+(fptr%bps),rcnt);
						//for(i=0;i<700;i++)
						//printf("%d ",buff[i]);
						if (dr) return ERR_UNSPEC;
						fptr += rcnt; buff += rcnt;			
						btr -= rcnt; 
					}
					//printf("fptr=%ld\n",fptr);
					return ret;

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
				
				int len(const char *name)
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
                
				void to_upper( char *src)
				{
					//int i;
					//char x;
				while((*src)!=0)
				{
					//printf("%d",*src);
					if(*src >=97 &&	 *src <=122)
					{
						//printf("%c",*src);
						 
						*src-=32;
					}
					src++;
					}	
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
                        //for(i=0;i<512;i++)
                        //{
                        //printf("%x  ",buffer[i]);
                        //if(i%16==0 && i!=0 &&i!=16 || i==15)
                        //printf("\n");
                //}
                        if(a==SUCCESS)
                        {
                        printf("succesfull read\n\n");
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
                if(fat_type()==16)
                return LD_SHORT(buffer1+ThisFATEntOffset);//change into word. eg 16 bit or 32 bit.
                else
                return  LD_INT(buffer1+ThisFATEntOffset);
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
				int mod=(bps/32);
				if (!(i % mod)) {		/* Sector changed? */
					sect++;			/* Next sector */

					if (clust == 0) {	
						if (i >= n_rootdir)	
							return 0;
					}
					else {					
						if (((i / mod) & (csize-1)) == 0) {	/* Cluster changed? */
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
					//printf("hello sir\n");
						return ERR_UNSPEC;//change
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
						if(res==ERR_UNSPEC)
						return ERR_UNSPEC;
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
				File<OsModel> open(const char* name)
                {
                //search for the file in root entries and if found create file object 
                //pointing to that clusture otherwise create new file and return file object
                //pointing to new clusture
				int i=0;
				char name1[15];
				block_data_t buf;
				int len1=len(name);
				//block_data_t *dir;
				while(*(name+i)!=0)
				{
				name1[i]=*(name+i);
				i++;
				}
				name1[i]=0;
				dir1=&buf;
				//printf("%s\n",name);
				//printf("hello %s\n",name1);
                to_upper(name1);
                File<OsModel> f(name1,0, fd);
                f.flag = 0;
                					
					dir_find(name1,len1);	
					//dir =(buffer2+((index % 16) * 32));
					//printf("buffer2=%u index=%ld\n",buffer2,index);
					//if (res ==0 ) printf("res=%d\n",res);		
					f.org_clust = LD_CLUST(dir1);			
					//printf("f.org_clust=%ld\n",f.org_clust);
					//for(i=0;i<5;i++)
					//printf("%c ",dir1[i]);
					f.fsize = LD_INT(dir1+28);	
					//printf("f.fsize=%ld\n",f.fsize);
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
