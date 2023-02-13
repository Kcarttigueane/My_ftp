/*
** EPITECH PROJECT, 2023
** STEP-1
** File description:
** main.c
*/

#pragma once

#include <sys/select.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <sys/un.h>

#include <netinet/in.h>

#include <arpa/inet.h>
#include <netdb.h>

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "unistd.h"

#include <errno.h>

// Error Status Codes :

#define ERROR 84
#define SUCCESS 0
#define FAILURE -1

// Boolean :

#define FALSE 0
#define TRUE 1

#define QUEUE_LEN 5
#define BUFFER_SIZE 1024

#define SERVER_USAGE \
    "USAGE: ./myftp port path\n\
\tport is the port number on which the server socket listens\n\
\tpath is the path to the home directory for the Anonymous user\n"

#define handle_error(msg)   \
    do {                    \
        perror(msg);        \
        exit(EXIT_FAILURE); \
    } while (0)
