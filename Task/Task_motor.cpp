//
// Created by admin on 2026/11/2.
//
#include<math.h>
#include"cmsis_os.h"
#include"DJI_motor_driver.h"
extern CAN_HandleTypeDef hcan1;


extern "C" void MotorTask05(void *argument) {
    DJI_motor *m=new DJI_motor(&hcan1,NULL,5,DJI_M3508,0);
    uint32_t tick=osKernelGetTickCount();
    float t=0;
    for (;;) {
        float target_round=1.0f*sinf(6.283f*0.5f*t);
        m->motor_set_rounds(target_round);
        t=t+0.001f;
        tick=tick+1;
        osDelayUntil(tick);
    }
}

