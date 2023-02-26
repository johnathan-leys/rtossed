#include "process.h"

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

	process_table[0].cmd = &sh;	//shell "pseudopointer"

	process_table[0].exc_return = EXC_RETURN_THREAD_PSP;
	process_table[0].pid = 0;

	stack_init(&process_table[0]);	//cast to pointer, init

	task_idle.state = stop;
	task_idle.r.xPSR = 0x01000000;
	task_idle.exc_return = EXC_RETURN_THREAD_MSP_FPU;
	task_idle.pid = -2;

    //now set process table[1] to be process1();

    process_table[1].r.sp = (uint32_t) _eustack -0x800;
	process_table[1].sp_start = (uint32_t) _eustack -0x800;	
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
	if (current == &task_idle) {	//if current points address of idle task
		return &process_table[0];	//return first process table entry
	} 
    else if (current == &process_table[0]) {	//if current points address of idle task
		return &process_table[1];	//return first process table entry
	}
    else if (current == &process_table[1]) {	//if current points address of idle task
		return &task_idle;	//return first process table entry
	}
    else {
		return &task_idle;	//return memory of idle task
	}

}
