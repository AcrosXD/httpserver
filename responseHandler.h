void sendNotFound(int socket);
void sendVerNotSupported(int socket);
void send_data_to_client(int socket, char* data, char* conty);
void manage_request(request in_request, int socket);

typedef struct {
    char* ext;
    char* type;
} ContentType;
