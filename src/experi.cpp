#include<bits/stdc++.h>
#define ll unsigned long long
#define FUSE_USE_VERSION 30

#include <fuse.h>
#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <time.h>

using namespace std;

char ROOT[] = "/";
ll TOTAL_SIZE = 0;

struct ALL_THE_DATA{
	ll id;
};

struct sss_file_data{
	char *file_name;
	char *parent;
	char *content;
};

struct ROOT_DIR{
	sss_file_data *kids;
};

bool vacant[1001];
sss_file_data all_the_file_records[1001];


static int s3fs_getattr( const char *path, struct stat *st ){

	printf( "[getattr] Called\n" );
	printf( "\tAttributes of %s requested\n\n", path );
	
	st->st_uid = getuid();
	st->st_gid = getgid();

	time_t accessTime,modifiedTime,statusChangeTime;

	st->st_atime = time( &accessTime );
	st->st_mtime = time( &modifiedTime ); 
	st->st_mtime = time( &statusChangeTime ); 
	
	if ( strcmp( path, "/" ) == 0 ){
		st->st_mode = S_IFDIR | 0755;
		st->st_nlink = 2;
	}else{
		st->st_mode = S_IFREG | 0644;
		st->st_nlink = 1;
		st->st_size = 1024;
	}
	cout<<"\n************************FULL DETAILS************************\n\n";
	cout<<"access time :: \t\t"<< ctime(&accessTime) <<"\n";
	cout<<"last modified time :: \t"<< ctime(&modifiedTime) <<"\n";
	cout<<"last status change time :: \t"<< ctime(&statusChangeTime) <<"\n";
	cout<<"File size :: \t\t"<< st->st_size <<"\n";
	cout<<"Block size ::\t\t"<< st->st_blksize <<"\n";
	cout<<"************************END************************\n\n";
	return 0;
}

static int s3fs_readdir( const char *path, void *buffer, fuse_fill_dir_t filler, off_t offset, struct fuse_file_info *fi ){

	// printf( "--> Getting The List of Files of %s\n", path );
	
	filler( buffer, ".", NULL, 0 );
	filler( buffer, "..", NULL, 0 );
	
	if ( strcmp( path, "/" ) == 0 ){
		filler( buffer, "file54", NULL, 0 );
		filler( buffer, "file349", NULL, 0 );
	}
	
	cout<<"All empty\n";

	return 0;
}

static int s3fs_read( const char *path, char *buffer, size_t size, off_t offset, struct fuse_file_info *fi ){

	printf( "--> Trying to read %s, %u, %u\n", path, offset, size );
	
	char file54Text[] = "Hello World From File54!";
	char file349Text[] = "Hello World From File349!";
	char *selectedText = NULL;
	
	cout<<"Path :: \t"<<path<<"\n";


	if ( strcmp( path, "/file54" ) == 0 )
		selectedText = file54Text;
	else if ( strcmp( path, "/file349" ) == 0 )
		selectedText = file349Text;
	else
		return -1;
	
	memcpy( buffer, selectedText + offset, size );
	
	return strlen( selectedText ) - offset;
}

static int s3fs_mkdir(const char *path,mode_t mode){

	
	cout<<"Directory made :: \t\t"<<path<<"\n";

	return 0;

}

static int s3fs_mknod(char *path,mode_t mode,dev_t dev){


	cout<<"File name ::\t\t"<<path<<"\n";

	return 0;
}



static struct fuse_operations operations = {
    // .init        = s3fs_init,
    // .destroy     = s3fs_destroy,
       .getattr     = s3fs_getattr,
    // .fgetattr    = s3fs_fgetattr,
    // .access      = s3fs_access,
    // .readlink    = s3fs_readlink,
    // .mknod       = s3fs_mknod,
    // .mkdir       = s3fs_mkdir,
    // .symlink     = s3fs_symlink,
    // .unlink      = s3fs_unlink,
    // .rmdir       = s3fs_rmdir,
    // .rename      = s3fs_rename,
    // .link        = s3fs_link,
    // .chmod       = s3fs_chmod,
    // .chown       = s3fs_chown,
    // .truncate    = s3fs_truncate,
    // .ftruncate   = s3fs_ftruncate,
    // .utimens     = s3fs_utimens,
    // .create      = s3fs_create,
    // .open        = s3fs_open,
       .read        = s3fs_read,
//     .write       = s3fs_write,
//     .statfs      = s3fs_statfs,
//     .release     = s3fs_release,
//     .opendir     = s3fs_opendir,
       .readdir     = s3fs_readdir,
//     .releasedir  = s3fs_releasedir,
//     .fsync       = s3fs_fsync,
//     .flush       = s3fs_flush,
//     .fsyncdir    = s3fs_fsyncdir,
//     .lock        = s3fs_lock,
//     .bmap        = s3fs_bmap,
//     .ioctl       = s3fs_ioctl,
//     .poll        = s3fs_poll,
// #ifdef HAVE_SETXATTR
//     .setxattr    = s3fs_setxattr,
//     .getxattr    = s3fs_getxattr,
//     .listxattr   = s3fs_listxattr,
//     .removexattr = s3fs_removexattr,
// #endif
//     .flag_nullpath_ok = 0,                /* See below */
};






int main( int argc, char *argv[] ){
	memset(vacant,0,sizeof(vacant));
	return fuse_main( argc, argv, &operations, NULL );
}