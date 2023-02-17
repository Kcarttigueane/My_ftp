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

// ! LIB functions:

size_t count_tokens(const char* str, const char* delimiter);
char** split_str(char* str, char* delimiter);

// ! DEBUG functions:

void debug_word_array(char** word_array);
