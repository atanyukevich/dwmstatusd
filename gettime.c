#include "gettime.h"

#include <time.h>
#include <stdlib.h>

/******************************************************************************/
char * gettime(void)
{
	time_t rawtime;
	char * buffer = malloc(sizeof(char)*80);

	time(&rawtime);

	strftime (buffer, 80, "%A %d %B %Y-%m-%d %X",localtime(&rawtime));
	return buffer;
}
/******************************************************************************/

