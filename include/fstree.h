#ifndef FSTREE
#define FSTREE

#include<bits/stdc++.h>
#include <fuse.h>
// #include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <time.h>
#include <string.h>
#include <stdlib.h>
#include <errno.h>

#define ll unsigned long long

#define CALL(a,b) (a*)calloc(sizeof(a),b)
#define MALL(a,b) (a*)malloc(sizeof(a)*b)
#define REALL(a,b,c) (a*)realloc(b,sizeof(a)*c)
#define B_SIZE(x)rev (x/512) + 1

#define INIT_SIZE 1048576
#define BLOCK_SIZE 4096

using namespace std;

struct sss_metadata{
	// string path;
	// string name;
	// string content;
	string path;
	string name;
	string data;
	off_t size;
	long int offset;
	
	bool isDir;
	mode_t permissions;
	uid_t user_id;
	gid_t group_id;

	int noc;
	int nof;
	
	time_t a_time;                  // Access time
    time_t m_time;                  // Modified time
    time_t c_time;                  // Status change time
    time_t b_time;                  // Creation time
    
    unsigned long int inode_number; // Inode number of the node in disk    
    struct sss_metadata * parent;         // Pointer to parent node
    
    set<struct sss_metadata*> chills;

    struct sss_metadata ** children;      // Pointers to children nodes
};



typedef struct sss_metadata FSMD;

extern FSMD * root;

// time_t TIMED_;

// extern MD * root;


// TREE OPERATIONS / METHODS


FSMD *make_node(string path,const string name,bool dir,FSMD *parent);
FSMD *make_dir_node(string name);
FSMD *make_file_node(string name);
FSMD *search(FSMD*,string);
FSMD *searcher(FSMD*,string);
// FSMD *searcher(FSMD*,string&);
void insert_node(const string,bool isDir);
void insert_file(const string);
string getDir(string &s);
FSMD *create_tree();
void temp_files(FSMD **);

#endif
