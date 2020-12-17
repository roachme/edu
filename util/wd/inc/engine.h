#ifndef ENGINE_UNCLUDED
#define ENGINE_UNCLUDED
#define SIZE 100

struct point {
	char *name;
	char *dir;
};
struct bucket {
	size_t size;
	struct point *points[SIZE];
	size_t avail;
};

#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <stdlib.h>
#include <assert.h>
#include "engine.h"


struct bucket *wd_init(char *filename);
void wd_fillpnt(struct point *point, char *line);
int wd_chkdup(struct bucket *bucket, char *name);
int wd_add(struct bucket *bucket, char *name);
int wd_free(struct point *point);
int wd_rm(struct bucket *bucket, char *name);
int wd_save(struct bucket *bucket, char *filename);
int wd_list(char *filename);
int wd_clean(char *filename);

static int wd_show(struct bucket *bucket);


#endif