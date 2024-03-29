/*
** EPITECH PROJECT, 2022
** Repository-MyFTP
** File description:
** myFTP_loop.c
*/

#include "../include/server.h"

#include <ctype.h>
#include <stdbool.h>
#include <string.h>

bool has_one_non_whitespace_char(const char* str)
{
    for (size_t i = 0; i < strlen(str); i++)
        if (!isspace(str[i]) && str[i] != '\r' && str[i] != '\n')
            return true;
    return false;
}

void read_input(int i, server_data_t* server_data, circular_buffer* cb,
client_t* clients)
{
    char buffer[BUFFER_SIZE] = {0};
    server_data->read_input_len = read(i, buffer, BUFFER_SIZE);
    buffer[server_data->read_input_len] = '\0';
    if (!has_one_non_whitespace_char(buffer)) {
        send_resp(i, FTP_REPLY_500);
        return;
    }
    if (server_data->read_input_len == 0) {
        FD_CLR(i, &server_data->fds);
        close(i);
        printf("Close client: %i\n", i);
    } else {
        cb_push(cb, buffer);
        printf("Client %i said: %s\n", i, buffer);
        parse_command(cb, server_data, i, clients);
    }
}

void file_descriptors_loop(server_data_t* server_data, client_t* clients,
circular_buffer* cb)
{
    for (int i = 0; i < (server_data->fd_max + 1); i++) {
        if (FD_ISSET(i, &server_data->copy_fds)) {
            (i == server_data->server_socket_fd)
                ? handle_new_client_connection(server_data, clients)
                : read_input(i, server_data, cb, clients);
        }
    }
}

void my_ftp_loop(server_data_t* server_data, client_t* clients)
{
    circular_buffer cb = {0};

    cb_init(&cb);
    printf("Server is listening on port %d\n", server_data->server_socket_fd);

    while (true) {
        server_data->copy_fds = server_data->fds;

        if ((server_data->fd_num =
        select(server_data->fd_max + 1, &server_data->copy_fds, 0, 0,
        &server_data->timeout)) == FAILURE) {
            break;
        }
        if (server_data->fd_num == STDIN_FILENO)
            continue;
        file_descriptors_loop(server_data, clients, &cb);
    }
}
