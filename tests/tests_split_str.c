/*
** EPITECH PROJECT, 2022
** Repository-MyFTP
** File description:
** tests_split_str.c
*/

#include <criterion/criterion.h>
#include <criterion/redirect.h>
#include "../include/lib.h"

Test(count_tokens_function, basic) {
    const char* str = "hello world";
    const char* delimiter = " ";
    size_t result = count_tokens(str, delimiter);
    cr_assert_eq(result, 2, "Expected 2 tokens, but got %lu", result);
}

Test(count_tokens_function, null_input) {
    size_t result = count_tokens(NULL, NULL);
    cr_assert_eq(result, 0, "Expected 0 tokens, but got %lu", result);
}

Test(split_str_function, basic) {
    char* str = "hello world";
    char* delimiter = " ";
    char** words = split_str(str, delimiter);
    cr_assert_not_null(words, "Expected non-null result");
    cr_assert_eq(strcmp(words[0], "hello"), 0, "Unexpected first token");
    cr_assert_eq(strcmp(words[1], "world"), 0, "Unexpected second token");
    cr_assert_null(words[2], "Expected null terminator");
    free(words[0]);
    free(words[1]);
    free(words);
}

Test(split_str_function, null_input) {
    char** words = split_str(NULL, NULL);
    cr_assert_null(words, "Expected null result");
}
