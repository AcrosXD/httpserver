#include "utils.h"

/*
    Old concat function
*/

// char* concat(const char* s1, const char* s2){
//     char* res = malloc(strlen(s1) + strlen(s1) + 1);

//     strcpy(res, s1);
//     strncat(res, s2, strlen(s1) + strlen(s1) + 1);

//     return res;
// }


/*
    Concatenate n number of strings
    Parameters: Number of strings to concatenate, const char* to concatenate
    Returns: One char* of concatenated strings
*/
char* concat(unsigned int n, ...){
    size_t mem_to_alloc = 1;
    size_t offset = 0;
    int i = n;

    va_list args;
    va_start(args, n);
    do {
        mem_to_alloc += strlen(va_arg(args, char*));
        i--;
    } while(i != 0);
    char* res = malloc(mem_to_alloc);
    va_end(args);

    i = n;
    va_start(args, n);
    do {
        char* string = va_arg(args, char*);
        strcpy(res + offset, string);
        offset += strlen(string);
        i--;
    } while(i != 0);
    va_end(args);
    

    return res;
}