#include <stdio.h>
#include "jWrite.h"


int main(int argc, char * argv[])
{
	char buffer[1024];
	unsigned int buflen= 1024;
	int err;

	printf("A JSON object example:\n\n");

	jwOpen( buffer, buflen, JW_OBJECT, JW_PRETTY );		// start root object

	jwObj_string( "key", "value" );				// add object key:value pairs
	jwObj_int( "int", 1 );
	jwObj_null( "nullThing" );
	jwObj_bool( "bool", 1 );
	jwObj_array( "EmptyArray" );

	jwEnd();
	jwObj_array( "anArray" );					// array with elements
		jwArr_string("array one" );
		jwArr_int( -2 );
		jwArr_null();
		jwArr_bool( 0 );
		jwArr_object();							// object in array
			jwObj_string( "obj3_one", "one");
			jwObj_string( "obj3_two", "two");
		jwEnd();
		jwArr_array();						// array in array
			jwArr_int( 0 );
			jwArr_int( 1 );
			jwArr_int( 2 );
		jwEnd();
	jwEnd();									// end of "anArray" , back to root object

	jwObj_object( "EmptyObject" );
	jwEnd();

	jwObj_object( "anObject" );					// object in the root object
		jwObj_string("msg","object in object");
		jwObj_string("msg2","object in object 2nd entry");
	jwEnd();
	jwObj_string( "ObjEntry", "This is the last one" );

	err= jwClose();								// close and get error code

	printf("%s\n", buffer);
	if( err != JWRITE_OK )
		printf( "Error: %s at function call %d\n", jwErrorToString(err), jwErrorPos() );
}

