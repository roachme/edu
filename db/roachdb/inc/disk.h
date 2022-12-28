#ifndef _RDB_DISK_H
#define _RDB_DISK_H

// FIX: move all of it to table.h
#include "roach.h"



int disk_export_table (table_t *table);
int disk_import_table (table_t *table);

#endif
