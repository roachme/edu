#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "engine.h"
#include <unistd.h>
#define DIR_SIZE 100

static char usage[] = 	"wd - warp directory\n"
						"wd [OPTION]... [POINT]...\n"
						"   -a add point\n"
						"   -r remove point\n"
						"   -l list points\n"
						"   -c clean up all point\n";
typedef enum OPT{
	OPT_ADD,
	OPT_RM,
	OPT_LIST,
	OPT_CLN,
	OPT_PNT,
	OPT_ERR
} OPT;

static int wd_show(struct bucket *bucket) {
	int i;
	for (i = 0; i < bucket->avail; i++)
		printf("%s:%s\n", bucket->points[i]->name, bucket->points[i]->dir);
}

OPT wd_getopt(char *opt) {
	if (strcmp(opt, "-a") == 0)
		return OPT_ADD;
	else if (strcmp(opt, "-r") == 0)
		return OPT_RM;
	else if (strcmp(opt, "-l") == 0)
		return OPT_LIST;
	else if (strcmp(opt, "-c") == 0)
		return OPT_CLN;
	else
		return OPT_ERR;
}

char *wd_getdir(struct bucket *bucket, char *name) {
	int avail = bucket->avail;
	for (int i = 0; i < avail; i++) {
		if (strcmp(bucket->points[i]->name, name) == 0) {
			return bucket->points[i]->dir;
		}
	}
	return NULL;
}


int main(int argc, char *argv[])
{
	char *filename = "/home/kali/.wreck";
	int opt;
	if (argc == 1) {
		printf("%s\n", usage);
		exit(1);
	}

	struct bucket *bucket = wd_init(filename);
	char *name = argv[2];
	char *dir;

	if ((opt = wd_getopt(argv[1])) == OPT_ERR) {
		if ((dir = wd_getdir(bucket, argv[1])) != NULL)
			printf("%s", dir);
		return 0;
	}

	switch(opt) {
	case OPT_ADD:
		if(wd_add(bucket, name) == 0) {
			wd_save(bucket, filename);
		}
		break;
	case OPT_RM:
		if (wd_rm(bucket, name) == 0)
			wd_save(bucket, filename);
			return 1;
	case OPT_LIST:
		wd_list(filename);
		return 1;
	case OPT_CLN:
		wd_clean(filename);
		return 1;
	}
}
