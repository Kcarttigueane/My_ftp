/*
** EPITECH PROJECT, 2022
** Repository-MyFTP
** File description:
** signals.c
*/

#include "server.h"

void sigint_handler(int signal)
{
    printf("Received SIGINT signal. Shutting down server.\n");
    exit(EXIT_SUCCESS);
}

void sigterm_handler(int signal)
{
    printf("Received SIGTERM signal. Shutting down server.\n");
    exit(EXIT_SUCCESS);
}
