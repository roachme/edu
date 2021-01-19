#include "ast.h"


struct node *binop(struct node *left, TokenType op, struct node *right)
{
	struct node *node = malloc(sizeof(struct node));
	node->binop.left  = left;
	node->binop.op    = op;
	node->binop.right = right;

	node->type = N_BINOP;
	return node;
}

struct node *factor()
{
	struct node *node;

	if (token->type == T_ID && token->value[0] == '.')
	{
		// fcall
	}

	else if (token->type == T_ID)
	{
		if (lookup("[", 1))
		{

		}

		else if (lookup("*", 0))
		{

		}

		else
		{
			node = malloc(sizeof(struct node));
			node->id = getvalue(token->type);
			node->type = L_VAR;
			return node;
		}
	}

	else if (token->type == T_L_PAREN)
	{
		advance(T_L_PAREN);
		node = expression();
		advance(T_R_PAREN);
		return node;
	}

	/* const data: int, float, string, char */
	node = malloc(sizeof(struct node));
	node->type  = token->type;
	node->value = getvalue(token->type);
	return node;
}

struct node *term()
{
	struct node *node = factor();
	TokenType op;

	while (token->type == T_MUL || token->type == T_DIV) 
	{	
		op = token->type;
		advance(op);
		node = binop(node, op, factor());
	}
	return node;
}

struct node *expression()
{
	struct node *node = term();
	TokenType op;

	while (token->type == T_PLUS || token->type == T_MINUS) 
	{
		op = token->type;
		advance(op);
		node = binop(node, op, term());
	}
	return node;
}

