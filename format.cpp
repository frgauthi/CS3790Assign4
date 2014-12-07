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
	unsigned long int status;
	

	// init dir start locations to -1
	for(int i = 0;i<DIRSIZE;i++){
		fs.dir[i].start = -1;	
	}
	
	strcpy(fs.dir[0].name, "frank");
	fs.dir[0].start = 0;
	fs.dir[0].size = 530;
	// add a file to the directory
	strcpy((char*)fs.data[0],"This is the data inside the frank file");


	
	// initialize the list to empty
	for(int i = 0;i<FATSIZE;i++){
		fs.fat[i] = -2;
	}
	//set the last block to signal the end of the free space
	
	
	fs.fat[0] = 1;
	fs.fat[1] = -1;	


	fd = open("Floppy.mfs", O_CREAT | O_WRONLY, 0666);

	status = write(fd,&fs,sizeof(FS));
	printf("status: %lu\n",status);

	close(fd);


return 0;
}
