/*
** EPITECH PROJECT, 2022
** Repository-MyFTP
** File description:
** retr.c
*/

#include "../../../include/server.h"

void send_file(int data_socket, FILE* file)
{
    struct stat file_stat;

    if (fstat(fileno(file), &file_stat) < 0)
        handle_error("fstat");

    int file_fd = fileno(file);
    char buffer[BUFFER_SIZE];
    int bytes_read;

    while ((bytes_read = read(file_fd, buffer, BUFFER_SIZE)) > 0)
        if (write(data_socket, buffer, bytes_read) < 0)
            handle_error("write");
}

void retr_cleanup(server_data_t* server_data,
FILE* file, int data_socket_temp, va_list args)
{
    fclose(file);
    close(data_socket_temp);
    close(server_data->data_socket_fd);
    server_data->data_socket_fd = FAILURE;
    va_end(args);
}

void retr(int control_socket, ...)
{
    va_list args;
    va_start(args, control_socket);
    client_t* clients = get_nth_argument(1, args);
    server_data_t* server_data = get_nth_argument(0, args);
    char** commands = get_nth_argument(2, args);
    if (!is_logged(control_socket, clients, &args)) return;
    if (!commands[1]) {
        send_resp(control_socket, FTP_REPLY_501);
        return;
    }
    printf("commands[1] = %s\n", commands[1]);
    FILE* file = open_file(commands[1], control_socket,
        "550 %s: No such file or directory.\r\n");
    if (file == NULL) return;
    if (!is_data_con_establish(control_socket, server_data)) return;
    int data_socket_temp = create_temp_socket(server_data);
    send_file(data_socket_temp, file);
    dprintf(control_socket, "226 Transfer complete.\r\n");
    retr_cleanup(server_data, file, data_socket_temp, args);
}
