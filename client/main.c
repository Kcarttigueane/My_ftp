/*
** EPITECH PROJECT, 2023
** client
** File description:
** main.c
*/

#include "./include/client.h"

int main(int argc, char const* argv[])
{
    if (argc != 3)
        handle_error("Usage: ./client [ip address] [port]");

    const char* IP_ADDRESS = argv[1];
    const int PORT = atoi(argv[2]);

    int client_fd = socket(AF_INET, SOCK_STREAM, 0);
    struct sockaddr_in server_address;
    char buffer[BUFFER_SIZE];

    if (client_fd == FAILURE)
        handle_error("Socket");

    memset(&server_address, 0, sizeof(server_address));

    server_address.sin_family = AF_INET;
    server_address.sin_port = htons(PORT);

    if (inet_pton(AF_INET, IP_ADDRESS, &server_address.sin_addr) <= 0)
        handle_error("inet_pton");

    if (connect(client_fd, (struct sockaddr*)&server_address,
                sizeof(server_address)) < 0)
        handle_error("Connect");

    printf("Connected to %s:%d\n", IP_ADDRESS, PORT);

    read(client_fd, buffer, BUFFER_SIZE);

    printf("Server said: %s\n", buffer);

    close(client_fd);
    return 0;
}
