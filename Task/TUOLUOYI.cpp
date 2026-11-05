//
// Created by admin on 2026/11/2.
//
#include"cmsis_os.h"
extern "C" {
#include "ins_task.h"
}
void TUOLUOYITask(void *argument) {

    uint32_t tick=osKernelGetTickCount();
    float t=0;
    for (;;) {
       INS_Task();
        tick=tick+2;
        osDelayUntil(tick);
    }
}
extern "C" void TUOLUOYITaskInit(void) {
    osThreadNew(TUOLUOYITask,NULL,NULL);
}