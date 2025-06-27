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
    size_t mem_to_alloc = 1; //Null char terminator added
    size_t offset = 0;
    //Using n as a ref value and letting i do the work (what a lazy ass)
    //Using n as a ref value and letting i do the work (what a lazy ass)
    int i = n;

    //Init va list
    //Init va list
    va_list args;
    va_start(args, n);
    //Compute the amount of memory needed
    do {
        mem_to_alloc += strlen(va_arg(args, char*));
        i--;
    } while(i != 0);
    //Allocate it
    //Allocate it
    char* res = malloc(mem_to_alloc);
    va_end(args);

    i = n;
    va_start(args, n);
    //Concatenate loop
    //Concatenate loop
    do {
        //Taking a string from the va list
        //Taking a string from the va list
        char* string = va_arg(args, char*);
        //Putting it in the final string shifted by the offset
        //Putting it in the final string shifted by the offset
        strcpy(res + offset, string);
        //The offset equals the current string length plus the sum of the previous ones
        //The offset equals the current string length plus the sum of the previous ones
        offset += strlen(string);
        i--;
    } while(i != 0);
    va_end(args);
    
    
    return res;
}

