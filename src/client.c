#include <stdio.h>
#include <winsock2.h>
#include <ws2tcpip.h>

#pragma comment(lib, "ws2_32.lib")

int main()
{
    struct WSAData wsa;
    SOCKET sock;
    struct sockaddr_in server_addr;
    char *message = "Hello from bigyan!";

    WSAStartup(MAKEWORD(2, 2), &wsa);

    sock = socket(AF_INET, SOCK_STREAM, 0);

    server_addr.sin_family = AF_INET;
    server_addr.sin_port = htons(8080);
    server_addr.sin_addr.s_addr = inet_addr("127.0.0.1");

    connect(sock, (struct sockaddr *)&server_addr, sizeof(server_addr));
    printf("Connected to the server");

    send(sock, message, strlen(message), 0);
    printf("message sent:%s\n", message);

    char buffer[512];
    int bytes = recv(sock, buffer, sizeof(buffer) - 1, 0);
    buffer[bytes] = '0';
    printf("Replyy from server:%s\n", buffer);

    closesocket(sock);
    WSACleanup();

    return 0;
}