#include "ast.h"


struct node *generate_ast(Tokens *toks)
{
	// init
	tokens = toks;
	token  = &tokens->token[0];
	pos    = 0;


	struct node **node = malloc(sizeof(struct node*));

	int i = 0;
	while (pos < tokens->size)
	{
		node[i] = malloc(sizeof(struct node));
		node[i] = macrostruct();
		i++; 
	}

	int count = i;
	for (int i = 0; i < count; ++i)
		proc_view(node[i]);

	printf("[!]  Ruturn NULL value: generate_ast\n");
	return (NULL);
}





int lookup(char *value, int shift)
{
	if (!strcmp(tokens->token[pos + shift].value, value))
		return 1;
	return 0;
}

int advance(TokenType type)
{
	if (token->type != type)
	{
		fprintf(stderr, "[!] ERROR advance: incorrect token %s\n", token->value);
		exit(0);
	}
	token = &tokens->token[++pos];
	return 1;
}

char *getvalue(TokenType type)
{
	char *value = strdup(token->value);
	advance(type);
	return value;
}

void tokv()
{
	printf("%s\n", token->value);
}
