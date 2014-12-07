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
	int tmp; int current;
	
	fd = open("Floppy.mfs", O_CREAT | O_RDWR |  O_TRUNC, 0666);

	read(fd,&fs,sizeof(FS));	
	
	printf("fat[0]: %d\n",fs.fat[0]);
	printf("fat[1]: %d\n",fs.fat[1]);
	
	int i = 0;
	while(!strcmp(fs.dir[i].name, "frank")){i++;}	

	
	current = fs.dir[i].start;
	
	fs.dir[i].start = -1;

	while (current != -2){
		tmp = fs.fat[current]; // storing the next location to jump to
		fs.fat[current] = -2;

			current = tmp;
	}
	
	status = write(fd, &fs, sizeof(FS));
	printf("status: %d\n",status);
	printf("fat[0]: %d\n",fs.fat[0]);
	printf("fat[1]: %d\n",fs.fat[1]);
	printf("dir start: %d\n",fs.dir[i].start);
	
	close(fd);
	printf("name: %s", fs.dir[0].name);	

return 0;
}
