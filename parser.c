#include "parser.h"

HttpTypesLUT httpTypes[] = {
    {"GET", GET},
    {"POST", POST},
    {"DELETE", hDELETE},
    {"UPDATE", UPDATE},
    {NULL, UNKNWOWN_HTTP_TYPE}
};

HttpVersLUT httpVer[] = {
    {"HTTP/0.9", HTTP09},
    {"HTTP/1.0", HTTP10},
    {"HTTP/1.1", HTTP11},
    {NULL, UNKNWOWN_HTTP_VER}
};

/*
    Find the request type with the request type LUT

    Parameters: unparsed, valid request type
    Returns: http_request_type enum
*/
http_request_type getRequestType(const char *bufferType) {
    for (int i = 0; httpTypes[i].method != NULL; i++) {
        printf("Comparing '%s' with '%s'\n", bufferType, httpTypes[i].method);
        if (strcmp(bufferType, httpTypes[i].method) == 0) {
            return httpTypes[i].type;
        }
    }
    return UNKNWOWN_HTTP_TYPE;
}

/*
    Find the http version with the http version LUT

    Parameters: unparsed, valid http version
    Returns: http_version enum
*/
http_version getHttpVersion(const char *bufferVer) {
    for (int i = 0; httpVer[i].ogVersion != NULL; i++) {
        if (strcmp(bufferVer, httpVer[i].ogVersion) == 0) {
            return httpVer[i].version;
        }
    }
    return UNKNWOWN_HTTP_VER;
}

/*
    Parse the data of a given http request into a easier to read request struct.

    Parameters: data char array to parse
    Returns: request struct
*/
request parseRequest(char data[]){
    request request = {0};

    char bufferType[6] = {0};
    char bufferVer[15] = {0};

    /* Lines:
        1 -             Request line
        2 to EL + 1 -   Headers
        EL + 1 to end - Body & data 
    */
    int line = 1;
    size_t tokens = 1;

    //Iterator for a single char in each token
    size_t k = 0;

    for (int i = 0; i < strlen(data); i++){
        //For each line the token counter resets as well as the token iterator, each line is ends by "\n"
        if(data[i] == '\n') { line++; tokens = 1; k=0;}

        //In line one the token separator is a space
        if(line == 1 && data[i] == ' '){ tokens++; k=0; };
        //Exclude the token separator (space) and for each token is attrubuted a data type
        if (line == 1 && data[i] != ' ' && data[i] != '\r'){
            
            //We take care to limit the number of character that is passed through the buffers
            switch (tokens){
                case 1:
                    bufferType[k] = data[i];
                    break;
                case 2:
                //Precaution if too much data is sent
                    if(k > 2083) 
                    request.path[k] = data[i];
                    break;
                case 3: 
                    bufferVer[k] = data[i];
                    break;
            }
            k++;
        } 

        //When the first line is parsed the new token separator is ": "(: + space)
        if(line > 1 && data[i] == ':' && data[i+1] == ' ') { tokens++; k=0; }
        //We exclude the token separator from 
        if (line > 1 && data[i] != '\n' && data[i] != ':' && (data[i-1] != ':' && data[i] != ' ') && data[i] != '\r'){
            switch (tokens){
                case 1:
                    request.headers[line-2].head[k] = data[i];
                    break;
                case 2:
                    request.headers[line-2].value[k] = data[i];
                    break;
            }
            k++; 
        }  
        if(data[i] == '\r' && data[i+1] == '\n' && data[i+2] == '\r') { strcpy(request.body, &data[i]); break; }
        
    }

    if (bufferType[0] != '\0') {
        request.requestType = getRequestType(bufferType);
        if (request.requestType == UNKNWOWN_HTTP_TYPE) {
            fprintf(stderr, "Unsupported request type: %s\n", bufferType);
        }
    }

    if (bufferVer[0] != '\0') {
        request.requestType = getHttpVersion(bufferVer);
        if (request.httpVersion == UNKNWOWN_HTTP_VER) {
            fprintf(stderr, "Unsupported request version: %s\n", bufferVer);
        }
    }

    return request;
}