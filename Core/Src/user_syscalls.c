#include "user_syscalls.h"
#include "process.h"
  uint32_t microsleep(uint32_t sleep_time)
{
	current->w_time = (sleep_time / 1000) + (uwTick);	//set wake time based on sleep time, change units
	current->state |= time_sleep;	//change state to sleep, 0x01
	current->state &= ~run;	//clear run
	yield();
	 return 1;		//tmp "The function returns the amount of time left to sleep (ignore this for now)"
}


