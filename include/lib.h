/*
** EPITECH PROJECT, 2023
** STEP-1
** File description:
** main.c
*/

#pragma once

    #include <stdio.h>
    #include <stdlib.h>
    #include <string.h>

size_t count_tokens(const char* str, const char* delimiter);
char** split_str(char* str, char* delimiter);

int get_size_word_array(char** array);
char* my_strcat(char* s1, char* s2);

// ! DEBUG functions:

void debug_word_array(char** word_array);

void debug_command(char* input_command);
