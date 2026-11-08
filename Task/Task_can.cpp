//
// Created by admin on 2026/11/3.
//
#include"cmsis_os.h"
#include"can.h"
#include "CAN_bsp.h"

extern "C" {
uint8_t rx_can_buf[4]={0};
int16_t chassis_power=0;
int16_t energy_buf=0;
uint8_t can_flag=0;
}
extern "C"  void can08_rx_callback(can_device_receive*dev,uint8_t*data) {
    rx_can_buf[0]=data[0];
    rx_can_buf[1]=data[1];
    rx_can_buf[2]=data[2];
    rx_can_buf[3]=data[3];
    can_flag=1;

}
extern "C" void CanTask08(void*argument) {
    new can_device_receive(&hcan1,0x31, can08_rx_callback);
    for (;;) {
        osDelay(10);
        if (can_flag==1) {
            can_flag=0;
            chassis_power=(int16_t)(rx_can_buf[0]|(rx_can_buf[1]<<8));
            energy_buf=(int16_t)(rx_can_buf[2]|(rx_can_buf[3]<<8));
        }
    }
}
