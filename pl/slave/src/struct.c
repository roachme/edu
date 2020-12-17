#include "ast.h"



// import, class, proc, struct, union
struct node *macrostruct()
{
	if (!strcmp(token->value, "import"))
	{
		return import();
	}

	else if (!strcmp(token->value, "class"))
	{
		return tclass();
	}

	else if (!strcmp(token->value, "proc"))
	{
		return proc();
	}
	
	else if (!strcmp(token->value, "struct"))
	{
		return tstruct();
	}

	else if (!strcmp(token->value, "union"))
	{
		return tunion();
	}

	else
	{
		return microstruct(0);
	}
}

struct node *import()
{

}

struct node *tclass()
{

}

struct node *tstruct()
{
	
}
	
struct node *tunion()
{
	
}

struct node *proc()
{
	advance(T_ID); // skip 'proc'	
	struct node *dec = malloc(sizeof(struct node));
	dec->fdec.id     = getvalue(T_ID);
	dec->fdec.argv   = get_fparam(&dec->fdec.argc);

	if (lookup(";", 0))
	{
		advance(T_SEMI);
		dec->type = N_FDEC;
		return dec;
	}

	advance(T_COLON);
	dec->fdec.type = getvalue(T_ID);
	advance(T_ID); advance(T_SEMI); // for 'return' command

	struct node *def = malloc(sizeof(struct node));
	def->fdef.dec    = dec;
	def->fdef.body   = bbody(&def->fdef.insc);
	advance(T_ID);

	def->type = N_FDEF;
	return def;
}

struct node **get_fparam(int *argc)
{
	int i = 0;
	struct node **node = malloc(sizeof(struct node*));

	advance(T_L_BRACKET);
	do {
		node[i] = malloc(sizeof(struct node));
		node[i]->vdec.type = getvalue(T_ID);
		node[i]->vdec.id   = getvalue(T_ID);
		
		i++;
	} while (token->type == T_COMMA && advance(T_COMMA));
	advance(T_R_BRACKET);

	*argc = i;
	return node;
}

struct node **get_aparam(int *argc)
{

}







// var, arr, ptr
struct node *microstruct(int mode)
{
	struct node *node;
	char *type;

	if (!mode)
		type = getvalue(T_ID);

	if (lookup("[", 1))
	{
		node = array();
		if (!mode) node->adec.type = type;
	}
	
	else if (lookup("*", 0))
	{
		node = pointer();
		if (!mode) node->pdec.type = type;
	}

	else
	{
		node = variable();
		if (!mode) node->vdec.type = type;
	}

	if (!mode) advance(T_SEMI);
	return node;
}

struct node *array()
{
	int i = 0;
	int maxdim = 5;
	struct node *node  = malloc(sizeof(struct node));
	node->adec.indexes = malloc(sizeof(struct node) * maxdim); // 5 dimensional by default
	node->adec.id      = getvalue(T_ID);

	// handle indexes
	do
	{
		if ((i+1) == maxdim)
		{
			maxdim += 2;
			node->adec.indexes = realloc(node->adec.indexes, maxdim);
		}
		advance(T_L_BRACKET);
		node->adec.indexes[i] = atoi(getvalue(T_INT));
		advance(T_R_BRACKET);

		i++;
	} while (token->type == T_L_BRACKET && lookup("[", 0));

	node->adec.indexes = realloc(node->adec.indexes, i);
	node->adec.dim     = i;

	node->type = N_ADEC;
	return node;
}

struct node *pointer()
{
	int deep = 0;
	struct node *node  = malloc(sizeof(struct node));

	// handling of pointer's deep 
	for (; token->type == T_MUL; deep++)
		advance(T_MUL);

	node->pdec.deep    = deep;
	node->type		   = N_PDEC;
	node->pdec.id      = getvalue(T_ID);

	return node;
}

struct node *variable()
{
	struct node *node = malloc(sizeof(struct node));
	node->vdec.id     = getvalue(T_ID);
	node->type = N_VDEC;

	return node;
}


// assignment, if, else, while, for
struct node *instruction()
{
	if (!strcmp(token->value, "if"))
	{
		return iif();
	}

	else if (!strcmp(token->value, "elif"))
	{
		return ielif();
	}

	else if (!strcmp(token->value, "else"))
	{
		return ielse();
	}

	else if (!strcmp(token->value, "for"))
	{
		return ifor();
	}

	else if (!strcmp(token->value, "while"))
	{
		return iwhile();
	}

	else if ((tokens->token[pos+1].type == T_ID) || 
			 (tokens->token[pos+1].type == T_MUL)) // for pointer
	{
		return microstruct(0);		
	}

	else
	{
		return assignment();
	}
}

struct node *iif()
{

}

struct node *ielif()
{
	
}

struct node *ielse()
{
	
}

struct node *ifor()
{
	
}

struct node *iwhile()
{
	
}

struct node *assignment()
{
	struct node *node = malloc(sizeof(struct node));

	node->assign.var  = microstruct(1);
	advance(T_ASSIGN);
	node->assign.exp  = expression();
	advance(T_SEMI);

	node->type = N_ASSIGN;
	return node;
}

// bound body of proc, branch, loop
struct node **bbody(int *insc)
{
	int i = 0;
	struct node **body = malloc(sizeof(struct node*));

	for (; strcmp(token->value, "end"); i++)
	{
		body[i] = malloc(sizeof(struct node));
		body[i] = instruction();
	}

	*insc = i;
	return body;
}


