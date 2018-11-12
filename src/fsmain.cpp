#include<bits/stdc++.h>
#define ll unsigned long long
#define FUSE_USE_VERSION 30

#define CALL(a,b) (a*)calloc(sizeof(a),b)
#define MALL(a,b) (a*)malloc(sizeof(a)*b)
#define REALL(a,b,c) (a*)realloc(b,sizeof(a)*c)
#define B_SIZE(x)rev (x/512) + 1

#include <fuse.h>
#include <unistd.h>
#include <sys/types.h>
#include <time.h>

// #include "../include/persistence.h"
#include "../include/fstree.h"
#include "../include/fsoperations.h"

using namespace std;

FSMD *root ;

static struct fuse_operations operations = {
    .getattr     = fs_getattr,
    .mknod       = fs_mknod,
    .mkdir       = fs_mkdir,
    .unlink      = fs_unlink,
    .rmdir       = fs_rmdir,
    .rename		 = fs_rename,
    .chmod		 = fs_chmod,
    .truncate	 = fs_truncate,
    .open        = fs_open,
    .read        = fs_read,
    .write       = fs_write,
    .readdir     = fs_readdir,
    .access      = fs_access,
};

int first = 0;

int main( int argc, char *argv[] ){

    root = create_tree();
	return fuse_main( argc, argv, &operations, NULL );
}
