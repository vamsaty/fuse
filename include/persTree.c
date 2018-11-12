#include<stdio.h>
#include<stdlib.h>
#define TOTALNODES 6

// size of each node is arbitrarily kept as 30 bytes

typedef struct node {
    int data;
    struct node *children[4];
}node;

node *nodeSpace;
char *nodeSpaceMap;

void initNode(node *initNode) {
    initNode->data = 0;
    int i;

    for(i=0; i<4; i++) {
        initNode->children[i] = NULL;
    }
}

void initNodeSpace() {
    int i; 
    nodeSpace = (node *)malloc(sizeof(node) * TOTALNODES);
    nodeSpaceMap = (char *)malloc(sizeof(char) * TOTALNODES);
    
    for(i=0; i<TOTALNODES; i++) {
        nodeSpaceMap[i] = 'v';
        initNode(&nodeSpace[i]);
    }
}

void freeNodeSpace() {
    free(nodeSpace);
    free(nodeSpaceMap);
}

int getVacantNode() {
    int i;
    for(i=0; i<TOTALNODES; i++) {
        if(nodeSpaceMap[i] == 'v') {
            return i;
        }
    }
    return -1; // no vacant node
}

node *pseudoMalloc() {
    int firstVac = getVacantNode();
    if(firstVac == -1) {
        return NULL; // no memory left
    } else {
        nodeSpaceMap[firstVac] = 'o'; // setting it to occupied
        return &nodeSpace[firstVac]; // memory of first empty node in nodeSpace
    }    
}

void pseudoFree(node *toFree) {
    int indexFreed = toFree - nodeSpace;

    nodeSpaceMap[indexFreed] = 'v';
}

void writeNodeSpaceToFile() {
    FILE *ftr;
    int i, j;

    ftr = fopen("tree.txt", "w");

    fprintf(ftr, "%s\n", nodeSpaceMap); 

    for(i=0; i<TOTALNODES; i++) {
        fprintf(ftr, "%d\n", nodeSpace[i].data);
        // fprintf(ftr, "%d\n", nodeSpace[i].children[0]-nodeSpace);
        // fprintf(ftr, "%d\n", nodeSpace[i].children[1]-nodeSpace);
        // fprintf(ftr, "%d\n", nodeSpace[i].children[2]-nodeSpace);
        // fprintf(ftr, "%d\n", nodeSpace[i].children[3]-nodeSpace);
        for (j=0; j<4; j++) {
            if (nodeSpace[i].children[j] == NULL) {
                fprintf(ftr, "%d\n", -1);
            } else {
                fprintf(ftr, "%d\n", nodeSpace[i].children[j]-nodeSpace);
            }
        }
    }

    fclose(ftr);
}

node *readNodeSpaceFromFile() {
    FILE *ftr;
    int i, j, intBuff;
    long long buff;

    // printf("Hello");

    ftr = fopen("tree.txt", "r");

    fscanf(ftr, "%s", nodeSpaceMap);

    printf("%s\n", nodeSpaceMap);

    for(i=0; i<TOTALNODES; i++) {
        fscanf(ftr, "%d", &nodeSpace[i].data);
        printf("%d\n", nodeSpace[i].data);

        for(j=0; j<4; j++) {
            fscanf(ftr, "%d", &intBuff);

            if(intBuff == -1) {
                nodeSpace[i].children[j] = NULL;
            } else {
                nodeSpace[i].children[j] = &nodeSpace[intBuff];
            }
        }
    }


    fclose(ftr);

    return &nodeSpace[0];
}

node *buildASimpleTree() {
    node *root;

    root = pseudoMalloc(); // 0
    root->data = 0;

    root->children[0] = pseudoMalloc(); // 1
    root->children[0]->data = 10;

    root->children[2] = pseudoMalloc(); // 2 
    root->children[2]->data = 12;

    root->children[1] = pseudoMalloc(); // 3
    root->children[1]->data = 11;
    root->children[1]->children[0] = pseudoMalloc(); //4
    root->children[1]->children[0]->data = 20;

    return root;
}

int main() {
    int i;   
    node *root;

    initNodeSpace();

    // for(i=0; i<TOTALNODES; i++) {
    //     printf("%c,", nodeSpaceMap[i]);
    // }

    // node *p = pseudoMalloc();
    // printf("\n");
    // node *q = pseudoMalloc();

    // for(i=0; i<TOTALNODES; i++) {
    //     printf("%c,", nodeSpaceMap[i]);
    // }    

    // pseudoFree(p);
    // printf("\n");

    // for(i=0; i<TOTALNODES; i++) {
    //     printf("%c,", nodeSpaceMap[i]);
    // }  

    // root = buildASimpleTree();

    // printf("%d", nodeSpace[3].children[0]-nodeSpace);

    // writeNodeSpaceToFile();

    root = readNodeSpaceFromFile();

    printf("\nContents Of nodeSpace\n");
    for(i=0; i<TOTALNODES; i++) {
        printf("%d\n", nodeSpace[i].data);
    }


    // char string[10];

    // FILE *ftr;

    // ftr = fopen("tree.txt", "r");

    // fscanf(ftr, "%s", string);

    // printf("%s", string);

    // freeNodeSpace();
    return 0;
}

