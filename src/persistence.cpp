#include<bits/stdc++.h>
// #include "tree.h"
// #include<string.h>
#include "../include/fstree.h"
// #include "../include/persistence.h";
FSMD *root;

dataStruct * copyTodataStruct(FSMD* nd){
	
	dataStruct* ds = (dataStruct*)malloc(sizeof(dataStruct));
	
	ds->size = nd->size;
	ds->offset = nd->offset;
	
	strcpy(ds->name,(nd->name).c_str());
	strcpy(ds->data,(nd->data).c_str());

	ds->isDir = nd->isDir;
	ds->isDeleted = nd->isDeleted;
	ds->permissions = nd->permissions;
	ds->user_id = nd->user_id;
	ds->group_id = nd->group_id;

	ds->noc = nd->noc;
	ds->nof = nd->nof;
	ds->deadEnd = nd->deadEnd;

	ds->a_time = nd->a_time;  
    ds->m_time = nd->b_time;
    ds->c_time = nd->b_time;
    ds->b_time = nd->b_time;	

    return ds;
}

FSMD* copyToNode(dataStruct* ds){
	
	string name(ds->name);
	FSMD* nd = make_node(name,"/",0,NULL);

	cout<<"NAME : "<<name<<"\t"<<"number of children : "<<ds->noc<<"\n";

	if(nd != NULL)
		printf("YESSSSS");

	nd->name.assign(ds->name);
	nd->data.assign(ds->data);

	nd->size = ds->size;
	nd->offset = ds->offset;

	nd->isDir = nd->isDir;
	nd->isDeleted = ds->isDeleted;
	nd->permissions = ds->permissions;
	nd->user_id = ds->user_id;
	nd->group_id = ds->group_id;

	nd->noc = nd->noc;
	nd->nof = nd->nof;
	nd->deadEnd = nd->deadEnd;

	nd->a_time = ds->a_time;  
    nd->m_time = ds->b_time;
    nd->c_time = ds->b_time;
    nd->b_time = ds->b_time;

    return nd;
}

int writeOneToFile(FILE* fp){
	// FILE * fp = fopen("data","wb");
	
	dataStruct* ds = copyTodataStruct(nd);

	if (fp != NULL){
		
		cout<<"NAME\n"<< root->name;
		fwrite(ds, sizeof(struct dataStruct),1,fp);
		
		return 1;
	}
	return 0;
}

FSMD* readOneFromFile(FILE* fp){
	dataStruct* ds = (dataStruct*)malloc(sizeof(dataStruct));
	// FILE * fp = fopen("data","rb");
	if(fp != NULL){
		
		int check = fread(ds,sizeof(dataStruct),1,fp);
		printf("No of items:%d  ",check);
		return copyToNode(ds);

	}
	return NULL;
}

int writeToFile(char* filepath){
	cout<<"--------------------------------------WRITE TO FILE----------------------------";
	FILE * fp = fopen("../.data","wb");
	if(fp != NULL){
		writeOneToFile(fp);
		for(int i=0;i < root->noc;i++){
			if(root->children[i] != NULL)
				writeOneToFile(fp,root->children[i]);
		}
		fclose(fp);
		return 1;
	}

	return 0;
}

FSMD* readFromFile(char* filepath){
	cout<<"--------------------------------------READ FROM FILE----------------------------";
	FILE * fp = fopen("../.data","rb");
	if (fp != NULL){
		root = readOneFromFile(fp);
		for(int i=0;i < root->noc;i++){
			root->children[i] = readOneFromFile(fp);
		}
		return root;
	}
	return 0;
}
