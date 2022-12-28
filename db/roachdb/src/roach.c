#include "roach.h"
#include "utils.h"
#include "disk.h"
#include "output.h"

#define COMMANDS_SIZE (sizeof (commands) / sizeof (commands[0]))

static const char *commands[] = {
  "create",
  "show",
  "add",
  "select",
  "delete",
  "import",
  "export",
  "exit"
};

static void (*dbcmds[COMMANDS_SIZE]) (void) = {
  db_create_table,
  db_show_table,
  db_add_entry,
  db_select_from_table,
  db_delete_entry,
  db_import_table,
  db_export_table,
  db_exit
};

static table_t table;


static void
usage (void)
{
  printf ("Usage: roachdb [OPTION]\n"
          "  create    - create a table\n"
          "  show      - show table definition\n"
          "  add       - add a new entry to table\n"
          "  select    - show specific columns in table\n"
          "  delete    - delete column from table\n"
          "  import    - save table content to disk\n"
          "  export    - download table content from disk to database"
          "  exit      - exit from db\n");
  exit (0);
}

void
db_create_table (void)
{
  char *buff;
  char *token = NULL;
  int width = 0;

  buff = get_input ("Table name: ");
  strcpy (table.name, buff);

  buff = get_input ("Table declaration: ");
  token = strtok (buff, DELIMITER_TITLE);
  while (token) {
    if (strcmp (token, "int") == 0) {
      token = strtok (NULL, DELIMITER_TITLE);
      value_array_add_title (&table.title, token, TYPE_INT);
    }
    else if (strcmp (token, "str") == 0) {
      token = strtok (NULL, DELIMITER_TITLE);
      value_array_add_title (&table.title, token, TYPE_STR);
    }
    token = strtok (NULL, DELIMITER_TITLE);
    ++width;
  }
  table.width = width;
}



void
db_show_table (void)
{
  output_table (&table);
}

void
db_add_entry (void)
{
  char *input = get_input ("Values: ");
  char *token = strtok (input, DELIMITER);
  int column_idx = 0;

  while (token) {
    value_array_add (&table.content[table.count], token,
                     table.title.values[column_idx].type);

    token = strtok (NULL, DELIMITER);
    ++column_idx;
  }

  ++table.count;
  free (input);
}

static int
table_lookpup (table_t *table, char *key, type_t *type)
{
  for (int i = 0; i < table->width; ++i) {
    if (strcmp (table->title.values[i].val_s, key) == 0) {
      *type =  table->title.values[i].type;
      return i;
    }
  }
  return -1;
}

void
db_select_from_table (void)
{
  char column_name[BUFFER_SIZE];
  type_t type;

  printf("Column name: ");
  fgets (column_name, BUFFER_SIZE, stdin);
  column_name[strcspn (column_name, "\n")] = '\0';

  int idx = table_lookpup (&table, column_name, &type);
  if (idx == -1) {
    db_warning ("no such column name");
    return ;
  }

  // show specified column in the intire table
  for (int i = 0; i < table.count; ++i) {
    switch (type) {
      case TYPE_INT:
        printf("%d\n", table.content[i].values[idx].val_i);
        break;
      case TYPE_STR:
        printf("%s\n", table.content[i].values[idx].val_s);
        break;
    }
  }
}

void
db_delete_entry (void)
{
  char *input = get_input ("Row index: ");
  int idx, idx_last = table.count - 1;

  if (!isnumber (input)) {
    db_error ("wrong formatted numeric value");
  }

  /* db table index starts at 1 not 0.  */
  idx = tonumber (input) - 1;

  if (idx < 0 || idx > table.count) {
    db_warning ("out of index");
    return ;
  }

  /* copy last row to the one you wanna delete
     and decrease table row count. */
  memcpy (&table.content[idx], &table.content[idx_last],
          sizeof (table.content[idx_last]));

  --table.count;
  free (input);
}

void
db_exit (void)
{
  exit (0);
}

void
db_import_table (void)
{
  if (disk_import_table (&table) != 0) {
    db_error ("could not export table data.");
  }
}

void
db_export_table (void)
{
  if (disk_export_table (&table) != 0) {
    db_error ("could not import table data.");
  }
}

void
db_error (const char *msg)
{
  fprintf(stderr, "err: db: %s\n", msg);
  exit (1);
}

void
db_warning (const char *msg)
{
  fprintf(stderr, "warning: db has no command '%s'\n", msg);
}


int
main (int argc, const char **argv)
{
  char *input;
  int handled;

  // handle options
  if (argc == 2) {
    if (strcmp (argv[1], "-h") == 0 ) {
      usage ();
      return 0;
    }
    else if (strcmp (argv[1], "-v") == 0 ) {
      printf("roachdb version 1.0\n");
      return 0;
    }
    else {
      fprintf(stderr, "roachdb: Unsipported option '%s'\n", argv[1]);
      return 1;
    }
  }

  // cli mode
  table_init (&table);
  while (true) {
    handled = false;
    input = get_input ("rdb> ");

    for (int i = 0; i < COMMANDS_SIZE; ++i) {
      if (strcmp (input, commands[i]) == 0) {
        dbcmds[i] ();
        handled = true;
        printf("%s: has been performed sucessfully\n",
               commands[i]);
      }
    }

    // wrong command was passed
    if (handled == false) {
      db_warning (input);
    }
    free (input);
  }
  return 0;
}
