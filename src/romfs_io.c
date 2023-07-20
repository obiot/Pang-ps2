#include <stdio.h>
#include <string.h>
#include "romfs_io.h"

// handle romdisk 
#include "romfs.h"




int sz;                  //size      of  file from romfs
int offset;              //offset  ... 
unsigned char *dataptr;  //datptr ... 

void rfs_init()
{
	sz = 0;
	offset = 0;
	dataptr = 0;
}

int rfs_open(char* path)
{
	rfs_init();
	
        if (romdisk_find(path, (void **)&dataptr, &sz) == 0) {
		return 0;
	}
	else
	{
		printf("failed to open %s\n", path);
		return 1;
	}
}

void rfs_read(void *ptr, unsigned int  len) {
	memcpy(ptr, dataptr + offset, len);
	offset += len;
}

void rfs_close() {	
        rfs_init();
}

int rfs_size() {
	return sz;
}

void rfs_seek(int off) {
	offset = off;
}
 
