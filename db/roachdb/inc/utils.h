#ifndef _RDB_UTILS_H
#define _RDB_UTILS_H

#include "roach.h"


int isnumber (char *num);
int isstring (char *str);
int tonumber (char *num);
int max (int a, int b);
int number_length (int num);
void show_array (int *arr, int size);


char *get_input (const char *prompt);
void value_array_init (value_array_t *arr);
void value_array_add_title (value_array_t *arr, char *value, type_t type);
int  value_array_add (value_array_t *row, char *value, type_t type);
void table_init (table_t *table);
#endif
