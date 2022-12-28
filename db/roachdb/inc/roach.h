#ifndef _roach_h
#define _roach_h

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>
#include <stdbool.h>
#include <ctype.h>


#define BUFFER_SIZE   256
#define DELIMITER     ", "

#define COLUMN_SIZE   10
#define TABLE_SIZE    20


typedef enum {
  TYPE_INT,
  TYPE_STR
} type_t;

typedef struct {
  type_t type;
  union {
    int val_i;
    char val_s[BUFFER_SIZE];
  };
} value_t;

typedef struct {
  size_t count;
  size_t size;
  value_t values[COLUMN_SIZE];
} value_array_t;


typedef struct {
  char name[BUFFER_SIZE];

  // table definitions (title)
  value_array_t title; // 1-D array

  // content (actual data)
  value_array_t content[TABLE_SIZE]; // 2-D array

  int count;
  int size;
  int width;
} table_t;



void db_create_table (void);
void db_show_table (void);
void db_add_entry (void);
void db_select_from_table (void);
void db_delete_entry (void);
void db_import_table (void);
void db_export_table (void);
void db_exit (void);

void db_error (const char *msg);
void db_warning (const char *msg);
#endif
