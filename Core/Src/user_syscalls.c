#include "user_syscalls.h"



uint32_t microsleep(uint32_t sleep_time){
    current->w_time = sleep_time + (uwTick * 1000); //set wake time based on sleep time, change uwTick to micro
    current->state = current->state | time_sleep; //change state to sleep, 0x01

    return 1; //tmp "The function returns the amount of time left to sleep (ignore this for now)"

}
