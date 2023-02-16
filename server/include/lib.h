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
