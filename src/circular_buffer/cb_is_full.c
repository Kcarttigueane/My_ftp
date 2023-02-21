/*
** EPITECH PROJECT, 2022
** Repository-MyFTP
** File description:
** cb_is_full.c
*/

#include "../../include/circular_buffer.h"

bool is_cb_full(circular_buffer* cb)
{
    return ((cb->write_index + 1) >= BUFFER_SIZE);
}
