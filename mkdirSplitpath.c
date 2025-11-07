#include "types.h"

extern struct NODE* root;
extern struct NODE* cwd;

//make directory
void mkdir(char pathName[]){

    char baseName[64];
    char dirName[64];

    struct NODE* base = splitPath(pathName,baseName,dirName);

    struct NODE* firstChild = base->childPtr;

    struct NODE* newNode = (struct NODE*)malloc(sizeof(struct NODE));

    strcpy(newNode->name,baseName);
    newNode->fileType = 'D';
    newNode->childPtr = NULL;
    newNode->siblingPtr = firstChild;
    newNode->parentPtr = base;

    base->childPtr = newNode;



    return;
}


struct NODE* getChild(struct NODE* directory, char* name){

    struct NODE* child = NULL;
    struct NODE* iterator = directory->childPtr;

    // printf("Directory name: %s, searching name: %s\n", directory->name,name);

    while(iterator != NULL ){
        // printf("strcmp Iterator name: <%s> name: <%s>\n", iterator->name,name);

        int res = strcmp(iterator->name, name);
        // printf("strcmp res: %d\n", res);
        if( res == 0){
            child = iterator;
            break;
        }
        iterator = iterator->siblingPtr;
    }
    if(child == NULL){
        printf("ERROR: directory %s does not exist\n", name);
        return NULL;
    }
    return child;
}

//handles tokenizing and absolute/relative pathing options
struct NODE* splitPath(char* pathName, char* baseName, char* dirName){

    // TO BE IMPLEMENTED
    // NOTE THAT WITHOUT COMPLETING THIS FUNCTION CORRECTLY
    // rm, rmdir, ls, cd, touch COMMANDS WILL NOT EXECUTE CORRECTLY
    // SEE THE PROVIDED SOLUTION EXECUTABLE TO SEE THEIR EXPECTED BEHAVIOR

    // YOUR CODE HERE

    char* mid;
    char hasSlash = 0;
    char* token=pathName;

    if(pathName[0] == '/'){
        token++;
        pathName++;
    }

    //find end
    for(; *token != '\0'; token++){
            //find start of dirname
        if(* token == '/'){
            hasSlash = 1;
        }
    }

    printf("hasSlash: %d\n",hasSlash);

    //if no slash
    if(hasSlash == 0){
        //copy to base
        strcpy(dirName,"");

        //copy to dirname
        strcpy(baseName,pathName);
    }else{

        //go back to a / or start of path.
        while( *token != '/' ){
            token--;
        }

        mid = token;
        *mid = '\0';
        mid++;

        //copy to base
        strcpy(baseName,mid);

        //copy to dirname
        strcpy(dirName,pathName);

    }

    printf("split <%s> to base <%s> and DIR <%s>\n",pathName,baseName,dirName);
    // printf("base: %s\n",baseName);
    // printf("dir: %s\n",dirName);

    char dirnameCopy[128];
    strcpy(dirnameCopy,dirName);

    struct NODE * traversalPtr = root;

    char* splitter = "/";

    if(hasSlash){

        char* dir = strtok(dirnameCopy, splitter);

        while (dir != NULL) {
            traversalPtr = getChild(traversalPtr, dir);
            if(traversalPtr == NULL){
                return NULL;
            }
            printf(" %s\n", dir);
            dir = strtok(NULL, splitter); // Subsequent calls use NULL
        }
    }
    

    

    //
    return traversalPtr;
}
