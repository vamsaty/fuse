#include "../include/fstree.h"

FSMD *make_node(string path,const string name,bool dir,FSMD *parent){
	

	cout<<"MAKE NODE CALLED\t\t"<<path<<"\t"<<"name -- "<<name<<"\n";

	time_t at,bt,ct,mt;
	FSMD *nd = MALL(FSMD, 1);
	
	nd->isDir = dir;
	nd->permissions = (dir)? (S_IFDIR | 0777) : (S_IFREG | 0777);
	
	nd->name.assign(name);
	nd->path.assign(path);

	nd->size = 0;
	nd->inode_number = 0;
	nd->noc = 0;
	nd->nof = 0;

	nd->group_id = getgid();
	nd->user_id = getuid();

	nd->a_time = time(&at);
	nd->m_time = time(&mt);
	nd->c_time = time(&ct);
	nd->b_time = time(&bt);
	
	nd->children = NULL;
	nd->parent = parent;

	return nd;
}

FSMD *create_tree(){
	return make_node("/","root",1,NULL);
}

string getDir(string &path){
	//gets the directory_name plus it changes the path value
	string dir(path);
	string final;
	
	if(dir.back()=='/'){
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

	if(found != string::npos && found+1 != len){
	    final.assign(dir,found+1,len-found);
	    path.replace(found+1,path.length(),"");
	}
    if(path.length()>1 && path.back()=='/')
    	path.pop_back();
    
	return final;
}


FSMD *search(FSMD *node,string name){
	// cout<<"seraching--------------------------------------------------------------------------------\n";
	for(int i=0;i<node->noc;i++){
		if(node->children[i]->name == name){
			return node->children[i];
		}
	}

	return NULL;
}


FSMD *searcher(FSMD *node, string path){

	int len = path.length();
	if(!len)
		return node;
	
	if(path.front() == '/'){
		if(len > 1)
			path.erase(path.begin());
	}

	size_t found = path.find("/");
	string name;
	len = path.length();

	if(found != string::npos){

		name.assign(path,0,found);
		path.replace(0,found,"");

	}else{

		name.assign(path,0,len);
		path.replace(0,len,"");

	}
	
	for(int i=0;i < node->noc;i++){
		if(node->children[i] != NULL){
			if(node->children[i]->name == name){
				return searcher(node->children[i],path);
			}
		}
	}

	return NULL;

}




void insert_node(const string path, bool isDir){
	

	string dpath(path);
	string dir_name = getDir(dpath);
	FSMD *dir_node = NULL;
	cout<<"CALLED INSERT NODE\n";
	if(dpath == "/"){
		cout<<"here\n";
		if(root->children == NULL){
			root->children = MALL(FSMD*,root->noc+1);
		}else{
			root->children = REALL(FSMD*,root->children,root->noc+1);
		}
		
		root->children[root->noc] = make_node(dpath,dir_name,isDir,root);
		root->noc++;

	}else{

		string pp(path);
		dir_node = searcher(root,dpath);
		
		cout<<"path -> "<<path<<"\t"<<dpath<<"\t"<<dir_name<<"\n";
		
		if(dir_node == NULL)cout<<"failed\n";
		
		cout<<"parent = "<<dir_node->parent->name<<"\n";

		if(dir_node != NULL){

			if(dir_node->parent != NULL){
				dir_node->c_time = time(NULL);
				dir_node->m_time = time(NULL);
			}

			if(root->children == NULL){
				root->children = MALL(FSMD*,root->noc+1);
			}else{
				root->children = REALL(FSMD*,root->children,root->noc+1);
			}

			dir_node->children = REALL(FSMD*,dir_node->children,dir_node->noc+1);
		
			dir_node->children[dir_node->noc] = make_node(dpath,dir_name,isDir,dir_node);
			dir_node->noc++;
		}

	}


}




void temp_files(FSMD **d){
	
	cout<<"heeeeeeeeeeeeeeeeeeeeeeeeeeeeerrrrrrrrrrrrrrrrrrrrrrrrrrre\n";
	cout<<root->path<<"her"<<"\n";
	const string dir(root->path+"her");
	insert_node(dir,1);

}





