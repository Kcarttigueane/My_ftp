/*
** EPITECH PROJECT, 2022
** Repository-MyFTP
** File description:
** is_directory_accessible.c
*/

#include "../include/server.h"

bool is_directory_accessible(int control_socket, server_data_t* server_data,
char* new_path, bool is_data_transfer)
{
    if (!new_path) {
        perror("realpath");
        is_data_transfer ? send_resp(control_socket, FTP_REPLY_425) : send_resp(
        control_socket, FTP_REPLY_550);
        return false;
    }
    if (strncmp(new_path, server_data->initial_path,
        strlen(server_data->initial_path)) != 0) {
        is_data_transfer ? send_resp(control_socket, FTP_REPLY_425) :
        send_resp(control_socket, FTP_REPLY_550);
        free(new_path);
        return false;
    }
    return true;
}
