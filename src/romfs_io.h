#ifndef _ROMFS_IO_
#define _ROMFS_IO_

extern unsigned char rd_start[];

void rfs_init();

int rfs_open(char* path);

void rfs_read(void *ptr, unsigned int  len);

void rfs_close();

int rfs_size();

void rfs_seek(int off);

#endif

