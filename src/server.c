#include <stdio.h>
#include <winsock2.h>
#include <ws2tcpip.h>

#pragma comment(lib, "ws2_32.lib")

DWORD WINAPI handle_client(LPVOID socket_ptr)
{
    SOCKET client_sock = *(SOCKET *)socket_ptr;
    char buffer[512];

    int bytes = recv(client_sock, buffer, sizeof(buffer) - 1, 0);
    buffer[bytes] = '\0';
    printf("Message from client:%s\n", buffer);

    char *reply = "This is server handling multiple clients!";
    send(client_sock, reply, strlen(reply), 0);
    printf("Reply sent!\n");

    closesocket(client_sock);
    return 0;
}

int main()
{
    struct WSAData wsa;
    SOCKET server_sock, client_sock;
    struct sockaddr_in server_addr, client_addr;
    int client_addr_len = sizeof(client_addr);

    WSAStartup(MAKEWORD(2, 2), &wsa);

    server_sock = socket(AF_INET, SOCK_STREAM, 0);

    server_addr.sin_family = AF_INET;
    server_addr.sin_addr.s_addr = INADDR_ANY;
    server_addr.sin_port = htons(8080);
    bind(server_sock, (struct sockaddr *)&server_addr, sizeof(server_addr));

    listen(server_sock, 1);
    printf("Server listening on port 8080");

    while (1)
    {
        client_sock = accept(server_sock, (struct sockaddr *)&client_addr, &client_addr_len);
        printf("Client is connected");

        CreateThread(NULL, 0, handle_client, &client_sock, 0, NULL);
    }

    closesocket(server_sock);
    WSACleanup();

    return 0;
}