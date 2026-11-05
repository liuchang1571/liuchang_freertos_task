//
// Created by admin on 2026/11/3.
//
#include"cmsis_os.h"
#include"can.h"
#include "CAN_bsp.h"

extern "C" {
uint8_t rx_caipan_buf[4]={0};
int16_t chassis_power=0;
int16_t energy_buf=0;
uint8_t caipan_flag=0;
}
extern "C"  void caipan_rx_callback(can_device_receive*dev,uint8_t*data) {
    rx_caipan_buf[0]=data[0];
    rx_caipan_buf[1]=data[1];
    rx_caipan_buf[2]=data[2];
    rx_caipan_buf[3]=data[3];
    caipan_flag=1;

}
void caipanTask(void*argument) {
    for (;;) {
        osDelay(10);
        if (caipan_flag==1) {
            caipan_flag=0;
            chassis_power=(int16_t)(rx_caipan_buf[0]|(rx_caipan_buf[1]<<8));
            energy_buf=(int16_t)(rx_caipan_buf[2]|(rx_caipan_buf[3]<<8));
        }
    }
}
extern "C" void caipanTaskInit(void){
    new can_device_receive(&hcan2,0x31,caipan_rx_callback);
    osThreadNew(caipanTask,NULL,NULL);
}