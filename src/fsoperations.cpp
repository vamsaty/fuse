#include "../include/fsoperations.h"

time_t top;

int fs_getattr( const char *path, struct stat *st ){

	
	string dpath(path);
	string dir_str;
	
	FSMD *dir_node = NULL;
	dir_str = getDir(dpath);	
	
	
	// cout<<"CALLED GETATTR\t"<<path<<"\t"<<dpath<<"\t"<<dir_str<<"\n";
	cout<<"CALLED GETATTR\n";

	if(dir_str == "/"){
		//check if the directory is root
		dir_node = root;

	}else if(dir_str.length() > 1){
		
		// search for the node
		dir_node = searcher(root,path);

	}

	if(dir_node == NULL){
		//if not found, return -ENOENT, to further take actions, allows to mkdir
		return -ENOENT;
	}
	
	if ( dir_node->isDir ){
		st->st_nlink = 2;
	}else{
		st->st_nlink = 1;
		st->st_size = 4096;
		st->st_blocks = (((st->st_size) / 512) + 1);
	}

	st->st_nlink += dir_node->noc;
	st->st_mode = dir_node->permissions;
	st->st_uid = dir_node->user_id; 
	st->st_gid = dir_node->group_id;

	st->st_atime = dir_node->a_time;
	st->st_mtime = dir_node->m_time;
	st->st_ctime = dir_node->c_time;
	
	return 0;
}

int fs_readdir( const char *path, void *buffer, fuse_fill_dir_t filler, off_t offset, struct fuse_file_info *fi ){
	
	cout<<"READDIR CALLED\n";

	filler( buffer, ".", NULL, 0 );
	filler( buffer, "..", NULL, 0 );
	
	string dpath(path);
	
	if(dpath == "/"){

		for(int i=0;i < root->deadEnd;i++){	//change
			if(root->children[i] != NULL){
				filler(buffer,(root->children[i]->name).c_str(),NULL,0);
			}
		}

	}else{
		//here dpath is same as path
		FSMD *dir_node = searcher(root,dpath);
		if(dir_node == NULL)
			return -ENOENT;
		
		for(int i=0;i < dir_node->deadEnd;i++){	//change
			if(dir_node->children[i] != NULL){
				filler(buffer,(dir_node->children[i]->name).c_str(),NULL,0);
			}
		}

	}

	return 0;
}

int fs_read(const char *path, char *buffer, size_t size, off_t offset,struct fuse_file_info *fi){
	
	string dpath(path);
	cout<<"CALLED READ\t\t";
	FSMD *dir_node = NULL;
	
	string select;
	string dir_name = getDir(dpath);

	dir_node = searcher(root,path);

	if(dir_node != NULL){
		if(!dir_node->isDir){
			dir_node->a_time = time(NULL);
			int len = dir_node->data.length();
			if(!len)
				return 0;
			memcpy(buffer, (dir_node->data).c_str() + offset, size);
			return size;
		}
	}
	
	return -ENOENT;
	
}

int fs_mkdir(const char *path,mode_t mode){
	
	cout<<"CALLED MKDIR\t\t\n";
	const string dpath(path);
	cout<<path<<"\n\n";
	insert_node(dpath,1);
	return 0;
}

int fs_mknod(const char *path,mode_t mode,dev_t dev){
	
	cout<<"CALLED MKNOD\t\t\n";

	const string dpath(path);
	
	insert_node(dpath,0);
	return 0;	
}

int fs_write(const char *path, const char *buf, size_t size, off_t offset, struct fuse_file_info *fi){

	string dpath(path);
	FSMD *dir_node = NULL;

	dir_node = searcher(root,path);
	if(dir_node != NULL){
		if(!dir_node->isDir){

			dir_node->a_time = time( NULL );
			dir_node->m_time = time(NULL);
			dir_node->c_time = time(NULL);
			
			dir_node->data.append(buf);
			
			cout<<"data -> "<<dir_node->data<<"\n\n";

			cout<<dir_node->data.length()<<"\n";

			memset((char *)buf, 0, strlen(buf));
			return size;
		}

	}
	
	return -ENOENT;
}


int fs_open(const char *path, struct fuse_file_info *fi){
	
	FSMD *dir_node = NULL;
	dir_node = searcher(root,path);
	if(dir_node != NULL){
		if(!dir_node->isDir){
			dir_node->permissions = (S_IFREG) | 777;
		}
	}

	return 0;
}


int fs_rmdir(const char * path){
	printf("GETATTR CALLED\n");
	
	string dpath(path);
	
	if(dpath == "/"){
		cout<<"Cannot delete ROOT\n";
		return -ENOTEMPTY;
	}
	
	FSMD * dir_node = searcher(root,path);
	int ret = delete_node(dir_node);
	
	if(ret < 0){
		return -ENOTEMPTY;
	}

	return 0;
}


int fs_unlink(const char *path){
	string dpath(path);
	FSMD *dir_node = searcher(root,path);
	if(dir_node == NULL || dir_node->isDir)
		return 0;
	
	delete_file(dir_node);

	return 0;
}



// int fs_rename(const char* from, const char* to){
// 	FSMD *dir_node = NULL;


// 	src_node = searcher(root,from);
// 	if(dir_node == NULL){
// 		return -ENOENT;
// 	}

// 	dest_node = searcher(root,to);
	
// 	if(dest_node != NULL){
// 		if(src_node->isDir && !dest_node->isDir){
// 			return -EPERM;
// 		}
// 	}
// 	move_node(from,to,dir_node->parent);
// 	if(!dest_node->isDir){

// 	}

// }