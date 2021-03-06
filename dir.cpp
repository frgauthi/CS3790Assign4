#include <cstdio>
#include <stdlib.h>
#include <string.h>
#include <fcntl.h>
#include <unistd.h>

#define DIRSIZE 32
#define FATSIZE 1024
#define BLOCKSIZE 512
#define FILELENGTH 12

 

typedef struct{

        char name[FILELENGTH];
        short start;
        int size;

}direntry;

 
typedef direntry DIRECTORY[DIRSIZE];
typedef short FAT[FATSIZE];
typedef unsigned char BLOCK[BLOCKSIZE];

typedef struct{
	DIRECTORY dir;
	FAT fat;
	BLOCK data[FATSIZE];

}FS;



int main(){

	// create a filesystem structure	
	FS fs;
	int fd;
	int status;

	fd = open("Floppy.mfs", O_RDONLY, 0666);

	read(fd,&fs,sizeof(FS));
	printf("File\t\tSize\n------------------------\n");
	
	int i = 0;
	while(fs.dir[i].start != -1) {printf("%s,\t\t%d\t\t%d\n",fs.dir[i].name,fs.dir[i].size,fs.dir[i].start);i++;}
		
	close(fd);
	

return 0;
}
