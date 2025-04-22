#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#define MAX_ALLOWED_HEADERS 16

typedef enum http_version {
    HTTP09,
    HTTP10,
    HTTP11,
    UNKNWOWN_HTTP_VER
} http_version;

//Struct for the lookup table 
typedef struct {
    const char* ogVersion;
    http_version version;
} HttpVersLUT; 

typedef enum http_request_type {
    GET,
    POST,
    hDELETE,
    UPDATE,
    UNKNWOWN_HTTP_TYPE
} http_request_type;

typedef struct {
    const char* method;
    http_request_type type;
} HttpTypesLUT; 

typedef struct {
    //         Head     |      Value
    //e.g: Content-Type: application/json
    char head[32];
    char value[255];
} header;


typedef struct {
    //Request line (1st line)
    http_request_type requestType;
    char path[2083];
    http_version httpVersion;

    //List of request's header 
    //TODO: Dynamic array, because an unnecessary number of ressource could be used 
    //in vain and the current implementation limits the number of headers
    header headers[MAX_ALLOWED_HEADERS];

    char body[2048];
} request;

request parseRequest(char data[]);
