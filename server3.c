#include <stdio.h>
#include <string.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <unistd.h>
#include <stdlib.h>

int main() {
    int server_fd, new_socket;
    struct sockaddr_in address;
    int addrlen = sizeof(address);
    char buffer[1024] = {0};

    server_fd = socket(AF_INET, SOCK_STREAM, 0);
    address.sin_family = AF_INET;
    address.sin_addr.s_addr = INADDR_ANY;
    address.sin_port = htons(8080);

    bind(server_fd, (struct sockaddr *)&address, sizeof(address));
    listen(server_fd, 3);

    while (1) {
        new_socket = accept(server_fd, (struct sockaddr *)&address, (socklen_t*)&addrlen);

        if (fork() == 0) {  // Child process
            close(server_fd);  // Child doesn't need access to the listening socket

            read(new_socket, buffer, 1024);
            printf("Message from client: %s\n", buffer);
            send(new_socket, "Hello from server", strlen("Hello from server"), 0);
            
            close(new_socket);  // Close the connection with the client
            exit(0);  // Terminate the child process
        } else {
            close(new_socket);  // Parent closes the client socket
        }
    }

    close(server_fd);
    return 0;
}
