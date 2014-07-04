#include <stdio.h>
#include <stdlib.h>
#include <stdarg.h>

#include "smprintf.h"


/******************************************************************************/
char * smprintf(char *fmt, ...)
{
	va_list fmtargs;
	char *buf = NULL;

	va_start(fmtargs, fmt);
	if (vasprintf(&buf, fmt, fmtargs) == -1)
		buf = NULL;  /* failed to allocate memory... 
				ignore it, set buf = NULL and go on*/
	va_end(fmtargs);

	return buf;
}
/******************************************************************************/


/******************************************************************************/
int readint(char * filename)
{
	int result = 0;

	FILE * tmp_file = fopen(filename, "r");
	if (! tmp_file)
	{
		fprintf(stderr, "%s: failed to open for reading\n", filename);
		return 0;
	}
	if (!fscanf(tmp_file, "%d", &result))
	{
		fprintf(stderr, "failed to read int from %s", filename);
		return 0;
	}
	
	fclose(tmp_file);
	return result;
}
/******************************************************************************/



/******************************************************************************/
char * readstring (char * filename)
{
	char * result = malloc(sizeof(char)*20);

	FILE * tmp_file = fopen(filename, "r");
	if ( !tmp_file )
	{
		fprintf(stderr, "%s: failed to open for reading\n", filename);
		return NULL;
	}

	if ( !fscanf(tmp_file, "%s", result) )
		fprintf(stderr, "Failed to resad 20 char string from %s", filename);
	
	fclose(tmp_file);
	return result;
}
/******************************************************************************/


