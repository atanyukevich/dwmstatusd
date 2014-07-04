#ifndef _gettemperature_h_
#define _gettemperature_h_

#define THERM1_FILE  "/sys/class/hwmon/hwmon0/device/temp1_input"
#define THERM2_FILE  "/sys/class/hwmon/hwmon0/device/temp1_input"

/*****************************************************************************/
char * gettemperature(void);
/*****************************************************************************/

#endif /* _gettemperature_h_ */
