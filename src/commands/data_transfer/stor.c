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

void stor_cleanup(server_data_t* server_data, FILE* file, int data_socket_temp)
{
    fclose(file);
    close(data_socket_temp);
    close(server_data->data_socket_fd);
    server_data->data_socket_fd = FAILURE;
}

void stor(list_args_t* args)
{
    if (!is_logged(args->control_socket, args->clients))
        return;
    if (get_size_word_array(args->input_command) != 2) {
        send_resp(args->control_socket, FTP_REPLY_550);
        return;
    }
    if (!is_data_con_establish(args->control_socket, args->server_data))
        return;
    int data_socket_temp = create_temp_socket(args->server_data, args->clients);
    FILE* file = fopen(args->input_command[1], "w");
    if (!file)
        return;
    dprintf(args->control_socket, FTP_REPLY_150);
    stor_file(data_socket_temp, file);
    dprintf(args->control_socket, FTP_REPLY_226);
    stor_cleanup(args->server_data, file, data_socket_temp);
}
