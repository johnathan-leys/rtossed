/* USER CODE BEGIN Header */
/**
******************************************************************************
  * @file    user_syscalls.h
  * @brief   This file contains all the function prototypes for
  *          the user_syscalls.c file
  ******************************************************************************
    */
/* USER CODE END Header */
/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __USER_SYSCALLS_H__
#define __USER_SYSCALLS_H__

#ifdef __cplusplus
extern "C" {
#endif
//begin user code--------
#include "stm32h7xx_it.h"
#include "process.h"
#include <stdint.h>

//extern task_struct *current;
uint32_t microsleep(uint32_t);






//-----------
#ifdef __cplusplus
}
#endif
#endif