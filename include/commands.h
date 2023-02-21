/*
** EPITECH PROJECT, 2022
** Repository-MyFTP
** File description:
** commands.h
*/

#if !defined(COMMAND_H)
    #define COMMAND_H

    #include "server.h"

    #define COMMANDS \
        "HELP NOOP USER PASS CWD CDUP QUIT DELE PWD PASV PORT RETR STOR LIST"

// ! HELP :

void help_all_commands(int i, char** input_command);
void help_one_command(int i, char** input_command);
void help_command(int control_socket, char** input_command);

// ! PWD:

void pwd(client_t* clients, int control_socket, server_data_t* server_data);

// ! PASV:

void pasv();

// ! LIST:

void list();

// ! CWD:

// ! CDUP:

void cdup(int control_socket, char** input_command, client_t* clients);

// ! DELE:

void dele();

// ! QUIT:

void quit(server_data_t* server_data, int i, char** command);

// ! PORT:

void port();

// ! USER:

void user(server_data_t* server_data, int i, char** command, client_t* clients);

// ! PASS:

void pass(server_data_t* server_data, int i, char** command, client_t* clients);

// ! NOOP:

void noop(int control_socket);

// ! RETR:

void retr();

// ! STOR:

void stor();

#endif  // COMMAND_H
