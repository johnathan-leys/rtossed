#include <stdio.h>
#include "progs.h"
#include "main.h"
#include "user_syscalls.h"
#include "stm32h7xx.h"  
#include "stm32h7a3xxq.h"

uint8_t iter = 0; //iterates in function, is printed to test locking

int process1(void)
{


	while (1) {

        //block so that function only runs if lock is open
        if(HAL_HSEM_Take(0, 0) == HAL_OK){  //process id is 0, semaphore id is 0... seems to work fine

        printf("%d\n\r", iter); 
        iter++; //should automatically roll over back to 0 past 255

		microsleep(250000);
		HAL_GPIO_TogglePin(LD1_GPIO_Port, LD1_Pin);	//toggle green LED
		microsleep(250000);
		HAL_GPIO_TogglePin(LD1_GPIO_Port, LD1_Pin);

        HAL_HSEM_Release(0,0); //release the lock
        }
        
    
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
