#include <WinSock2.h>
#include <ws2tcpip.H>

#include "parser.h"
#include "utils.h"
#include "responseHandler.h"

/*
    Build the response to send back to the client

    Parameters: body of the response, response code and the headers
    Returns: 
*/
const char* buildResponse(const char* body, int code, header headers[], size_t header_size){
    char resCode[32] = {0};
    const char* base = "HTTP/1.1 ";
    
    switch (code){
    case 200:
        strcpy(resCode, "200 OK\n");
        break;
    case 404:
        strcpy(resCode, "404 Not Found\n");
        break;
    case 505:
        strcpy(resCode, "505 HTTP Version Not Supported\n");
        break;
    default:
        break;
    }

    const char* repsonseLine = concat(2, base, resCode);
    const char* headersReq;

    size_t n = 0;
    do {
        //headersReq = concat(headersReq, concat(headers->head, concat(": ", concat(headers->value, "\n"))));
        headersReq = concat(4, headers->head, ": ", headers->value, "\n");
        n++;        
    } while (n != (header_size));
    headersReq = concat(2, headersReq, "\n\r\n\r");
    repsonseLine = concat(3, repsonseLine, headersReq, body);

    return repsonseLine;
}

void sendNotFound(int socket){
    header headers[2] = {0};
    const char* data = "<!doctype html><body><h1>404 not found</h1></body>";
    char* size[6]; sprintf(size, "%d", strlen(data));
    
    /*---HEADERS---*/
    strcpy(headers[0].head, "Content-Type"); strcpy(headers[0].value, "text/html; charset=UTF-8");
    strcpy(headers[1].head, "Content-Length"); strcpy(headers[1].value, size);

    const char* response = buildResponse(data, 404, headers, 2);
    send(socket, response, strlen(response), 0);
}

void sendVerNotSupported(int socket){
    header headers[2] = {0};

    /*---HEADERS---*/
    strcpy(headers[0].head, "Content-Type"); strcpy(headers[0].value, "text/plain; charset=UTF-8");

    const char* response = buildResponse("Not Suported", 505, headers, 1);
    send(socket, response, strlen(response), 0);
}

void send_data_to_client(int socket, char* data, char* conty){
    header headers[2] = {0};
    char* size[6]; sprintf(size, "%d", strlen(data));

    char* type = concat(2, conty, "; charset=UTF-8");

    /*---HEADERS---*/
    strcpy(headers[0].head, "Content-Type"); strcpy(headers[0].value, type);
    strcpy(headers[1].head, "Content-Length"); strcpy(headers[1].value, size);

    const char* response = buildResponse(data, 200, headers, 2);
    send(socket, response, strlen(response), 0);
}