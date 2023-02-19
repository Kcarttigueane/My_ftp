/*
** EPITECH PROJECT, 2022
** Repositery-MyFTP
** File description:
** commands.h
*/

#if !defined(COMMAND_H)
#define COMMAND_H

#include "server.h"

// ! HELP :

void help_all_commands(int i, char** input_command);
void help_one_command(int i, char** input_command);

// ! PWD:

void pwd();

// ! PASV:

void pasv();

// ! LIST:

void list();

// ! CWD:

void cwd();

// ! CDUP:

void cdup();

// ! DELE:

void dele();

// ! QUIT:

void quit(server_data_t* server_data, int i, char** command);

// ! PORT:

void port();

// ! USER:

void user();

// ! PASS:

void pass();

// ! NOOP:

void noop(int ontrol_socket);

// ! RETR:

void retr();

// ! STOR:

void stor();



#endif // COMMAND_H
