#ifndef __ROMFS_H__
#define __ROMFS_H__

int romdisk_mount(const void *img);
int romdisk_umount();
int romdisk_find(const char *path, void **ptr, int *size);

#endif
