#include <stdio.h>
#include <string.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <unistd.h>

int main() {
    int sock;
    struct sockaddr_in server_addr;
    char buffer[1024];
    socklen_t addr_len = sizeof(server_addr);

    sock = socket(AF_INET, SOCK_DGRAM, 0);
    server_addr.sin_family = AF_INET;
    server_addr.sin_port = htons(8080);
    inet_pton(AF_INET, "127.0.0.1", &server_addr.sin_addr);

    sendto(sock, "Hello from client", strlen("Hello from client"), 0, (struct sockaddr *)&server_addr, addr_len);
    recvfrom(sock, buffer, 1024, 0, (struct sockaddr *)&server_addr, &addr_len);
    printf("Message from server: %s\n", buffer);

    close(sock);
    return 0;
}
