#include <WinSock2.h>
#include <ws2tcpip.H>

#include "parser.h"
#include "responseHandler.h"
#include "utils.h"

#define MAX_SIZE 10000

SOCKET server_fd, client;

void cleanAndClose(){
    closesocket(server_fd);
    closesocket(client);
    WSACleanup();
    exit(1);
}

int main(){
    WSADATA wsaData;    
    if (WSAStartup(MAKEWORD(2,2), &wsaData) != NO_ERROR) {
        printf("WSAStartup failed: %d\n", GetLastError());
        return 1;
      }
    struct sockaddr_in address;
    int addrlen = sizeof(address);
    char buffer[MAX_SIZE] = {0};
    
    if((server_fd = socket(AF_INET, SOCK_STREAM, 0)) == 0){
        perror("Failed to create fd socket\n");
        cleanAndClose();
    }

    address.sin_family = AF_INET;
    address.sin_addr.s_addr = INADDR_ANY;
    address.sin_port = htons(80);

    if(bind(server_fd, (SOCKADDR *)&address, addrlen) < 0){
        perror("Failed to bind fd socket\n");
        cleanAndClose();
    }

    if(listen(server_fd, 10) < 0){
        perror("Failed to listen fd socket\n");
        cleanAndClose();
    }
    printf("[STATUS] Server started listening for incoming con...\n");

    while (1){
        if((client = accept(server_fd, (SOCKADDR *)&address, (socklen_t*)&addrlen)) < 0){
            perror("Failed to accept con\n");
            cleanAndClose();
        }
    
        recv(client, buffer, MAX_SIZE, 0);
        request request = parseRequest(buffer);
        
        manage_request(request, client);
        
        printf("Sent response to client !\n");
    }

    cleanAndClose();
}