#include <stdio.h>
#include <ctype.h>

#include "utils.h"

char *cut_padding (char *str)
{
  char *beg = str;
  char *end = str + strlen (str) - 1;

  // trim whitespaces in the beginning
  while (*beg && *beg == ' ')
    ++beg;

  // trim whitespaces and newline in the end
  end = str + strlen (str) - 1;
  while (end > beg && (*end == ' ' || *end == '\n')) {
    --end;
  }
  *(end+1) = '\0';
  return beg;
}

int isnumber (char *num)
{
  char *ptr = cut_padding (num);

  if (*ptr == '-') {
    ++ptr;
  }

  while (*ptr) {
    if (!isdigit (*ptr)) {
      return 0;
    }
    ++ptr;
  }
  return 1;
}

int isstring (char *str)
{
  char *ptr = cut_padding (str);

  if (*ptr == '"')
    ++ptr;
  else
    return 0;

  while (*ptr && *ptr != '"')
    ++ptr;

  if (*ptr == '"')
    return 1;
  return 0;
}

int tonumber (char *num)
{
  int sign = 1;
  char *ptr = cut_padding (num);
  int res = 0;

  if (*ptr == '-') {
    sign = -1;
    ++ptr;
  }

  while (*ptr) {
    res = 10 * res + (*ptr - '0');
    ++ptr;
  }
  return sign * res;
}


int
max (int a, int b)
{
  return a > b ? a : b;
}

int
number_length (int num)
{
  int length = 0;

  while (num) {
    num /= 10;
    ++length;
  }
  return length;
}

void
show_array (int *arr, int size)
{
  for (int i = 0; i < size; ++i) {
    printf("%d\n", arr[i]);
  }
}

char
*get_input (const char *prompt)
{
  char buff[BUFFER_SIZE];
  char *ptr = buff;

  printf("%s", prompt);
  fgets (buff, BUFFER_SIZE, stdin);

  ptr = cut_padding (buff);
  return strdup (ptr);
}

void
value_array_init (value_array_t *arr)
{
  arr->count = 0;
  arr->size  = COLUMN_SIZE;
}

void
value_array_add_title (value_array_t *arr, char *value, type_t type)
{
  if (arr->size <= arr->count + 1) {
    db_error ("table width is over");
  }
  arr->values[arr->count].type = type;
  strcpy (arr->values[arr->count].val_s, value);

  ++arr->count;
}

int
value_array_add (value_array_t *row, char *value, type_t type)
{
  switch (type) {
    case TYPE_INT:
      if (!isnumber (value)) {
        db_error ("wrong formatted numeric value");
      }
      row->values[row->count].val_i = tonumber (value);
      row->values[row->count].type = TYPE_INT;
      break;
    case TYPE_STR:
      if (!isstring (value)) {
        db_error ("wrong formatted string value");
      }
      value = cut_padding (value);
      strcpy (row->values[row->count].val_s, value);
      row->values[row->count].type = TYPE_STR;
      break;
    default:
      db_error ("unsupported data type");
  }

  ++row->count; // increment COLUMN index
}

void
table_init (table_t *table)
{
  table->width = 0;
  table->count = 0;
  table->size  = TABLE_SIZE;

  value_array_init (&table->title);

  for (int i = 0; i < TABLE_SIZE; ++i) {
    value_array_init (&table->content[i]);
  }
}
