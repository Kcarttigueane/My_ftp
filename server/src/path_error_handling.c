/*
** EPITECH PROJECT, 2022
** server
** File description:
** path_error_handling.c
*/

#include "server.h"

void is_valid_path(const char *path)
{
    struct stat st;
    char msg[200];

    // Check if the directory exists
    if (access(path, F_OK) == FAILURE) {
        sprintf(msg, "Directory %s does not exist", path);
        handle_error(msg);
    }

    // Check if the path is a directory
    if (stat(path, &st) == FAILURE || !S_ISDIR(st.st_mode)) {
        sprintf(msg, "%s is not a directory", path);
        handle_error(msg);
    }

    // Check if the server has permission to access the directory
    if (access(path, R_OK | W_OK) == FAILURE) {
        sprintf(msg, "Server does not have permission to access %s", path);
        handle_error(msg);
    }

    // Limit the access of the server to the directory
    // if (chroot(path) == FAILURE) {

    //     fprintf(stderr, "Failed to limit server access to %s\n", path);
    //     return 0;
    // }
}
