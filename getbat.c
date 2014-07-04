#include <stdio.h>
#include <stdint.h>
#include "getbat.h"
#include "smprintf.h"



/******************************************************************************/
char * getbat (void)
{
	char * status = readstring(NOW_STATUS);
	int now_state = readint(NOW_STATE)/10000;
	int now_full = readint(NOW_FULL)/10000;
	int now_design = readint(NOW_DESIGN)/10000;
	
	uint8_t bat_proc = 0;

	if ( now_state > now_full )
		bat_proc = ( (now_state*100)/now_design );
	else
		bat_proc = ( (now_state*100)/now_full );

	return smprintf("bat: %s %d%%", status, bat_proc);
}
/******************************************************************************/

