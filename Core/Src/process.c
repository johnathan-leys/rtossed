#include "process.h"
#include <stdio.h>

#define PROC_MAX 4		//max number of processes, "current to be define as four"

static task_struct process_table[PROC_MAX];	//static limits scope, should hold 5 task_struct 
//initialize it? not sure how to in declaration, maybe add a function

task_struct task_idle;		//This variable keeps track of context switches for the idle task (while (1) loop in main.c).

task_struct *current = &task_idle;	//init to first task_struct in process_table

void stack_init(task_struct * inputTask)
{				//increment through stack, set zeroes, r values
	uint32_t *sp = (uint32_t *) inputTask->r.sp;	//assign stak pointer, cast to 32 int
	for (int i = 0; i < 17; i++) {	//incremet through first 17 stack and set to 0, (FPSR to s0)
		*(--sp) = 0;	//set value to 0, update sp to decrement until xpsr
	};
	//now increment sp and assign r values
	*(--sp) = inputTask->r.xPSR;	//xpsr
	*(--sp) = inputTask->r.pc;	//pc
	*(--sp) = inputTask->r.lr;	//lr
	*(--sp) = inputTask->r.r12;
	*(--sp) = inputTask->r.r3;
	*(--sp) = inputTask->r.r2;
	*(--sp) = inputTask->r.r1;
	*(--sp) = inputTask->r.r0;
	inputTask->r.sp = (uint32_t) sp;	//cast to 32 

}

void process_table_init(void)
{
	memset(process_table, 0, sizeof(process_table));	//init process_table to zeroes, only way to do with "one function call" I know of

	//set process table to exe shell
	process_table[0].r.sp = (uint32_t) _eustack;
	process_table[0].sp_start = (uint32_t) _eustack;	//cast to get properly store
	process_table[0].r.lr = 0;

	process_table[0].r.pc = (uint32_t) process_start;

	process_table[0].r.xPSR = 0x01000000;
	process_table[0].state = run;

	//change to another instance of process1 to demonstrate locking
    process_table[0].cmd = &process1;	//shell "pseudopointer" process_table[0].cmd = &sh

	process_table[0].exc_return = EXC_RETURN_THREAD_PSP;
	process_table[0].pid = 0;

	stack_init(&process_table[0]);	//cast to pointer, init

	task_idle.state = stop;
	task_idle.r.xPSR = 0x01000000;
	task_idle.exc_return = EXC_RETURN_THREAD_MSP_FPU;
	task_idle.pid = -2;

	//now set process table[1] to be process1();

	process_table[1].r.sp = (uint32_t) _eustack - 0x800;
	process_table[1].sp_start = (uint32_t) _eustack - 0x800;
	process_table[1].r.lr = 0;
	process_table[1].r.pc = (uint32_t) process_start;
	process_table[1].r.xPSR = 0x01000000;
	process_table[1].state = run;

	process_table[1].cmd = &process1;	//shell "pseudopointer"

	process_table[1].exc_return = EXC_RETURN_THREAD_PSP;
	process_table[1].pid = 1;

	stack_init(&process_table[1]);

}

void process_start()
{
	int (*cmd1)() = current->cmd;
	cmd1();

	current->state = stop;
	while (1) {
		//no op
	}
}

task_struct *schedule(void)
{
    
	static int next_task_index;

	//check each for current, set next, round robin style
	if (current == &process_table[0]) {
		next_task_index = 1;

	} else if (current == &process_table[1]) {
		next_task_index = 2;

	} else if (current == &process_table[2]) {
		next_task_index = 3;

	} else {		//Process 3, if for some reason current is none of these, it will default to index 0
		next_task_index = 0;

	}

	//increment through each table, starting with next_task, return at first run instance
	for (int i = 0; i < 4; i++) {
		if ((process_table[next_task_index].state & time_sleep) == time_sleep) {	//if state is in time sleep

			if (process_table[next_task_index].w_time < uwTick) {	//if uwTick is larger

				process_table[next_task_index].state &= ~time_sleep;	//clear sleep
				process_table[next_task_index].state |= run;	//set run

			}

		}
		if (process_table[next_task_index].state & run) {	//if state is in run

			return &process_table[next_task_index];
		}

		if (next_task_index >= 3)
			next_task_index = 0;	//loop back to 0, avoid out of bounds index
		else
			next_task_index++;	//else increment index of next

	}

	return &task_idle;	//if none are runnnable, run idle task
    
   
}
