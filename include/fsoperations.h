#ifndef OPERATIONS
#define OPERATIONS

#include<bits/stdc++.h>
#include <fuse.h>
#include <unistd.h>
#include "fstree.h"

#define ll unsigned long long

using namespace std;

//what is this then?
extern FSMD* root;

int fs_getattr(const char *path, struct stat *st);

int fs_readdir(const char *path, void *buffer, fuse_fill_dir_t filler, off_t offset, struct fuse_file_info *fi );

int fs_read(const char *path, char *buf, size_t size, off_t offset,struct fuse_file_info *fi);

int fs_mkdir(const char *path,mode_t mode);

int fs_mknod(const char *path,mode_t mode,dev_t dev);

int fs_write(const char *path, const char *buf, size_t size, off_t offset, struct fuse_file_info *fi);

int fs_open(const char *path, struct fuse_file_info *fi);

int fs_rmdir(const char * path);

int fs_unlink(const char *path);

// int fs_rename(const char* from, const char* to);

#endif
