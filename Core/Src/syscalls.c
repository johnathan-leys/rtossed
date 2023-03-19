
//Includes
#include "syscalls.h"
#include "usart.h"		//has huart3 defined
#include "process.h"

task_struct *IO_wait = NULL;

int _write(int file, void *ptr, size_t len)
{
	// Transmit printf string to USART - blocking call
	HAL_UART_Transmit(&huart3, (uint8_t *) ptr, len, 10000);	
	return len;
}

_ssize_t _write_r(struct _reent *ptr, int fd, const void *buf, size_t cnt)
{
	return _write(fd, (char *)buf, cnt);	//get write 
}

_ssize_t _read_r(struct _reent *ptr, int fd, void *buf, size_t cnt)
{	
	if(cnt == 0){ //return if count is zero
		return 0;
	}
	
	
	HAL_UART_Receive_IT(&huart3, (uint8_t*)buf, 1);//interrupt bases hal uart receive
	

	current->state |= io_sleep; //mask to change states to sleep
	current->state &= ~run;

	IO_wait =  current; //set IO wait to current process

	yield();

	return -1;// yield should prevent

}

void HAL_UART_RxCpltCallback(UART_HandleTypeDef * huart)//doesnt look like it ever gets called... used GDB and prints
{
	IO_wait->state |= run;
	IO_wait->state &= ~io_sleep;
	yield();
}
