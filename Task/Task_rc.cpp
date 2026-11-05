//
// Created by admin on 2026/11/3.
//
#include"cmsis_os.h"
#include"usart.h"
#include<string.h>
extern UART_HandleTypeDef huart3;
extern "C" {
uint8_t rc_buf[18]={0};
uint8_t rc_task_buf[18]={0};
int16_t rc_ch[4]={1024,1024,1024,1024};
uint8_t rc_s1=0;
uint8_t rc_s2=0;
volatile uint8_t flag=0;
}
void RcTask(void *argument) {
    for (;;) {
     osDelay(5);
        if (flag==1) {
            flag=0;
            rc_ch[0]=((rc_task_buf[0]|(rc_task_buf[1]<<8))&0x07FF);
            rc_ch[1]=((rc_task_buf[1]>>3|(rc_task_buf[2]<<5))&0x07FF);
            rc_ch[2]=((rc_task_buf[2]>>6|(rc_task_buf[3]<<2|(rc_task_buf[4]<<10))&0x07FF));
            rc_ch[3]=((rc_task_buf[4]>>1|(rc_task_buf[5]<<7))&0x07FF);
            rc_s1=(rc_task_buf[5]>>4)&0x03;
            rc_s2=(rc_task_buf[5]>>6)&0x03;
        }
    }
}
extern "C" void RcTaskInit(void) {
    HAL_UART_Receive_DMA(&huart3,rc_buf,18);
    __HAL_UART_ENABLE_IT(&huart3,UART_IT_IDLE);
    osThreadNew(RcTask,NULL,NULL);
}
