#include "roach.h"
#include "utils.h"
#include "output.h"

static int array_maxwidth[COLUMN_SIZE] = {0};
static const int SPACE_BETWEEN = 4;

static void
show_title (value_array_t *title)
{
  char buff[BUFFER_SIZE];

  for (int i = 0; i < title->count; ++i) {
    sprintf (buff, "%s %s",
           title->values[i].type == TYPE_INT ? "int" : "str", 
           title->values[i].val_s);
    printf("%-*s", array_maxwidth[i] + SPACE_BETWEEN, buff);
  }
  printf("\n");
}

static void
show_content (value_array_t *content, int count, int width)
{
  char buff[BUFFER_SIZE];

  for (int i = 0; i < count; ++i) {

    for (int j = 0; j < width; ++j) {
      switch (content[i].values[j].type) {
        case TYPE_INT:
          printf("%-*d", array_maxwidth[j] + SPACE_BETWEEN, content[i].values[j].val_i);
          break;
        case TYPE_STR:
          printf("%-*s", array_maxwidth[j] + SPACE_BETWEEN, content[i].values[j].val_s);
          break;
        default:
          db_error ("wrong data type");
      }
    }
    printf("\n");
  }
}

void
output_table (table_t *table)
{
  int maxval;
  int length;
  type_t type;


  // calculate padding format
  for (int i = 0; i < table->width; ++i) {
    maxval = 0;

    // title
    type = table->title.values[i].type;
    length = type == TYPE_INT
             ? number_length (table->title.values[i].val_i)
             : strlen (table->title.values[i].val_s);

    // include the length of data types and space.
    switch (type) {
      case TYPE_INT:
        length += 3 + 1; // data type (int) + space
        break;
      case TYPE_STR:
        length += 3 + 1; // data type (str) + space
        break;
      default:
        db_error ("wrong data type");
    }
    maxval = max (maxval, length);

    // content
    for (int j = 0; j < table->count; ++j) {
      length = table->content[j].values[i].type == TYPE_INT
               ? number_length (table->content[j].values[i].val_i)
               : strlen (table->content[j].values[i].val_s);
      maxval = max (maxval, length);
    }
    array_maxwidth[i] = maxval;
  }

  printf("Table: %s\n", table->name);
  show_title (&table->title);
  show_content (table->content, table->count, table->width);
}
