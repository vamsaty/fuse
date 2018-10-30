#include<stdio.h>
#include<stdlib.h>
#include<string.h>


dataStruct * copyTodataStruct(FSMD* nd);

FSMD* copyToNode(dataStruct* ds);

int writeOneToFile(FILE* fp,FSMD* nd);

FSMD* readOneFromFile(FILE* fp);

int writeToFile(char* filepath,FSMD* root);

FSMD* readFromFile(char* filepath);