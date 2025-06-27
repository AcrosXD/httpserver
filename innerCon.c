#include <WinSock2.h>
#include <ws2tcpip.H>

#include "parser.h"
#include "responseHandler.h"
#include "utils.h"
#include "file_handler.h" 

#define MAX_SIZE 10000

ContentType httpContTypes[8] = {
    {"html",            "text/html"},
    {"css",             "text/css"},
    {"js",              "text/javascript"},

    {"gif",             "image/gif"},
    {"jpeg" || "jpg",   "image/jpeg"},
    {"png",             "image/png"},

    {"mp3",             "audio/mpeg"},
    {"mp4",             "video/mp4"}
};

char* getRequestContentType(const char *filename) {
    char* extPos = strrchr(filename, '.') + 1;

    for (int i = 0; httpContTypes[i].ext != NULL; i++) {
        //printf("Comparing '%s' with '%s'\n", extPos, httpContTypes[i].ext);
        if (strcmp(extPos, httpContTypes[i].ext) == 0) {
            return httpContTypes[i].type;
        }
    }
    return "html";
}

void handle_get(request in_request, int socket){
    char sendBuffer[300] = {0}; 
    char* dataToSend = getFileContent(in_request.path, MAX_SIZE);

    if(dataToSend == NULL){
        sendNotFound(socket);
        return;
    }

    send_data_to_client(socket, dataToSend, getRequestContentType(in_request.path));
    closesocket(socket);
    
    return;
}

void manage_request(request in_request, int socket){

    if(in_request.httpVersion == UNKNWOWN_HTTP_VER){
        sendVerNotSupported(socket);
        return;
    }

    switch(in_request.requestType){
        case GET:
            handle_get(in_request, socket);
            break;
        default:
            sendVerNotSupported(socket);
            break;
    }
}