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

void help_all_commands(int i, char** input_command);
void help_one_command(int i, char** input_command);
void help_command(int control_socket, char** input_command);

// ! PWD:

void pwd(client_t* clients, int control_socket, server_data_t* server_data);

// ! PASV:

void pasv(circular_buffer* cb, server_data_t* server_data, int control_socket,
client_t* clients);

// ! LIST:

void list(void);

// ! CWD:

void cwd_command(int control_socket, char** input_command, client_t* clients);

// ! CDUP:

void cdup(int control_socket, char** input_command, client_t* clients);

// ! DELE:

void dele(int control_socket, char** input_command);

// ! QUIT:

void quit(server_data_t* server_data, int i, char** command);

// ! PORT:

void port(void);

// ! USER:

void user(server_data_t* server_data, int i, char** command, client_t* clients);

// ! PASS:

void pass(server_data_t* server_data, int i, char** command, client_t* clients);

// ! NOOP:

void noop(int control_socket);

// ! RETR:

void retr(void);

// ! STOR:

void stor(void);
