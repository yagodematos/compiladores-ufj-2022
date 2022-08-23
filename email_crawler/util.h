#ifndef UTIL_H
#define UTIL_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef enum { q1, q2, q3, q4 } states;

void email(char c);

size_t process_data(char *data, size_t a, size_t n, void* b);

#endif
