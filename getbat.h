#ifndef _getbat_h_
#define _getbat_h_

/******************************************************************************/
#define BAT_DIR "/sys/class/power_supply/BAT0"

#define NOW_STATE BAT_DIR"/charge_now"
#define NOW_FULL  BAT_DIR"/charge_full"
#define NOW_DESIGN BAT_DIR"/charge_full_design"
#define NOW_STATUS BAT_DIR"/status"
/******************************************************************************/

/******************************************************************************/
char * getbat (void);
/******************************************************************************/

#endif /* _getbat_h_ */

