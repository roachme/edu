#include "ast.h"

static char space[] = "    ";



void fparam_view(struct node **node, int argc)
{
	printf("[");

	for (int i = 0; i < argc; ++i)
	{
		printf("%s ",  node[i]->vdec.type);
		printf("%s", node[i]->vdec.id);
		if (i+1 < argc) printf(", ");
	}
	printf("]");
}


void microstruct_view(struct node *node)
{
	if (node->type == N_VDEC)
	{
		printf("%s%s ",space, node->vdec.type);
		printf("%s;\n", node->vdec.id);
	}

	else if (node->type == N_ADEC)
	{
		printf("%s%s ",space, node->adec.type);
		printf("%s", node->adec.id);
		for (int i = 0; i < node->adec.dim; ++i)
			printf("[%d]", node->adec.indexes[i]);
		printf(";\n");
	}
}


void proc_view(struct node *node)
{
	printf("[..] proc ast view\n\n");

	printf("proc %s", node->fdef.dec->fdec.id);
	fparam_view(node->fdef.dec->fdec.argv, node->fdef.dec->fdec.argc);
	
	if (node->type == N_FDEF) printf(":\n");
	else printf("\n");
	printf("    %s ret;\n", node->fdef.dec->fdec.type);

	for (int i = 0; i < node->fdef.insc; ++i)
		microstruct_view(node->fdef.body[i]);



	printf("end\n\n\n");
}






/* expr */ 

int ast_expr(struct node *node) {
	int left, right;
	switch (node->binop.op) {
	case T_PLUS:
		left  = ast_expr(node->binop.left);
		printf(" + ");
		right = ast_expr(node->binop.right);
		break;

	case T_MINUS:	
		left  = ast_expr(node->binop.left);
		printf(" - ");
		right = ast_expr(node->binop.right);
		break;
	
	case T_MUL:	
		left  = ast_expr(node->binop.left);
		printf(" * ");
		right = ast_expr(node->binop.right);
		break;

	case T_DIV:	
		left  = ast_expr(node->binop.left);
		printf(" / ");
		right = ast_expr(node->binop.right);
		break;

	default:
		if (token->type == T_ID)
		{
			if (lookup("[", 1))
			{

			}

			else if (lookup("*", 0))
			{

			}

			else
			{
				printf("%s", node->value);
			}
		}

		/* const data: int, float, string, char */
		else
		{
			printf("%s", node->value);
		}
		break;
	}
}
