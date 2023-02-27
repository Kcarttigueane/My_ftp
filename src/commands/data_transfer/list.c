/*
** EPITECH PROJECT, 2022
** Repository-MyFTP
** File description:
** list.c
*/

#include "../../../include/server.h"

void list_command_display(char* path_to_study, int data_sock_temp)
{
    DIR* dir = opendir(path_to_study);
    struct dirent* ent;

    if (dir == NULL) {
        dprintf(data_sock_temp, "550 Failed to open directory\r\n");
        return;
    }

    while ((ent = readdir(dir)) != NULL)
        if (strlen(ent->d_name) > 2 && ent->d_name[0] != '.')
            dprintf(data_sock_temp, "%s\r\n", ent->d_name);
    closedir(dir);
}

void list(int control_socket, ...)
{
    va_list args;
    va_start(args, control_socket);
    server_data_t* server_data = get_nth_argument(0, args);
    char** input_command = get_nth_argument(2, args);
    client_t* clients = get_nth_argument(1, args);

    if (!is_logged(control_socket, clients, &args)) return;
    if (!is_data_con_establish(control_socket, server_data)) return;

    int data_sock_temp = create_temp_socket(server_data);
    dprintf(control_socket, FTP_REPLY_150);
    char* path_to_study = (get_size_word_array(input_command) == 2)
    ? input_command[1]
    : clients[control_socket - 4].current_path;
    list_command_display(path_to_study, data_sock_temp);
    dprintf(data_sock_temp, FTP_REPLY_226);
    close(data_sock_temp);
    close(server_data->data_socket_fd);
    server_data->data_socket_fd = FAILURE;
}
