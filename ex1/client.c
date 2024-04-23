#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <unistd.h> // For read() and close() functions

#define PORT 8080
#define BUFFER_SIZE 1024

int main() {
    int sock = 0, valread;
    struct sockaddr_in serv_addr;
    char buffer[BUFFER_SIZE] = {0};
    char file_path[BUFFER_SIZE];

    // Get file path from user
    printf("Enter the file path to transfer: ");
    fgets(file_path, BUFFER_SIZE, stdin);
    // Remove newline character from the file path
    file_path[strcspn(file_path, "\n")] = '\0';

    // Create socket file descriptor
    if ((sock = socket(AF_INET, SOCK_STREAM, 0)) < 0) {
        perror("Socket creation error");
        exit(EXIT_FAILURE);
    }

    serv_addr.sin_family = AF_INET;
    serv_addr.sin_port = htons(PORT);

    // Convert IPv4 and IPv6 addresses from text to binary form
    if (inet_pton(AF_INET, "127.0.0.1", &serv_addr.sin_addr) <= 0) {
        perror("Invalid address/ Address not supported");
        exit(EXIT_FAILURE);
    }

    // Connect to server
    if (connect(sock, (struct sockaddr *)&serv_addr, sizeof(serv_addr)) < 0) {
        perror("Connection Failed");
        exit(EXIT_FAILURE);
    }

    FILE *fp = fopen(file_path, "wb");
    if (fp == NULL) {
        perror("Unable to open file");
        exit(EXIT_FAILURE);
    }

    // Receive data from server and write to file
    while ((valread = read(sock, buffer, BUFFER_SIZE)) > 0) {
        fwrite(buffer, 1, valread, fp);
        memset(buffer, 0, BUFFER_SIZE);
    }

    fclose(fp);
    close(sock);
    return 0;
}
