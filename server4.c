#include <stdio.h>
#include <string.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <unistd.h>

int main() {
    int server_fd;
    struct sockaddr_in server_addr, client_addr;
    char buffer[1024];
    socklen_t addr_len = sizeof(client_addr);

    server_fd = socket(AF_INET, SOCK_DGRAM, 0);
    server_addr.sin_family = AF_INET;
    server_addr.sin_addr.s_addr = INADDR_ANY;
    server_addr.sin_port = htons(8080);

    bind(server_fd, (struct sockaddr *)&server_addr, sizeof(server_addr));

    while (1) {
        memset(buffer, 0, sizeof(buffer));
        recvfrom(server_fd, buffer, 1024, 0, (struct sockaddr *)&client_addr, &addr_len);
        printf("Message from client: %s\n", buffer);
        sendto(server_fd, "Hello from server", strlen("Hello from server"), 0, (struct sockaddr *)&client_addr, addr_len);
    }

    close(server_fd);
    return 0;
}
