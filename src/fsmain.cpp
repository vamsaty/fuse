#include<bits/stdc++.h>
#define ll unsigned long long
#define FUSE_USE_VERSION 30

// #define CALL(a,b) (a*)calloc(sizeof(a),b)
// #define B_SIZE(x) (x/512) + 1 

#define CALL(a,b) (a*)calloc(sizeof(a),b)
#define MALL(a,b) (a*)malloc(sizeof(a)*b)
#define REALL(a,b,c) (a*)realloc(b,sizeof(a)*c)
#define B_SIZE(x)rev (x/512) + 1

#include <fuse.h>
#include <unistd.h>
#include <sys/types.h>
#include <time.h>
#include "../include/fstree.h"
#include "../include/fsoperations.h"
using namespace std;

FSMD *root ;

static struct fuse_operations operations = {
/* .init        = fs_init,
       .destroy     = fs_destroy,
*/
    .getattr     = fs_getattr,


/*
    .fgetattr    = fs_fgetattr,
    .access      = fs_access,
    .readlink    = fs_readlink,
*/
    .mknod       = fs_mknod,
    .mkdir       = fs_mkdir,

    // .symlink     = fs_symlink,
    .unlink      = fs_unlink,
    .rmdir       = fs_rmdir,
/*
    .rename      = fs_rename,
    .link        = fs_link,
    .chmod       = fs_chmod,
    .chown       = fs_chown,
    .truncate    = fs_truncate,
    .ftruncate   = fs_ftruncate,
    .utimens     = fs_utimens,
    .create      = fs_create,
    
*/
    .open        = fs_open,
    .read        = fs_read,
    .write       = fs_write,
/*
     .statfs      = fs_statfs,
     .release     = fs_release,
     .opendir     = fs_opendir,
*/
    .readdir     = fs_readdir,
/*
    .releasedir  = fs_releasedir,
    .fsync       = fs_fsync,
    .flush       = fs_flush,
    .fsyncdir    = fs_fsyncdir,
    .lock        = fs_lock,
    .bmap        = fs_bmap,
    .ioctl       = fs_ioctl,
    .poll        = fs_poll,
 */
};



int main( int argc, char *argv[] ){
	// cout<<"Asdffffffffffffffffffffffffffff";
    root = create_tree();
    temp_files(&root);
	return fuse_main( argc, argv, &operations, NULL );
}
