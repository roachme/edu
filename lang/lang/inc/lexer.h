#ifndef TOKENIZER_H
#define TOKENIZER_H


typedef enum {
	T_ID,
	T_NUM,
	T_INT,
	T_FLOAT,
	T_CHAR,
	T_STRING,
	
	T_PLUS,
	T_MINUS,	
	T_MUL,
	T_DIV,
	T_MOD,

	T_LESSER,
	T_GRATTER,
	T_LEQ,
	T_GEQ,
	T_EQ,
	T_NEQ,
	
	T_ASSIGN,

	T_L_BRACKET,
	T_R_BRACKET,
	T_L_PAREN,
	T_R_PAREN,
	
	//T_AMPERSANT,
	T_BACKQUOTE,
	T_COLON,
	T_COMMA,
	T_SEMI,
	T_DOT,

} TokenType;

typedef struct token
{
	TokenType type;
	char *value;
	int line;
} Token;

typedef struct tokens
{
	Token *token;
	int pos;
	int size;
} Tokens;


Tokens *lexer(char *src);
Tokens *make_lexer();



void token_id(Token *dest, char* src);
void token_number(Token *dest, char* src);
void token_char(Token *dest, char* src);
void token_string(Token *dest, char* src);
void token_token(Token *dest, char* src);

void tokens_view();
int skip_comments(char *src);







#endif
