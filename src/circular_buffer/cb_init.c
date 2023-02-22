/*
** EPITECH PROJECT, 2022
** Repository-MyFTP
** File description:
** cb_init.c
*/

#include "../../include/server.h"

void cb_init(circular_buffer* cb)
{
    for (size_t i = 0; i < BUFFER_SIZE; i++)
        cb->buffer[i] = '\0';
    cb->read_index = 0;
    cb->write_index = 0;
}
