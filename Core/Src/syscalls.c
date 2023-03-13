
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
	uint8_t charStore;	//store UART char, use uint8_t instead of char for portability, avoid sing errors

	HAL_StatusTypeDef ok;
	while (1) {		//should stop exit
		ok = HAL_UART_Receive(&huart3, &charStore, 1, HAL_MAX_DELAY);	// pass ptr to huart3, store in charStore, 1 char, wait for max time allowed
        //above call should automatically block until recieiving char
		if (ok == HAL_OK) {
			*(uint8_t *) buf = charStore;	//cast buf as uint8_t and pass value of data in
			return 1;
		}
	}

	return -1;		//error

}
