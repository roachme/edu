#include <stdio.h>

#include "disk.h"
//#include "table.h"
//#include "db_error.h"


#define DBFILE "data/dbfile.txt"

int
disk_export_table (table_t *table)
{
  FILE *dbfile = fopen (DBFILE, "wb");
  if (dbfile == NULL) {
    return 1;
  }

  fwrite (table, sizeof (table_t), 1, dbfile);
  fclose (dbfile);
  return 0;
}


int
disk_import_table (table_t *table)
{
  int i = 0;
  FILE *dbfile = fopen (DBFILE, "rb");
  if (dbfile == NULL) {
    return 1;
  }

  fread (table, sizeof (table_t), 1, dbfile);
  fclose (dbfile);
  return 0;
}
