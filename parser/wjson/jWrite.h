#ifndef JWRITE_H
#define JWRITE_H

#define JWRITE_STACK_DEPTH 32			// max nesting depth of objects/arrays
#define JW_COMPACT	0					// output string control for jwOpen()
#define JW_PRETTY	1					// pretty adds \n and indentation

enum jwNodeType{
	JW_OBJECT= 1,
	JW_ARRAY
};

struct jwNodeStack{
	enum jwNodeType nodeType;
	int elementNo;
};

struct jWriteControl{
	char *buffer;						
	unsigned int buflen;				
	char *bufp;							
	char tmpbuf[32];					
	int error;							
	int callNo;							
	struct jwNodeStack nodeStack[JWRITE_STACK_DEPTH];
	int stackpos;
	int isPretty;						
};

// Error Codes
// -----------
#define JWRITE_OK           0
#define JWRITE_BUF_FULL     1		// output buffer full
#define JWRITE_NOT_ARRAY	2		// tried to write Array value into Object
#define JWRITE_NOT_OBJECT	3		// tried to write Object key/value into Array
#define JWRITE_STACK_FULL	4		// array/object nesting > JWRITE_STACK_DEPTH
#define JWRITE_STACK_EMPTY	5		// stack underflow error (too many 'end's)
#define JWRITE_NEST_ERROR	6		// nesting error, not all objects closed when jwClose() called


char *jwErrorToString( int err );


void jwOpen( char *buffer, unsigned int buflen, enum jwNodeType rootType, int isPretty );
int jwClose( );
int jwErrorPos( );

void jwObj_string( char *key, char *value );
void jwObj_int( char *key, int value );
void jwObj_double( char *key, double value );
void jwObj_bool( char *key, int oneOrZero );
void jwObj_null( char *key );
void jwObj_object( char *key );
void jwObj_array( char *key );

void jwArr_string( char *value );
void jwArr_int( int value );
void jwArr_double( double value );
void jwArr_bool( int oneOrZero );
void jwArr_null( );
void jwArr_object( );
void jwArr_array( );

int jwEnd( );
void jwObj_raw( char *key, char *rawtext );
void jwArr_raw( char *rawtext );

#endif