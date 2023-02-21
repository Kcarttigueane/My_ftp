/*
** EPITECH PROJECT, 2022
** Repository-MyFTP
** File description:
** circular_buffet.c
*/

#include "server.h"

void cb_init(circular_buffer* cb)
{
    for (size_t i = 0; i < BUFFER_SIZE; i++)
        cb->buffer[i] = '\0';
    cb->read_index = 0;
    cb->write_index = 0;
}

bool is_cb_full(circular_buffer* cb)
{
    return ((cb->write_index + 1) >= BUFFER_SIZE);
}

void cb_push(circular_buffer* cb, char* input_command)
{
    printf("read index: %li\n", cb->read_index);
    printf("write index: %li\n", cb->write_index);
    for (size_t i = 0; i < strlen(input_command); i++) {
        if (is_cb_full(cb))
            cb->write_index = 0;
        cb->buffer[cb->write_index] = input_command[i];
        cb->write_index += 1;
    }
    // debug_command(cb->buffer);
}

int find_CRLF_index(circular_buffer* cb)
{
    char *position = strstr(cb->buffer + cb->read_index, "\r\n");

    if (position == NULL)
        return FAILURE;

    position = strstr(cb->buffer, "\r\n");

    if (position == NULL)
        return FAILURE;

    printf("position: %li\n", position - cb->buffer);
    return position - cb->buffer;
}

char** cb_pop_command(circular_buffer* cb)
{
    int CRLF_index = find_CRLF_index(cb);

    if (CRLF_index == FAILURE) {
        printf("CRLF not found\n");
        return NULL;
    }

    size_t nb_char_to_copy = 0;

    for (size_t i = cb->read_index; nb_char_to_copy != (size_t)CRLF_index; i++) {
        if (i >= BUFFER_SIZE)
            i = 0;
        nb_char_to_copy++;
    }
    printf("nb_char_to_copy: %li\n", nb_char_to_copy);

    if (nb_char_to_copy == 0)
        return NULL;

    char* command = malloc(sizeof(char) * (nb_char_to_copy + 1));

    for (size_t i = 0; i < (size_t)nb_char_to_copy; i++) {
        if (cb->read_index >= BUFFER_SIZE)
            cb->read_index = 0;
        command[i] = cb->buffer[cb->read_index++];
    }
    printf("read_index ==> %li\n", cb->read_index);
    command[nb_char_to_copy] = '\0';
    cb->read_index += 2;

    char** command_array = split_str(command, " ");

    if (!command_array)
        return NULL;

    return command_array;
};

void print_cb(circular_buffer* cb)
{
    for (size_t i = 0; i < BUFFER_SIZE; i++)
        write(1, &cb->buffer[i], 1);
    printf("\n");
}
