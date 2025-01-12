#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <unistd.h>

int main() {
    
    // create a socket
    int client_socket;
    client_socket = socket(AF_INET, SOCK_STREAM, 0);
    char message_to_server[] = "This is my custom message! I hope I get it sent back to me.";

    // specify address to for socket to connect to
    struct sockaddr_in server_address;
    server_address.sin_family = AF_INET;
    server_address.sin_port = htons(8181);
    server_address.sin_addr.s_addr = INADDR_ANY;

    // connect to other socket
    int connect_status = connect(client_socket, (struct sockaddr*) &server_address, sizeof(server_address));
    // check for error in connection
    if (connect_status == 1) {
        printf("There was an error connecting to the remote socket. \n\n");
    }

    // send the server message
    send(client_socket, message_to_server, sizeof(message_to_server), 0);

    // receive from remote socket
    char server_response[256];
    recv(client_socket, &server_response, sizeof(server_response), 0);
    
    // print out data from remote socket
    printf("The server responded with: %s\n", server_response);

    // close the socket
    close(client_socket);

    return 0;
}