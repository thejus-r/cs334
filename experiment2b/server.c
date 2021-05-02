#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <netinet/in.h>
#include <string.h>

#define PORT 8080

int main(int argc, char *argv[])
{
    int serverDescriptor, newSocket, valueRead;
    struct sockaddr_in address;
    int opt = 1;
    int addrLength = sizeof(address);
    char buffer[1024] = {0};
    char *message = "Hello from Server";

    // Create Socket
    if ((serverDescriptor = socket(AF_INET, SOCK_STREAM, 0)) == 0)
    {
        perror("SOCKET_FAILED");
        exit(EXIT_FAILURE);
    }

    if (setsockopt(serverDescriptor, SOL_SOCKET, SO_REUSEADDR | SO_REUSEPORT, &opt, sizeof(opt)))
    {
        perror("SETSOCKET");
        exit(EXIT_FAILURE);
    }

    address.sin_family = AF_INET;
    address.sin_addr.s_addr = INADDR_ANY;
    address.sin_port = htons(PORT);

    // Binding the Socket

    if ((bind(serverDescriptor, (struct sockaddr *)&address, sizeof(address)) < 0))
    {
        perror("BINDING_FAILED");
        exit(EXIT_FAILURE);
    }

    if (listen(serverDescriptor, 3) < 0)
    {
        perror("LISTEN");
        exit(EXIT_FAILURE);
    }

    if ((newSocket = accept(serverDescriptor, (struct sockaddr *)&address, (socklen_t *)&address)) < 0)
    {
        perror("ACCEPT");
        exit(EXIT_FAILURE);
    }

    valueRead = read(newSocket, buffer, 1023);
    printf("%s\n", buffer);
    send(newSocket, message, strlen(message), 0);
    printf("Message Sent!");
    return 0;
}