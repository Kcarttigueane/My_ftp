/*
** EPITECH PROJECT, 2022
** server
** File description:
** path_error_handling.c
*/

#include "../include/server.h"

void check_directory_exists(const char* path)
{
    if (access(path, F_OK) == FAILURE) {
        char msg[200];
        sprintf(msg, "Directory %s does not exist", path);
        handle_error(msg);
    }
}

void check_directory(const char* path)
{
    struct stat st;
    char msg[200];

    if (stat(path, &st) == FAILURE || !S_ISDIR(st.st_mode)) {
        sprintf(msg, "%s is not a directory", path);
        handle_error(msg);
    }
}

void check_directory_permissions(const char* path)
{
    if (access(path, R_OK | W_OK) == FAILURE) {
        char msg[200];
        sprintf(msg, "Server does not have permission to access %s", path);
        handle_error(msg);
    }
}

void is_valid_path(const char* path)
{
    check_directory_exists(path);
    check_directory(path);
    check_directory_permissions(path);
}
