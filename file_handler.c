#include "parser.h"
#include "utils.h"

/*
    Get the content of a given file

    Parameters: path from the project root, size of file conten
    Returns: requested file content, NULL in case of an error
*/
char* getFileContent(char* path, size_t size){

    FILE* file = fopen(concat(2, ".\\www\\", path), "r");
        char* currData[260];
        char* filecontent = malloc(size + 1);

        if(file){
            while (fgets(currData, size, file)){
                filecontent = concat(2, filecontent, currData);
            }
            return filecontent;
        }
           
        return NULL;
        fclose(file);
}