#include <stddef.h>
#include <stdio.h>
#include <string.h>
#include <stdint.h>
#include "jWrite.h"

struct jWriteControl g_jWriteControl;			// global control struct
#define JWC(x) g_jWriteControl.x				// functions access global


// Internal functions
void jwPutch(char c);
void jwPutstr(char *str);
void jwPutraw(char *str);
void modp_itoa10(int32_t value, char* str);
void jwPretty();
enum jwNodeType jwPop();
void jwPush(enum jwNodeType nodeType);


void jwOpen(char *buffer, unsigned int buflen, enum jwNodeType rootType, int isPretty)
{
	memset(buffer, 0, buflen);	// zap the whole destination buffer
	JWC(buffer)= buffer;
	JWC(buflen)= buflen;
	JWC(bufp)= buffer;
	JWC(nodeStack)[0].nodeType= rootType;
	JWC(nodeStack)[0].elementNo= 0;
	JWC(stackpos)=0;
	JWC(error)= JWRITE_OK;
	JWC(callNo)= 1;
	JWC(isPretty)= isPretty;
	jwPutch((rootType==JW_OBJECT) ? '{' : '[');
}

int jwClose()
{
	if(JWC(error) == JWRITE_OK)
	{
		if(JWC(stackpos) == 0)
		{
			enum jwNodeType node= JWC(nodeStack)[0].nodeType;
			if(JWC(isPretty))
				jwPutch('\n');
			jwPutch((node == JW_OBJECT) ? '}' : ']');
		}
		else
			JWC(error)= JWRITE_NEST_ERROR;	// nesting error, not all objects closed when jwClose() called
	}
	return JWC(error);
}

int jwEnd()
{
	if(JWC(error) == JWRITE_OK)
	{
		enum jwNodeType node;
		int lastElemNo= JWC(nodeStack)[JWC(stackpos)].elementNo;
		node= jwPop();
		if(lastElemNo > 0)
			jwPretty();
		jwPutch((node == JW_OBJECT) ? '}' : ']');
	}
	return JWC(error);
}

int jwErrorPos()
{
	return JWC(callNo);
}


int _jwObj(char *key);

// put raw string to object (i.e. contents of rawtext without quotes)
//
void jwObj_raw(char *key, char *rawtext)
{
	if(_jwObj(key) == JWRITE_OK)
		jwPutraw(rawtext);
}

// put "quoted" string to object
//
void jwObj_string(char *key, char *value)
{
	if(_jwObj(key) == JWRITE_OK)
		jwPutstr(value);
}

void jwObj_int(char *key, int value)
{
	modp_itoa10(value, JWC(tmpbuf));
	jwObj_raw(key, JWC(tmpbuf));
}

void jwObj_bool(char *key, int oneOrZero)
{
	jwObj_raw(key, (oneOrZero) ? "true" : "false");
}

void jwObj_null(char *key)
{
	jwObj_raw(key, "null");
}

// put Object in Object
//
void jwObj_object(char *key)
{
	if(_jwObj(key) == JWRITE_OK)
	{
		jwPutch('{');
		jwPush(JW_OBJECT);
	}
}

// put Array in Object
//
void jwObj_array(char *key)
{
	if(_jwObj(key) == JWRITE_OK)
	{
		jwPutch('[');
		jwPush(JW_ARRAY);
	}
}

// Array insert functions
int _jwArr();

// put raw string to array (i.e. contents of rawtext without quotes)
//
void jwArr_raw(char *rawtext)
{
	if(_jwArr() == JWRITE_OK)
		jwPutraw(rawtext);
}

// put "quoted" string to array
//
void jwArr_string(char *value)
{
	if(_jwArr() == JWRITE_OK)
		jwPutstr(value);
}

void jwArr_int(int value)
{
	modp_itoa10(value, JWC(tmpbuf));
	jwArr_raw(JWC(tmpbuf));
}

void jwArr_bool(int oneOrZero)
{
	jwArr_raw((oneOrZero) ? "true" : "false");
}

void jwArr_null()
{
	jwArr_raw("null");
}

void jwArr_object()
{
	if(_jwArr() == JWRITE_OK)
	{
		jwPutch('{');
		jwPush(JW_OBJECT);
	}
}

void jwArr_array()
{
	if(_jwArr() == JWRITE_OK)
	{
		jwPutch('[');
		jwPush(JW_ARRAY);
	}
}


char *jwErrorToString(int err)
{
	switch(err)
	{
	case JWRITE_OK:         return "OK"; 
	case JWRITE_BUF_FULL:   return "output buffer full";
	case JWRITE_NOT_ARRAY:	return "tried to write Array value into Object";
	case JWRITE_NOT_OBJECT:	return "tried to write Object key/value into Array";
	case JWRITE_STACK_FULL:	return "array/object nesting > JWRITE_STACK_DEPTH";
	case JWRITE_STACK_EMPTY:return "stack underflow error (too many 'end's)";
	case JWRITE_NEST_ERROR:	return "nesting error, not all objects closed when jwClose() called";
	}
	return "Unknown error";
}

//============================================================================
// Internal functions
//
void jwPretty()
{
	int i;
	if(JWC(isPretty))
	{
		jwPutch('\n');
		for(i=0; i<JWC(stackpos)+1; i++)
			jwPutraw("    ");
	}
}

// Push / Pop node stack
//
void jwPush(enum jwNodeType nodeType)
{
	if((JWC(stackpos)+1) >= JWRITE_STACK_DEPTH)
		JWC(error)= JWRITE_STACK_FULL;		// array/object nesting > JWRITE_STACK_DEPTH
	else
	{
		JWC(nodeStack[++JWC(stackpos)]).nodeType= nodeType;
		JWC(nodeStack[JWC(stackpos)]).elementNo= 0;
	}
}

enum jwNodeType jwPop()
{
	enum jwNodeType retval= JWC(nodeStack[JWC(stackpos)]).nodeType;
	if(JWC(stackpos) == 0)
		JWC(error)= JWRITE_STACK_EMPTY;		// stack underflow error (too many 'end's)
	else
		JWC(stackpos)--;
	return retval;
}

void jwPutch(char c)
{
	if((unsigned int)(JWC(bufp) - JWC(buffer)) >= JWC(buflen))
	{
		JWC(error)= JWRITE_BUF_FULL;
	}else{
		*JWC(bufp)++ = c;
	}
}

// put string enclosed in quotes
//
void jwPutstr(char *str)
{
	jwPutch('\"');
	while(*str != '\0')
		jwPutch(*str++);
	jwPutch('\"');
}

// put raw string
//
void jwPutraw(char *str)
{
	while(*str != '\0')
		jwPutch(*str++);
}	


// *common Object function*
// - checks error
// - checks current node is OBJECT
// - adds comma if reqd
// - adds "key" :
//
int _jwObj(char *key)
{
	if(JWC(error) == JWRITE_OK)
	{
		JWC(callNo)++;
		if(JWC(nodeStack)[JWC(stackpos)].nodeType != JW_OBJECT)
			JWC(error)= JWRITE_NOT_OBJECT;			// tried to write Object key/value into Array
		else if(JWC(nodeStack)[JWC(stackpos)].elementNo++ > 0)
			jwPutch(',');
		jwPretty();
		jwPutstr(key);
		jwPutch(':');
		if(JWC(isPretty))
			jwPutch(' ');
	}
	return JWC(error);
}

// *common Array function*
// - checks error
// - checks current node is ARRAY
// - adds comma if reqd
//
int _jwArr()
{
	if(JWC(error) == JWRITE_OK)
	{
		JWC(callNo)++;
		if(JWC(nodeStack)[JWC(stackpos)].nodeType != JW_ARRAY)
			JWC(error)= JWRITE_NOT_ARRAY;			// tried to write array value into Object
		else if(JWC(nodeStack)[JWC(stackpos)].elementNo++ > 0)
			jwPutch(',');
		jwPretty();
	}
	return JWC(error);
}

static void strreverse(char* begin, char* end)
{
    char aux;
    while (end > begin)
        aux = *end, *end-- = *begin, *begin++ = aux;
}

/* brief convert an signed integer to char buffer */
void modp_itoa10(int32_t value, char* str)
{
    char* wstr=str;
    // Take care of sign
    unsigned int uvalue = (value < 0) ? -value : value;
    // Conversion. Number is reversed.
    do *wstr++ = (char)(48 + (uvalue % 10)); while(uvalue /= 10);
    if (value < 0) *wstr++ = '-';
    *wstr='\0';

    // Reverse string
    strreverse(str,wstr-1);
}
