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
void help_command(list_args_t* args);

// ! PWD:

void pwd(list_args_t* args);

// ! PASV:

void pasv(list_args_t* args);

// ! LIST:

void list(list_args_t* args);

// ! CWD:

void cwd_command(list_args_t* args);

// ! CDUP:

void cdup(list_args_t* args);

// ! DELE:

void dele(list_args_t* args);

// ! QUIT:

void quit(list_args_t* args);

// ! PORT:

void port(list_args_t* args);

// ! USER:

bool test_user_conditions(client_t* clients, char** command,
int control_socket);
void user(list_args_t* args);

// ! PASS:

bool test_pass_conditions(client_t* clients, int control_socket,
char** command);
void pass(list_args_t* args);

// ! NOOP:

void noop(list_args_t* args);

// ! RETR:

void retr(list_args_t* args);

// ! STOR:

void stor(list_args_t* args);
