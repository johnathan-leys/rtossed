#include "progs.h"
#include "main.h"
//TODO write the code
//Place user space process code in progs.c
void process1(void)
{
	while (1) {
		HAL_Delay(250);	//delay to get 2hz, 4 toggles/sec)
		HAL_GPIO_TogglePin(LD1_GPIO_Port, LD1_Pin);	//toggle green LED
		HAL_Delay(250);
		HAL_GPIO_TogglePin(LD1_GPIO_Port, LD1_Pin);
	}
}

void process2(void)
{
	while (1) {
		HAL_Delay(500);	//delay to get 1hz, 2 toggles/sec)
		HAL_GPIO_TogglePin(LD2_GPIO_Port, LD2_Pin);	//toggle amber LED
		HAL_Delay(500);
		HAL_GPIO_TogglePin(LD2_GPIO_Port, LD2_Pin);
	}
}
