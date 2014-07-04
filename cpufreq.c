#include "smprintf.h"
#include <stdio.h>
#include <unistd.h>

#define KERNEL_MAX_FILE "/sys/devices/system/cpu/kernel_max"
	/*
	 * /sys/devices/system/cpu/cpu0/cpufreq/cpuinfo_cur_freq
	 * /sys/devices/system/cpu/cpu1/cpufreq/cpuinfo_cur_freq
	 * /sys/devices/system/cpu/cpu2/cpufreq/cpuinfo_cur_freq
	 * /sys/devices/system/cpu/cpu3/cpufreq/cpuinfo_cur_freq
	 * /sys/devices/system/cpu/online
	 * */


int get_cpufreq(void)
{
	int max_cores = sysconf(_SC_NPROCESSORS_CONF);
	int i = 0;
	int cur_freq[32];
	float cur_freq_tmp ;

	while ( i < max_cores )
	{
		cur_freq[i] = readint(smprintf("/sys/devices/system/cpu/cpu%d/cpufreq/cpuinfo_cur_freq",i));
		cur_freq_tmp = (float)cur_freq[i]/1000000 ;
		printf("%1.1f;", cur_freq_tmp);
		++i;
	}
	printf("\n");
	return 0;
}
