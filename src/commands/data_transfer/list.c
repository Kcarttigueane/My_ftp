/*
** EPITECH PROJECT, 2022
** Repository-MyFTP
** File description:
** list.c
*/

#include "../../../include/server.h"

void list_clean_up(server_data_t* server_data, list_args_t* args,
int data_sock_temp)
{
    dprintf(args->control_socket, FTP_REPLY_226);
    close(data_sock_temp);
    close(server_data->data_socket_fd);
    server_data->data_socket_fd = FAILURE;
}

void list_command_display(char* path_to_study, list_args_t* args)
{
    DIR* dir = opendir(path_to_study);
    struct dirent* ent;

    if (dir == NULL) {
        dprintf(args->control_socket, "550 Failed to open directory\r\n");
        return;
    }

    int data_sock_temp = create_temp_socket(args->server_data, args->clients);

    dprintf(args->control_socket, FTP_REPLY_150);

    while ((ent = readdir(dir)) != NULL)
        if (strlen(ent->d_name) > 2 && ent->d_name[0] != '.')
            dprintf(data_sock_temp, "%s\r\n", ent->d_name);
    closedir(dir);
    list_clean_up(args->server_data, args, data_sock_temp);
}

void list(list_args_t* args)
{
    if (!is_logged(args->control_socket, args->clients)) return;
    char* path_to_study = (get_size_word_array(args->input_command) == 2)
        ? realpath(args->input_command[1], NULL)
        : args->clients[args->control_socket - 4].current_path;
    if (is_directory_accessible(args->control_socket, args->server_data,
        path_to_study) == false) return;
    args->server_data->data_mode = NO_MODE;
    if (strncmp(path_to_study, args->server_data->initial_path,
        strlen(args->server_data->initial_path)) != 0) {
        dprintf(args->control_socket, FTP_REPLY_550);
        args->server_data->data_socket_fd = FAILURE;
        return;
    }
    if (!is_data_con_establish(args->control_socket, args->server_data))
        return;
    list_command_display(path_to_study, args);
}
