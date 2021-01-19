#ifndef AST_H
#define AST_H

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>

#include "lexer.h"

typedef enum
{
	N_FDEC,	
	N_FDEF,	
	N_FCALL,

	N_VDEC,	
	N_ADEC,	
	N_PDEC,	

	N_ASSIGN,
	N_BINOP,

	L_VAR,
	L_ARR,
	L_PTR,
} ntype;



struct node
{
	ntype type;
	union
	{
		char *id;
		char *value;

		struct fdec
		{
			char *type;
			char *id;
			struct node **argv;
			int argc;
		} fdec;

		struct fdef
		{
			struct node *dec;
			struct node **body;
			int insc;
		} fdef;

		struct fcall
		{
			char *id;
			struct node *argv;
			int argc;
		} fcall;

		struct vdec
		{
			char *type;
			char *id;
		} vdec;

		struct adec
		{
			char *type;
			char *id;
			int  *indexes;
			int  dim;
		} adec;
		struct arr
		{
			char *id;
			int *indexes;
			int  dim;
		} arr;

		struct pdec
		{
			char *type;
			char *id;
			int deep;
		} pdec;
		struct ptr
		{
			char *id;
			int deep;
		} ptr;


		struct assign
		{
			struct node *var;
			struct node *exp;
		} assign;

		struct binop
		{
			struct node *left;
			struct node *right;
			TokenType op;
		} binop;
	};
} node;



extern Tokens *tokens;
extern Token  *token;
extern int pos;



struct node *generate_ast(Tokens *toks);
void represent_ast(struct node *ast);

struct node *macrostruct();
struct node *import();
struct node *class();
struct node *proc();
	struct node **get_fparam(int *argc);
	
struct node *struct_();
struct node *union_();

struct node *microstruct(int mode);

struct node *instruction();
	struct node *assignment();
	struct node *expression();
	struct node *binop();
	int ast_expr(struct node *node);
	




/* expr */


/* struct */
struct node *macrostruct();
	struct node *import();
	struct node *tclass();
	struct node *tstruct();
	struct node *tunion();
	struct node *proc();
		struct node **get_fparam(int *argc);
		struct node **get_aparam(int *argc);
		struct node *freturn();
		

struct node *microstruct(int mode);
	struct node *array();
	struct node *pointer();
	struct node *variable();


struct node *instruction();
	struct node *iif();
	struct node *ielif();
	struct node *ielse();
	struct node *ifor();
	struct node *iwhile();
	struct node *assignment();
		struct node *binop();
		struct node *factor();
		struct node *term();
		struct node *expression();


struct node **bbody(int *insc);




/* view */
void proc_view(struct node *node);






// aux proc
int  advance(TokenType type);
int  lookup(char *value, int shift);
char *getvalue(TokenType type);
void tokv();


#endif
