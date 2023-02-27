/*
** EPITECH PROJECT, 2022
** Repository-MyFTP
** File description:
** store.c
*/

#include "../../../include/server.h"

void stor_file(int data_socket_temp, FILE* file)
{
    char buffer[BUFFER_SIZE];
    int bytes_received;

    bytes_received = read(data_socket_temp, buffer, BUFFER_SIZE);
    if (bytes_received < 0) {
        handle_error("stor: read data socket");
        return;
    }
    if (fwrite(buffer, 1, bytes_received, file) < (size_t)bytes_received) {
        handle_error("fwrite failed in stor");
        return;
    }
}

void stor_cleanup(server_data_t* server_data, FILE* file, int data_socket_temp,
va_list args)
{
    fclose(file);
    close(data_socket_temp);
    close(server_data->data_socket_fd);
    server_data->data_socket_fd = FAILURE;
    va_end(args);
}

void stor(int control_socket, ...)
{
    va_list args;
    va_start(args, control_socket);
    client_t* clients = get_nth_argument(1, args);
    server_data_t* server_data = get_nth_argument(0, args);
    char** commands = get_nth_argument(2, args);
    if (!commands[1]) {
        send_resp(control_socket, FTP_REPLY_501);
        return;
    }
    if (!is_logged(control_socket, clients, &args)) return;
    if (!is_data_con_establish(control_socket, server_data)) return;
    int data_socket_temp = create_temp_socket(server_data);
    FILE* file = fopen(commands[1], "w");
    if (!file) return;
    dprintf(control_socket, FTP_REPLY_150);
    stor_file(data_socket_temp, file);
    dprintf(control_socket, FTP_REPLY_226);
    stor_cleanup(server_data, file, data_socket_temp, args);
}
