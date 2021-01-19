#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>

#include "lexer.h"

Tokens *tokens;
Token *token;
int pos;

static int i;


Tokens *lexer(char *src)
{
	tokens = malloc(sizeof(Tokens));
	tokens->token  = malloc(100 * sizeof(Token));
	tokens->pos	 = 0;
	tokens->size   = 100;
	token = &tokens->token[0];

	int leng;
	int line = 1;

	Tokens *tokens = make_lexer();
	leng   = strlen(src);

	for (i = 0; i < leng; i++) 
	{
		if (tokens->size < pos + 1)
		{
			tokens->size *= 2;
			tokens->token = realloc(tokens->token, tokens->size * sizeof(Token));
		}

		// eleminate non-printable symbols
		if (src[i] != 10 && (src[i] < 33 || src[i] > 128))
			continue;

		if (src[i] == '\n')
		{
			line++;
			continue;
		}

		if (src[i] == '#')
		{
			line += skip_comments(src);
			continue;
		}

		token = &tokens->token[pos];
		token->line = line;

		switch (src[i]) 
		{

		// string
		case '\"':
			//token_string(token->value, src, &i);
			token->type = T_STRING;
			break;


		// char
		case '\'':
			//token_char(token->value, src, &i);
			token->type = T_STRING;
			break;


		// math signs
		case '+':
			token->value = strdup("+");
			token->type = T_PLUS;
			break;

		case '-':
			token->value = strdup("-");
			token->type = T_MINUS;
			break;

		case '*':
			token->value = strdup("*");
			token->type = T_MUL;
			break;

		case '/':
			token->value = strdup("/");
			token->type = T_DIV;
			break;


		case '<':
			if (src[i+1] == '=')
			{
				token->value = strdup("<=");
				token->type = T_LEQ;
				i++;
			}
			else
			{
				token->value = strdup("<");
				token->type = T_LESSER;
			}
			break;

		case '>':
			if (src[i+1] == '=')
			{
				token->value = strdup("<=");
				token->type = T_GEQ;
				i++;
			}
			else
			{
				token->value = strdup("<");
				token->type = T_GRATTER;
			}
			break;

		case '=':
			if (src[i+1] == '=')
			{
				token->value = strdup("==");
				token->type = T_EQ;
				i++;
			}
			else
			{
				token->value = strdup("=");
				token->type = T_ASSIGN;
			}
			break;

		case '!':
			if (src[i+1] == '=')
			{
				token->value = strdup("!=");
				token->type = T_NEQ;
			}
			break;


		// syntax signs
		case '[':
			token->value = strdup("[");
			token->type = T_L_BRACKET;
			break;

		case ']':
			token->value = strdup("]");
			token->type = T_R_BRACKET;
			break;

		case '(':
			token->value = strdup("(");
			token->type = T_L_PAREN;
			break;

		case ')':
			token->value = strdup(")");
			token->type = T_R_PAREN;
			break;


		// id signs
		case '`':
			token->value = strdup("`");
			token->type = T_BACKQUOTE;
			break;

		case ':':
			token->value = strdup(":");
			token->type = T_COLON;
			break;

		case ',':	
			token->value = strdup(",");
			token->type = T_COMMA;
			break;

		case ';':
			token->value = strdup(";");
			token->type = T_SEMI;
			break;

		case '.':
			token->value = strdup(".");
			token->type = T_DOT;
			break;

		default:
			// number
			if (isdigit(src[i]))
			{
				token_number(token, src);
			}

			// id
			else if (isalpha(src[i]))
			{
				token_id(token, src);
				token->type = T_ID;
			}
			else
			{
				fprintf(stderr, "ERROR lexer: <%c>: %d\n", src[i], src[i]);
				fprintf(stderr, "i: %d\n", i);
				exit(0);
			}
			break;
		}
		pos++;
	}

	tokens->pos  = 0;
	tokens->size = pos;
	tokens->token = realloc(tokens->token, tokens->size * sizeof(Token));

	//tokens_view(tokens);
	return (tokens);
}






Tokens *make_lexer()
{
	Tokens* toks = malloc(sizeof(Tokens));
	toks->token  = malloc(100 * sizeof(Token));
	toks->pos	 = 0;
	toks->size   = 100;

	token = &toks->token[0];
	return (toks);
}


void tokens_view(Tokens *tokens)
{
	for (int i = 0; i < tokens->size; ++i)
	{
		printf("%d\t", tokens->token[i].line);
		printf("%s\t\t", tokens->token[i].value);
		printf("%d\n", tokens->token[i].type);
	}
}


void token_id(Token *dest, char* src)
{
	int index;
	const int maxTokenLeng = 32;
	
	for (index = 0; isalnum(src[i+index]) || src[i+index] == '_'; index++)
		;


	if (index > maxTokenLeng)
	{
		fprintf(stderr, "Too long id [token_id2]\n");
		exit(0);
	}

	dest->value = strndup(src+i, index);

	index--;
	i += index;
}



void token_number(Token *dest, char *src)
{
	int isfloat = 0;
	char num[32];
	int k = 0;

	while (isdigit(src[i]))
		num[k++] = src[i++];
	i--;


	if (src[i] == '.')
	{
		num[k++] = src[i++]; isfloat = 1;
		while (isdigit(src[i]))
			num[k++] = src[i++];
		num[k] = 0;
	}
	else
		num[k] = 0;


	dest->type  = T_INT + isfloat;
	dest->value = strdup(num);
}



int skip_comments(char *src)
{
	int line = 0;
	if (src[i] == '#' && src[i+1] == '>')
	{
		while (!(src[i] == '#' && src[i+1] == '<'))
		{
			if (src[i] == '\n')
				line++;
			i++;
		}
		i += 2;
		return line;
	}

	else
	{
		while (src[i] != '\n')
			i++;
		return 1;
	}
}


