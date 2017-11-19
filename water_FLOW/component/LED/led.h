#ifndef __LED_H
#define __LED_H	 

#include "sys.h"
#include "delay.h"

#include "FreeRTOS.h"
#include "task.h"

#define LED_TASK_PRIO			3
#define LED_STK_SIZE			128

#define LED0 PBout(11)	// PB11
#define Relay PCout(4)	// PC4

extern TaskHandle_t LEDTask_Handler	;
extern float flow ; 

void LED_Init(void);		//初始化
void LED_task(void * pvParameters) ; //LED 任务
void Relay_Init(void) ; // 继电器         
		 				    
#endif
