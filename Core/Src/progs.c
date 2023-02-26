#include "progs.h"
#include "main.h"
#include "user_syscalls.h"

int process1(void)
{
	while (1) {
		microsleep(250000);
		HAL_GPIO_TogglePin(LD1_GPIO_Port, LD1_Pin);	//toggle green LED
		microsleep(250000);
		HAL_GPIO_TogglePin(LD1_GPIO_Port, LD1_Pin);
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
