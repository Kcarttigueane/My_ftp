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

void pwd(int control_socket);

#endif // COMMAND_H
