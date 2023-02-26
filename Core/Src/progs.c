#include "progs.h"
#include "main.h"

int process1(void)
{
	while (1) {
		HAL_Delay(250);	//delay to get 2hz, 4 toggles/sec)
		HAL_GPIO_TogglePin(LD1_GPIO_Port, LD1_Pin);	//toggle green LED
		HAL_Delay(250);
		HAL_GPIO_TogglePin(LD1_GPIO_Port, LD1_Pin);
	}
    return 1;
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
