#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>

#include "lexer.h"
#include "ast.h"

char *readsrc(char *filename)
{
	FILE *file;
	char *src;
	int size;

	file = fopen(filename, "r");
	if (file == NULL)
	{
		fprintf(stderr, "[!] ERROR: cannot open file %s\n", filename);
		exit(0);
	}

	fseek(file, 0, SEEK_END);
	size = ftell(file);
	fseek(file, 0, SEEK_SET);

	src = malloc(size);
	fread(src, 1, size, file);

	if (src == NULL)
	{
		fprintf(stderr, "[!] ERROR: cannot read file %s\n", filename);
		exit(0);
	}
	return src;
}






int main()
{
	char *src = readsrc("exm/code.s");

	Tokens *tokens = lexer(src);


	struct node *ast = generate_ast(tokens);
	if (ast == NULL) {
		printf("[*] Done\n");
	}


	return (0);
}
