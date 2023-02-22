/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file    sh.h
  * @brief   This file contains the headers of the sh.c
  ******************************************************************************
  * @attention
  *
  * Copyright (c) 2023 STMicroelectronics.
  * All rights reserved.
  *
  * This software is licensed under terms that can be found in the LICENSE file
  * in the root directory of this software component.
  * If no LICENSE file comes with this software, it is provided AS-IS.
  *
 ******************************************************************************
  */
/* USER CODE END Header */

/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __SH_H
#define __SH_H

#ifdef __cplusplus
extern "C" {
#endif
//Begin user code-------

	int sh(void);		//single threaded process shell

	int sh_getline(char *inputLine);

//End user code-------
#ifdef __cplusplus
}
#endif
#endif				/* sh */
