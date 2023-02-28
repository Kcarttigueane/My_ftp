/*
** EPITECH PROJECT, 2022
** server
** File description:
** path_error_handling.c
*/

#include "../include/server.h"

bool check_directory_exists(const char* path)
{
    if (access(path, F_OK) == FAILURE) {
        dprintf(2, "Directory %s does not exist", path);
        return false;
    }
    return true;
}

bool check_directory(const char* path)
{
    struct stat st;

    if (stat(path, &st) == FAILURE || !S_ISDIR(st.st_mode)) {
        dprintf(2, "Path %s is not a directory", path);
        return false;
    }
    return true;
}

bool check_directory_permissions(const char* path)
{
    if (access(path, R_OK | W_OK) == FAILURE) {
        dprintf(2, "Server does not have permission to access %s", path);
        return false;
    }
    return true;
}

int is_valid_path(const char* path)
{
    if (!check_directory_exists(path) || !check_directory(path)
        || !check_directory_permissions(path)) {
        return ERROR;
    }
    return SUCCESS;
}
