#include "../include/fstree.h"

FSMD *make_node(string path,const string& name,bool dir,FSMD *parent){
	
	cout<<"MAKE NODE CALLED\n";

	time_t at,bt,ct,mt;
	FSMD *nd = MALL(FSMD, 1);

	nd->isDir = dir;
	nd->permissions = (dir)? (S_IFDIR | 0777) : (S_IFREG | 0777);

	nd->name.assign(name);
	nd->data;

	nd->size = 0;
	nd->inode_number = 0;
	nd->deadEnd = 0;
	nd->noc = 0;
	nd->nof = 0;
	nd->isDeleted = 0;

	nd->group_id = getgid();
	nd->user_id = getuid();

	nd->a_time = time(&at);
	nd->m_time = time(&mt);
	nd->c_time = time(&ct);
	nd->b_time = time(&bt);
	
	nd->children = MALL(FSMD*,100);
	nd->parent = parent;

	return nd;
}

FSMD *create_tree(){
	return make_node("/","root",1,NULL);
}

//gets the directory_name plus it changes the path value
string getDir(string &path){

	// root /xyz/abc

	string dir(path);
	string final;
	
	// root/xyz/abc/ --> root/xyz/abc
	if(dir.back() == '/'){
		if(dir.length()>1){
			dir.pop_back();
			path.pop_back();
		}else if(dir.length() == 1){
			final.assign(dir);
			return final;
		}
	}

	int len = dir.length();
	size_t found = dir.rfind("/");

	// final => abc
	// path => root/xyz/
	if(found != string::npos && found+1 != len){
	    final.assign(dir,found+1,len-found);
	    path.replace(found+1,path.length(),"");
	}

	// path => root/xyz
    if(path.length()>1 && path.back()=='/')
    	path.pop_back();
    
	return final;
}

FSMD *searcher(FSMD *node, string path){
	// _ /xyz/abc/			len = 12

	int len = path.length();

	if(!len)
		return node;
	
	// path => xyz/abc/
	if(path.front() == '/'){
		if(len > 1)
			path.erase(path.begin());
	}

	size_t found = path.find("/");
	string name;
	len = path.length();

	// path => abc/
	// name => xyz
	if(found != string::npos){

		name.assign(path,0,found);
		path.replace(0,found,"");

	}else{

		name.assign(path,0,len);
		path.replace(0,len,"");

	}
	// search xyz in the node
	for(int i=0;i < node->deadEnd;i++){
		if(node->children[i] != NULL){
			if(node->children[i]->name == name){
				return searcher(node->children[i],path);
			}
		}
	}

	return NULL;

}


void insert_node(const string &path, bool isDir){
	

	string dpath(path);
	string dir_name = getDir(dpath);
	FSMD *dir_node = NULL;
	cout<<"CALLED INSERT NODE\n";

	// check if it is the root
	if(dpath == "/"){

		if(root->children == NULL){
			root->children = MALL(FSMD*,root->deadEnd+1);//changed
		}else{
			root->children = REALL(FSMD*,root->children,root->deadEnd+1);//changed
		}
		
		root->children[root->deadEnd] = make_node(dpath,dir_name,isDir,root);//change
		root->deadEnd++;//changed
		root->noc++;

	}else{

		string pp(path);
		//search for the node
		dir_node = searcher(root,dpath);

		if(dir_node != NULL){

			if(dir_node->parent != NULL){
				dir_node->c_time = time(NULL);
				dir_node->m_time = time(NULL);
			}

			if(root->children == NULL){
				root->children = MALL(FSMD*,root->deadEnd+1);//change
			}else{
				root->children = REALL(FSMD*,root->children,root->deadEnd+1);//change
			}

			dir_node->children = REALL(FSMD*,dir_node->children,dir_node->deadEnd+1);//change
		
			dir_node->children[dir_node->deadEnd] = make_node(dpath,dir_name,isDir,dir_node);//change
			dir_node->deadEnd++;	//change
			dir_node->noc++;
		}

	}

}

int delete_node(FSMD* r){
	// don't delete if it is a file
	if(r == NULL || !r->isDir || r->noc)
		return 0;

	// traverse the parent for the node
	for(int i=0;i < r->parent->deadEnd;i++){	//change
		if(r->parent->children[i] == r){
			r->parent->children[i]->name.clear();
			r->parent->children[i] = NULL;
			r->parent->noc--;
	
			free(r);
			return 0;
		}
	}

	return 1;
}

int delete_file(FSMD *r){
	
	// don't delete if it is a directory
	if(r->isDir || r == NULL || r->noc)
		return 0;

	// traverse the parent for the node
	for(int i=0;i < r->parent->deadEnd;i++){	//change

		if(r->parent->children[i] == r){

			r->parent->children[i] = NULL;
			r->parent->noc--;
			r->data.clear();
			free(r);		
			return 0;
		}
	}

	return 0;

}