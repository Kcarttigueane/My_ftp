/*
** EPITECH PROJECT, 2022
** Repositery-MyFTP
** File description:
** user_command.c
*/

#include "server.h"

void user_command()
{
    printf("USER command\n");
    // Send USER command to server
    // char user[1024];
    // printf("Enter username: ");
    // fgets(user, 1024, stdin);
    // user[strcspn(user, "\n")] = 0;  // remove newline character from input

    // char command[1024];
    // sprintf(command, "USER %s\r\n", user);
    // send(clientSocket, command, strlen(command), 0);

    // Receive response from server
    // char response[1024];
    // recv(clientSocket, response, 1024, 0);

    // // Parse and handle server response
    // int code = atoi(response);
    // if (code == 230 || code == 232) {
    //     printf("User logged in\n");
    // } else if (code == 331 || code == 332 || code == 336) {
    //     printf("Username accepted, password required\n");
    // } else if (code == 421) {
    //     printf("Service not available, closing control connection\n");
    // } else if (code == 500 || code == 501 || code == 530) {
    //     printf("Invalid username or password\n");
    // }
}
