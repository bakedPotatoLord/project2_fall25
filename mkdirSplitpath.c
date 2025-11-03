#include "types.h"

extern struct NODE* root;
extern struct NODE* cwd;

//make directory
void mkdir(char pathName[]){

    // TO BE IMPLEMENTED
    //
    // YOUR CODE TO REPLACE THE PRINTF FUNCTION BELOW

    printf("TO BE IMPLEMENTED\n");

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
    char hasSlash = 0;
    char* token=pathName;

    //find end
    for(; *token != '\0'; token++){
            //find start of dirname
        if(* token == '/'){
            hasSlash = 1;
        }
    }

    // printf("hasSlash: %d\n",hasSlash);

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

    // printf("base: %s\n",baseName);
    // printf("dir: %s\n",dirName);
    

    struct NODE temp = {
        baseName,
    }

    //
    return NULL;
}
