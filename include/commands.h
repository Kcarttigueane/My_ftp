/*
** EPITECH PROJECT, 2022
** Repositery-MyFTP
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

// void pwd(client_t *clients, int control_socket);

// ! PASV:

void pasv();

// ! LIST:

void list();

// ! CWD:


// ! CDUP:

void cdup();

// ! DELE:

void dele();

// ! QUIT:


// ! PORT:

void port();

// ! USER:

void user();

// ! PASS:

void pass();

// ! NOOP:

void noop(int control_socket);

// ! RETR:

void retr();

// ! STOR:

void stor();



#endif // COMMAND_H
