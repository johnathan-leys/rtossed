#include "user_syscalls.h"
#include "process.h"

{
	
	current->state |= time_sleep;	//change state to sleep, 0x01
	current->state &= ~run;	//clear run
	yield();
	


