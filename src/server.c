#include <stdio.h>
#include <winsock2.h>
#include <ws2tcpip.h>

#pragma comment(lib, "ws2_32.lib")

int main()
{
    struct WSAData wsa;
    SOCKET server_sock, client_sock;
    struct sockaddr_in server_addr, client_addr;
    int client_addr_len = sizeof(client_addr);
    char buffer[512];

    WSAStartup(MAKEWORD(2, 2), &wsa);

    server_sock = socket(AF_INET, SOCK_STREAM, 0);

    server_addr.sin_family = AF_INET;
    server_addr.sin_addr.s_addr = INADDR_ANY;
    server_addr.sin_port = htons(8080);
    bind(server_sock, (struct sockaddr *)&server_addr, sizeof(server_addr));

    listen(server_sock, 1);
    printf("Server listening on port 8080");

    client_sock = accept(server_sock, (struct sockaddr *)&client_addr, &client_addr_len);
    printf("Client Connected");

    int bytes = recv(client_sock, buffer, sizeof(buffer) - 1, 0);
    buffer[bytes] = '\0';
    printf("message from client is:%s\n", buffer);

    char *reply = "Hello from server";
    send(client_sock, reply, strlen(reply), 0);
    printf("Reply sent!\n");

    closesocket(client_sock);
    closesocket(server_sock);
    WSACleanup();

    return 0;
}