/*
** EPITECH PROJECT, 2023
** STEP-1
** File description:
** main.c
*/

#include <stdio.h>
#include "./include/server.h"

int main(__attribute__((unused)) int argc,
         __attribute__((unused)) char const* argv[])
{
    if (argc != 2)
        handle_error(SERVER_USAGE);

    const int PORT = atoi(argv[1]);
    const int server_fd = socket(AF_INET, SOCK_STREAM, 0);

    if (server_fd == FAILURE)
        handle_error("Socket creation");

    struct sockaddr_in server_address, client_address;
    socklen_t client_len = sizeof(client_address);

    memset(&server_address, 0, sizeof(server_address));
    server_address.sin_family = AF_INET;
    server_address.sin_addr.s_addr = INADDR_ANY;
    server_address.sin_port = htons(PORT);

    char buffer[1024];

    if (bind(server_fd, (struct sockaddr*)&server_address,
             sizeof(server_address)) < 0)
        handle_error("Bind error");

    printf("Server started on port %d\n", PORT);

    if (listen(server_fd, QUEUE_LEN) < 0)
        handle_error("Listen");

    printf("Waiting for a client...\n");

    int client_fd =
        accept(server_fd, (struct sockaddr*)&client_address, &client_len);

    if (client_fd < 0)
        handle_error("Accept");

    while (TRUE) {
        int client_fd =
            accept(server_fd, (struct sockaddr*)&client_address, &client_len);

        if (client_fd < 0)
            handle_error("Accept");

        // Display client connection information

        printf("Connection from %s:%d\n", inet_ntoa(client_address.sin_addr),
               ntohs(client_address.sin_port));

        // Write "Hello World!!!" to socket
        strcpy(buffer, "Hello World!!!\n");
        write(client_fd, buffer, strlen(buffer));

        close(client_fd);
    }

    close(server_fd);
    return 0;
}
