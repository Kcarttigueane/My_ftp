/*
** EPITECH PROJECT, 2023
** STEP-1
** File description:
** main.c
*/

#include "./include/server.h"

int main(int argc, char const* argv[])
{
    if (argc != 3) {
        printf(SERVER_USAGE);
        return ERROR;
    }
    is_valid_path(argv[2]);

    // signal(SIGINT, sigint_handler);
    // signal(SIGTERM, sigterm_handler);

    server_data_t server_data;
    client_t clients[FD_SETSIZE];
    memset(clients, 0, sizeof(clients));

    init_server(&server_data, argv);

    myFTP_loop(&server_data, clients);

    close(server_data.server_socket_fd);
    return 0;
}

// if (strcmp(username, ANONYMOUS_USERNAME) == 0 &&
//     strcmp(password, ANONYMOUS_PASSWORD) == 0) {
//     printf("Access granted.\n");
//     // Accept the connection and proceed with the FTP commands
// } else {
//     printf("Access denied.\n");
//     // Reject the connection and close the socket
// }
