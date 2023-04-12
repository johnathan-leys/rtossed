#include <stdio.h>
#include "progs.h"
#include "main.h"
#include "user_syscalls.h"
#include "stm32h7xx.h"

//Define grabbed from STM examples as available ID number
//https://github.com/STMicroelectronics/STM32CubeH7
#define HSEM_ID (9U)		/* use HW semaphore 9 */

uint8_t iter = 0;		//iterates in function, is printed to test locking

int process1(void)
{

	while (1) {

		//block so that function only runs if lock is open
		if (HAL_HSEM_Take(HSEM_ID, current->pid) == HAL_OK) {
			//blocking

			printf("Current Process: %d | Value of iter:  %d\n\r",
			       current->pid, iter);
			iter++;	//should automatically roll over back to 0 past 255

			HAL_GPIO_TogglePin(LD1_GPIO_Port, LD1_Pin);	//toggle green LED
			HAL_HSEM_Release(HSEM_ID, current->pid);	//release the lock
			microsleep(1000);	//needs to come after the release to give time for 2nd process to acquire lock

		} else
			yield();	//give up process
		//Code stil "works" without yield, but delay seen on printing is much higher, process keeps trying lock         
	}
	return 1;
}

void process2(void)
{
	while (1) {
		microsleep(500000);	//delay to get 1hz, 2 toggles/sec)
		HAL_GPIO_TogglePin(LD2_GPIO_Port, LD2_Pin);	//toggle amber LED
		microsleep(500000);
		HAL_GPIO_TogglePin(LD2_GPIO_Port, LD2_Pin);
	}
}
