/*
** EPITECH PROJECT, 2022
** Repositery-MyFTP
** File description:
** signals.c
*/

#include "server.h"

void sigint_handler(int signal)
{
    printf("Received SIGINT signal. Shutting down server.\n");
    // perform any cleanup or resource release here
    exit(0);
}

void sigterm_handler(int signal)
{
    printf("Received SIGTERM signal. Shutting down server.\n");
    // perform any cleanup or resource release here
    exit(0);
}
