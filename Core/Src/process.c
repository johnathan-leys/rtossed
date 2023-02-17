#include "process.h"

#define PROC_MAX 4 //max number of processes, "current to be define as four"

static task_struct process_table[PROC_MAX]; //static limits scope, should hold 5 task_struct 
//initialize it? not sure how to in declaration, maybe add a function


task_struct *current = &process_table[0]; //init to first task_struct in process_table

task_struct task_idle; //This variable keeps track of context switches for the idle task (while (1) loop in main.c).

void stack_init(task_struct *inputTask) 
{   //increment through stack, set zeroes, r values
    uint32_t *sp = (uint32_t*) inputTask->sp_start; //assign stak pointer, cast to 32 int
    for(int i =0; i< 16; i++){//incremet through first 17 stack and set to 0, (FPSR to s0)
    *(--sp) = 0; //set value to 0, update sp to decrement until xpsr
    };
    //now increment sp and assign r values
    *(--sp) = inputTask->r.xPSR; //xpsr
    *(--sp) = inputTask->r.pc; //pc
    *(--sp) = inputTask->r.lr; //lr
    *(--sp) = inputTask->r.r12;
    *(--sp) = inputTask->r.r3;
    *(--sp) = inputTask->r.r2;
    *(--sp) = inputTask->r.r1;
    *(sp) = inputTask->r.r0; //leave sp or decrement again?
    //save new sp, should be at r0 or past it? not sure
    inputTask->sp_start = (uint32_t) sp; //cast to 32 to get rid of warning

}