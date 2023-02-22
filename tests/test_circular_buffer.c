/*
** EPITECH PROJECT, 2022
** Repository-MyFTP
** File description:
** test_circular_buffer.c
*/

#include <criterion/criterion.h>
#include <criterion/redirect.h>
#include "../include/server.h"

Test(cb_init_function, basic) {
    circular_buffer cb;
    cb_init(&cb);

    cr_assert_eq(cb.read_index, 0, "Expected 0, but got %li\n", cb.read_index);
    cr_assert_eq(cb.write_index, 0, "Expected 0, but got %li\n",
    cb.write_index);
}

Test(is_cb_full_function, basic) {
    circular_buffer cb;
    cb_init(&cb);

    for (cb.write_index = 0; cb.write_index < BUFFER_SIZE; cb.write_index++) {
        cb.buffer[cb.write_index] = 'a';
    }
    cr_assert_eq(is_cb_full(&cb), true, "Expected true, but got %d\n",
    is_cb_full(&cb));
    cb.write_index = 0;
    cr_assert_eq(is_cb_full(&cb), false, "Expected true, but got %d\n",
    is_cb_full(&cb));
}

Test(cb_push_function, basic) {
    circular_buffer cb;
    cb_init(&cb);

    cb_push(&cb, "Hello World!");
    printf("write_index: %li\n", cb.write_index);
    cr_assert_eq(cb.buffer[cb.write_index - 1], '!', "Expected !, but got %c\n",
    cb.buffer[cb.write_index - 1]);
    cr_assert_eq(cb.buffer[cb.write_index - 2], 'd', "Expected d, but got %c\n",
    cb.buffer[cb.write_index - 2]);
    cr_assert_eq(cb.buffer[cb.write_index - 3], 'l', "Expected l, but got %c\n",
    cb.buffer[cb.write_index - 3]);
    cr_assert_eq(cb.buffer[cb.write_index - 4], 'r', "Expected r, but got %c\n",
    cb.buffer[cb.write_index - 4]);
    cr_assert_eq(cb.buffer[cb.write_index - 5], 'o', "Expected o, but got %c\n",
    cb.buffer[cb.write_index - 5]);
    cr_assert_eq(cb.buffer[cb.write_index - 6], 'W', "Expected W, but got %c\n",
    cb.buffer[cb.write_index - 6]);
    cr_assert_eq(cb.buffer[cb.write_index - 7], ' ', "Expected  , but got %c\n",
    cb.buffer[cb.write_index - 7]);
    cr_assert_eq(cb.buffer[cb.write_index - 8], 'o', "Expected o, but got %c\n",
    cb.buffer[cb.write_index - 8]);
    cr_assert_eq(cb.buffer[cb.write_index - 9], 'l', "Expected l, but got %c\n",
    cb.buffer[cb.write_index - 9]);
    cr_assert_eq(cb.buffer[cb.write_index - 10], 'l',
    "Expected l, but got %c\n", cb.buffer[cb.write_index - 10]);
    cr_assert_eq(cb.buffer[cb.write_index - 11], 'e',
    "Expected e, but got %c\n", cb.buffer[cb.write_index - 11]);
    cr_assert_eq(cb.buffer[cb.write_index - 12], 'H',
    "Expected H, but got %c\n", cb.buffer[cb.write_index - 12]);
}

Test(cb_pop_function, basic) {
    circular_buffer cb;
    cb_init(&cb);

    cb_push(&cb, "Hello World!");
    char* str = cb_pop_command(&cb);
    cr_assert_str_eq(str, "Hello World!", "Expected Hello World!, but got %s\n",
    str);

}
