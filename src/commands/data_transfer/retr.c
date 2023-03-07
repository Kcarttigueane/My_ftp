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

void retr_cleanup(server_data_t* server_data, FILE* file, int data_socket_temp)
{
    fclose(file);
    close(data_socket_temp);
    close(server_data->data_socket_fd);
    server_data->data_socket_fd = FAILURE;
}

void retr(list_args_t* args)
{
    if (!is_logged(args->control_socket, args->clients)) return;
    if (get_size_word_array(args->input_command) != 2) {
        send_resp(args->control_socket, FTP_REPLY_425);
        return;
    }
    char *file_path = realpath(args->input_command[1], NULL);
    if (is_directory_accessible(args->control_socket, args->server_data,
    file_path, true) == false) {
        return;
    }
    FILE* file = open_file(args->input_command[1], args->control_socket,
    "425 %s: No such file or directory.\r\n");
    if (file == NULL) return;
    if (!is_data_con_establish(args->control_socket, args->server_data))
        return;
    int data_socket_temp = create_temp_socket(args->server_data, args->clients);
    args->server_data->data_mode = NO_MODE;
    send_file(data_socket_temp, file);
    dprintf(args->control_socket, "226 Transfer complete.\r\n");
    retr_cleanup(args->server_data, file, data_socket_temp);
}
