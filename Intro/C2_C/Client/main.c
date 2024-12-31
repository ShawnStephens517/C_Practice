// Client Program
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <errno.h>

#define PORT 8080
#define BUFFER_SIZE 1024

int main()
{
    int sock = 0;
    struct sockaddr_in serv_addr;
    char buffer[BUFFER_SIZE] = {0};

    // Creating socket file descriptor
    if ((sock = socket(AF_INET, SOCK_STREAM, 0)) < 0)
    {
        perror("Socket creation error");
        return -1;
    }

    serv_addr.sin_family = AF_INET;
    serv_addr.sin_port = htons(PORT);

    // Convert IPv4 and IPv6 addresses from text to binary form
    if (inet_pton(AF_INET, "127.0.0.1", &serv_addr.sin_addr) <= 0)
    {
        perror("Invalid address or Address not supported");
        return -1;
    }

    // Connect to the server
    if (connect(sock, (struct sockaddr *)&serv_addr, sizeof(serv_addr)) < 0)
    {
        perror("Connection failed");
        return -1;
    }

    while (1)
    {
        // Receive command from server
        memset(buffer, 0, BUFFER_SIZE);
        int valread = read(sock, buffer, BUFFER_SIZE);
        if (valread <= 0)
        {
            printf("Server disconnected.\n");
            break;
        }

        printf("Command received from server: %s\n", buffer);

        // Execute the command
        char response[BUFFER_SIZE];
        FILE *fp = popen(buffer, "r");
        if (fp == NULL)
        {
            snprintf(response, BUFFER_SIZE, "Error executing command: %s", strerror(errno));
        }
        else
        {
            fread(response, 1, BUFFER_SIZE - 1, fp);
            pclose(fp);
        }

        // Send response back to server
        send(sock, response, strlen(response), 0);
        printf("Response sent to server: %s\n", response);
    }

    close(sock);
    return 0;
}