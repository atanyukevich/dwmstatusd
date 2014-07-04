#include "pulseaudiovol.h"
#include "smprintf.h"
#include <string.h>

/* #include <pulse/pulseaudio.h> */

/******************************************************************************/
char * getpavolume(void)
{
	uint8_t ctr;
	char * result;
	pa_devicelist_t pa_output_devicelist[16];
	

	result = smprintf("vol: ");
	if (pa_get_devicelist(pa_output_devicelist) < 0) {
		return smprintf("ERR");
	}

	for (ctr = 0; ctr < 16; ctr++) {
		if (! pa_output_devicelist[ctr].initialized) {
			continue;
		}
		if ( pa_output_devicelist[ctr].mute )
		{
			char * tmp_res = result ;
			result = smprintf("%s mute", tmp_res) ;
			free(tmp_res);
		}
		else
		{
			char * tmp_res = result;
			result = smprintf("%s %d%%", tmp_res, (pa_cvolume_avg(&pa_output_devicelist[ctr].volume)*100)/PA_VOLUME_NORM);
			free(tmp_res);
		}
	}
	return result;
}
/******************************************************************************/



/******************************************************************************/
int pa_get_devicelist(pa_devicelist_t *output)
{
	pa_mainloop *pa_ml = NULL;
	pa_mainloop_api *pa_mlapi = NULL;
	pa_operation *pa_op = NULL;
	pa_context *pa_ctx = NULL;

	uint8_t state = 0;
	int pa_ready = 0;

	memset(output, 0, sizeof(pa_devicelist_t) * 16);

	if ( (pa_ml = pa_mainloop_new()) == NULL) return -1;
	if ( (pa_mlapi = pa_mainloop_get_api(pa_ml)) == NULL ) return -2;
	if ( (pa_ctx = pa_context_new(pa_mlapi, "test")) == NULL) return -3;

	pa_context_connect(pa_ctx, NULL, 0, NULL);

	pa_context_set_state_callback(pa_ctx, pa_state_cb, &pa_ready);

	while (1) {
		if (pa_ready == 0) {
			pa_mainloop_iterate(pa_ml, 1, NULL);
			continue;
		}
		if (pa_ready == 2) {
			pa_context_disconnect(pa_ctx);
			pa_context_unref(pa_ctx);
			pa_mainloop_free(pa_ml);
			return -1;
		}
		switch (state) {
			case 0:
				pa_op = pa_context_get_sink_info_list(pa_ctx, pa_sinklist_cb, output);

				state++;
				break;
			case 1:
				if (pa_operation_get_state(pa_op) == PA_OPERATION_DONE) {
					pa_operation_unref(pa_op);
					pa_context_disconnect(pa_ctx);
					pa_context_unref(pa_ctx);
					pa_mainloop_free(pa_ml);
					return 0;
				}
				break;
			default:
				return -1;
		}
		pa_mainloop_iterate(pa_ml, 1, NULL);
	}
}
/******************************************************************************/



/******************************************************************************/
void pa_state_cb(pa_context *c, void *userdata)
{
	pa_context_state_t state;
	int *pa_ready = userdata;

	state = pa_context_get_state(c);
	switch  (state) {
		case PA_CONTEXT_UNCONNECTED:
		case PA_CONTEXT_CONNECTING:
		case PA_CONTEXT_AUTHORIZING:
		case PA_CONTEXT_SETTING_NAME:
		default:
			break;
		case PA_CONTEXT_FAILED:
		case PA_CONTEXT_TERMINATED:
			*pa_ready = 2;
			break;
		case PA_CONTEXT_READY:
			*pa_ready = 1;
			break;
	}
}
/******************************************************************************/



/******************************************************************************/
void pa_sinklist_cb(pa_context *c, const pa_sink_info *l, int eol, void *userdata)
{
	pa_devicelist_t *pa_devicelist = userdata;
	uint8_t ctr = 0;

	if (eol > 0) {
		return;
	}

	for (ctr = 0; ctr < 16; ctr++) {
		if (! pa_devicelist[ctr].initialized) {
			pa_devicelist[ctr].volume = l->volume;
			pa_devicelist[ctr].mute = l->mute;
			pa_devicelist[ctr].initialized = 1;
			
			break;
		}
	}
}
/******************************************************************************/

