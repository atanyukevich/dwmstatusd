/*
 * gettemperature("/sys/class/hwmon/hwmon0/device", "temp1_input");
 **/

#include "gettemperature.h"
#include "smprintf.h"

/*****************************************************************************/
char * gettemperature(void)
{
	int c1 = readint(THERM1_FILE);
	int c2 = readint(THERM2_FILE);
	if ( ! ( c1 || c2 ) ) return smprintf("");
	return smprintf("temp: %d/%dC", c1/1000, c2/1000);
}
/*****************************************************************************/

