/* USER CODE BEGIN Header */
/**
******************************************************************************
  * @file    gpio.h
  * @brief   This file contains all the function prototypes for
  *          the syscalls.c file
  ******************************************************************************
    */
/* USER CODE END Header */
/* Define to prevent recursive inclusion -------------------------------------*/

#ifndef __SYSCALLS_H__
#define __SYSCALLS_H__

#ifdef __cplusplus
extern "C" {
#endif

//includes
#include "main.h"

//declare functions
int _write(int file, void *ptr, size_t len);

_ssize_t _write_r (struct _reent *ptr, int fd, const void *buf, size_t cnt);

_ssize_t _read_r(struct _reent *ptr, int fd, void *buf, size_t cnt);

#ifdef __cplusplus
}
#endif
#endif
