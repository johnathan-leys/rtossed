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
    SCB->ICSR |= SCB_ICSR_PENDSVSET_Msk; //or with predeclared ISC ICSR mask, avoids wipinf any data
    __DSB(); //predeclared data synch barrier, CMSIS function
    __ISB(); //predeclared inst sync barrier, CMSIS function
}


//end user code---------
#ifdef __cplusplus
}
#endif
#endif