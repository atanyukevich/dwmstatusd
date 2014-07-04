#ifndef _pulseaudiovol_h_
#define _pulseaudiovol_h_

#include <pulse/pulseaudio.h>

/******************************************************************************/
typedef struct pa_devicelist 
{
	uint8_t initialized;
	int mute;
	pa_cvolume volume;
} pa_devicelist_t;
/******************************************************************************/

/******************************************************************************/
void pa_state_cb(pa_context *c, void *userdata);
void pa_sinklist_cb(pa_context *c, const pa_sink_info *l, int eol, void *userdata);
int pa_get_devicelist(pa_devicelist_t *output);
char * getpavolume(void);
/******************************************************************************/

#endif /* _pulseaudiovol_h_ */
