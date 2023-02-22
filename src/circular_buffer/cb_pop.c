/*
** EPITECH PROJECT, 2022
** Repository-MyFTP
** File description:
** cb_pop.c
*/

#include "../../include/server.h"

int find_crlf_index(circular_buffer* cb)
{
    char* position = strstr(cb->buffer + cb->read_index, CRLF);

    if (position != NULL) {
        return (int)(position - cb->buffer);
    } else {
        position = strstr(cb->buffer, CRLF);
        if (position == NULL)
            return FAILURE;
        return (int)(position - cb->buffer);
    }
}

size_t get_nb_char_to_copy(circular_buffer* cb, int CRLF_index)
{
    size_t nb_char_to_copy = 0;
    for (size_t i = cb->read_index; i != (size_t)CRLF_index; i++) {
        if (i >= BUFFER_SIZE)
            i = 0;
        nb_char_to_copy++;
    }
    return nb_char_to_copy;
}

char* copy_chars(circular_buffer* cb, size_t nb_char_to_copy)
{
    char* command = malloc(sizeof(char) * (nb_char_to_copy + 1));
    for (size_t i = 0; i < (size_t)nb_char_to_copy; i++) {
        if (cb->read_index >= BUFFER_SIZE)
            cb->read_index = 0;
        command[i] = cb->buffer[cb->read_index];
        cb->read_index++;
    }
    command[nb_char_to_copy] = '\0';
    return command;
}

char** cb_pop_command(circular_buffer* cb)
{
    int CRLF_index = find_crlf_index(cb);

    if (CRLF_index == FAILURE)
        return NULL;

    size_t nb_char_to_copy = get_nb_char_to_copy(cb, CRLF_index);

    if (nb_char_to_copy == 0)
        return NULL;

    char* command = copy_chars(cb, nb_char_to_copy);
    if (!command)
        return NULL;

    cb->read_index += 2;

    char** command_array = split_str(command, " ");
    if (!command_array)
        return NULL;
    return command_array;
};
