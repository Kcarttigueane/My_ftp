/*
** EPITECH PROJECT, 2022
** Repository-MyFTP
** File description:
** commands.h
*/

#pragma once

    #include "server.h"
    #include "circular_buffer.h"

    #define COMMANDS \
        "HELP NOOP USER PASS CWD CDUP QUIT DELE PWD \
        PASV PORT RETR STOR LIST\r\n"

// ! HELP :

void help_all_commands(int control_socket);
void help_one_command(int control_socket, char ** input_commands);
void help_command(int control_socket, ...);

// ! PWD:

void pwd(int control_socket, ...);

// ! PASV:

void pasv(circular_buffer* cb, server_data_t* server_data,
int control_socket, client_t* clients);

// ! LIST:

void list(void);

// ! CWD:

void cwd_command(int control_socket, ...);

// ! CDUP:

void cdup(int control_socket, ...);

// ! DELE:

void dele(int control_socket, ...);

// ! QUIT:

void quit(int control_socket, ...);

// ! PORT:

void port(void);

// ! USER:

void user(int control_socket, ...);

// ! PASS:

void pass(int control_socket, ...);

// ! NOOP:

void noop(int control_socket, ...);

// ! RETR:

void retr(void);

// ! STOR:

void stor(void);
