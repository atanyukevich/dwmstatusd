#include "gettime.h"
#include "getbat.h"
#include "smprintf.h"
#include "gettemperature.h"
#include "pulseaudiovol.h"


#include <X11/Xlib.h>
#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>


/******************************************************************************/
int main (void)
{
#ifndef _DEBUG
	static Display * dpy;
	pid_t process_id = 0;
	
	process_id = fork();
	if (process_id < 0)
	{
		fprintf(stderr, "fork failed!\n");
		exit(EXIT_FAILURE);
	}
	
	if (process_id > 0)
	{
		printf("process_id of child process %d \n", process_id);
		exit(EXIT_SUCCESS);
	}
	umask(0);
	
	if( setsid() < 0) { exit(1); }
	
	if ( chdir("/") < 0 ) { exit(1); }
	
	if (!(dpy = XOpenDisplay(NULL))) {
		fprintf(stderr, "dwmstatus: cannot open display.\n"); 
		exit(EXIT_FAILURE);
	}
	
	close(STDIN_FILENO);
	close(STDOUT_FILENO); 
	close(STDERR_FILENO);
#endif /* _DEBUG */

	while(1)
	{
		char * bat_status = getbat(); 
		char * time_status = gettime();
		/* char * temperature_status = gettemperature(); */
		char * volume_status = getpavolume();
		char * final_status = smprintf("%s | %s | %s", volume_status, bat_status, time_status);
		
#ifndef _DEBUG
		XStoreName(dpy, DefaultRootWindow(dpy), final_status);
		XSync(dpy, False);
#else /* _DEBUG */
		printf("%s\n", final_status);
#endif /* _DEBUG */

		free(bat_status); 
		free(time_status);
		free(volume_status);
		free(final_status);
		/* free(temperature_status); */

		sleep(1);
	}
	
	
#ifndef _DEBUG
	XCloseDisplay(dpy);
#endif /* _DEBUG */

	return EXIT_SUCCESS;
}
/******************************************************************************/
