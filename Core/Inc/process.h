/* USER CODE BEGIN Header */
/**
******************************************************************************
  * @file    process.h
  * @brief   This file contains all the function prototypes for
  *          the process.c file
  ******************************************************************************
    */
/* USER CODE END Header */
/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __PROCESS_H__
#define __PROCESS_H__

#ifdef __cplusplus
extern "C" {
#endif
//begin user code--------
#include "stm32h7xx_hal.h" //found in drivers, has def for 
#include "core_cm7.h"



static inline void yield(void) //static forces compiler to consider it, inline is in .h
{ //In this function set the PENDSV bit to one in the ICSR register within the System Control Block (SCB)
    SCB->ICSR |= SCB_ICSR_PENDSVSET_Msk; //or with predeclared ISC ICSR mask, avoids wipinf any data already in ICSR
    __DSB(); //predeclared data synch barrier, CMSIS function
    __ISB(); //predeclared inst sync barrier, CMSIS function
}
//need to define r struct above task_struct or prototype it...
/*
packed attribute stops compiler from padding- adding offsets to memoery in a structure.
Padding may interfere with the registers?
From ARM Cortex m7 docs:
The processor has the following 32-bit registers:

13 general-purpose registers, R0-R12.

Stack Pointer (SP), R13 alias of banked registers, SP_process and SP_main.

Link Register (LR), R14.

Program Counter (PC), R15.

Special-purpose Program Status Registers (xPSR).
*/
typedef struct __attribute__((__packed__)) { 
    uint32_t r0, r1, r2, r3, r4, r5, r6, r7, r8, r9, r10, r11, r12; //general purpose regs

    uint32_t lr; //link register r14
    uint32_t pc; // program counter r15
    uint32_t xPSR; //Special-purpose Program Status Registers


}saved_reg;


//Task (process) Structure
typedef struct{ //typedef is needed or else declaration occurs multiple times...

uint16_t state; //16 should be big enough for many more states later, even if each state is only one bit (bit map), can hold up to 16 states
uint16_t pid;// unique integer

uint32_t exc_return; // program counter value that indicates how an exception handler returns,32 bit system so uint32
uint32_t sp_start; //Starting stack pointer address, 32bit

int (*cmd)(void); //Pointer to int cmd(void) function, not created yet

saved_reg r; //previously defined packed structure of saved registers

}task_struct;


//end user code---------
#ifdef __cplusplus
}
#endif
#endif