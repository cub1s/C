#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <unistd.h>

int main() {

    char server_message[256] = "Success! You have reached the server.";

    // create server socket
    int server_socket;
    server_socket = socket(AF_INET, SOCK_STREAM, 0);

    // define server address
    struct sockaddr_in server_address;
    server_address.sin_family = AF_INET;
    server_address.sin_port = htons(8181);
    server_address.sin_addr.s_addr = INADDR_ANY;

    // bind socket to specified IP and port
    bind(server_socket, (struct sockaddr*) &server_address, sizeof(server_address));

    // listen for connections
    listen(server_socket, 1);

    int client_socket;
    client_socket = accept(server_socket, NULL, NULL);

    // receive from remote socket
    char client_message[256];
    recv(client_socket, &client_message, sizeof(client_message), 0);

    // send the server message
    send(client_socket, client_message, sizeof(server_message), 0);

    // close the socket
    close(server_socket);

    return 0;
}