#include "types.h"

extern struct NODE* root;
extern struct NODE* cwd;


struct NODE* getChild(struct NODE* directory, char* name){

    struct NODE* child = NULL;
    struct NODE* iterator = directory->childPtr;

    // printf("Directory name: %s, searching name: %s\n", directory->name,name);

    if(iterator == NULL){
        // printf("getChild iterator is NULL\n");
        return NULL;
    }

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
    
    return child;
}

//make directory
void mkdir(char pathName[]){

    char baseName[64];
    char dirName[64];

    char pathNameCopy[64];
    strcpy(pathNameCopy,pathName);

    struct NODE* base = splitPath(pathName,baseName,dirName);

    if(base == NULL){
        //if splitPath returns NULL
        return;
    }
    struct NODE* firstChild = base->childPtr;

    //check for no name
    if(baseName[0] == '\0'){
        printf("MKDIR ERROR: no path provided\n");
        return;
    }

    //check for duplicate node
    if(getChild(base,baseName) != NULL){
        printf("MKDIR ERROR: directory %s already exists\n", baseName);
        return;
    }

    struct NODE* newNode = (struct NODE*)malloc(sizeof(struct NODE));

    strcpy(newNode->name,baseName);
    newNode->fileType = 'D';
    newNode->childPtr = NULL;
    newNode->siblingPtr = firstChild;
    newNode->parentPtr = base;

    base->childPtr = newNode;

    printf("MKDIR SUCCESS: node %s successfully created\n", pathNameCopy);

    return;
}




//handles tokenizing and absolute/relative pathing options
struct NODE* splitPath(char* pathName, char* baseName, char* dirName){

    // TO BE IMPLEMENTED
    // NOTE THAT WITHOUT COMPLETING THIS FUNCTION CORRECTLY
    // rm, rmdir, ls, cd, touch COMMANDS WILL NOT EXECUTE CORRECTLY
    // SEE THE PROVIDED SOLUTION EXECUTABLE TO SEE THEIR EXPECTED BEHAVIOR

    // YOUR CODE HERE

    char* mid;
    char slashCount = 0;
    char firstSlash = 0;
    char* token=pathName;

    char pathNameCopy[64];
    strcpy(pathNameCopy,pathName);

    //find end
    for(; *token != '\0'; token++){
            //find start of dirname
        if(* token == '/'){
            slashCount++;
            if(token ==pathName){
                //if on first char
                firstSlash = 1;
            }
        }
    }

    // printf("first slash: <%hhu>, slash count: <%hhu>\n",firstSlash,slashCount);

    //if no slash
    if(slashCount == 0){
        //copy empty string to base
        strcpy(dirName,"");

        //copy to dirname
        strcpy(baseName,pathName);
        return root;
    }else{

        if(firstSlash && slashCount == 1){ //ex: "/a"
            //copy to dirname and basename
            strcpy(dirName,"");
            strcpy(baseName,pathName+1);
            return root;
        }
        else{
            //ex: /a/b/c or a/b 

            //token starts at end. iterate back until on a slash
            for(; *token != '/'; token--){}

            //turn slash to null
            mid = token;
            *mid = '\0';
            mid++;

            //copy to base
            strcpy(baseName,mid);

            //copy to dirname
            strcpy(dirName,pathName);
        }
    }

    // printf("split <%s> to base <%s> and DIR <%s>\n",pathNameCopy,baseName,dirName);
    // printf("base: %lu\n",(size_t)baseName);
    // printf("dir: %lu\n",(size_t)dirName);

    char dirnameCopy[128];
    strcpy(dirnameCopy,dirName);

    struct NODE * traversalPtr = root;

    char* splitter = "/";

    

    // if(dirnameCopy[0] == '/'){
    //     printf("dirnameCopy: %s\n",dirnameCopy);
    // }

    // printf("begin traverse\n");

    char* dir = strtok(dirnameCopy, splitter);

    while (dir != NULL) {
        traversalPtr = getChild(traversalPtr, dir);
        if(traversalPtr == NULL){
            printf("ERROR: directory %s does not exist\n", dir);
            return NULL;
        }
        // printf(" %s\n", dir);
        dir = strtok(NULL, splitter); // Subsequent calls use NULL
    }
    
    // printf("end traverse\n");
    
    //
    return traversalPtr;
}
