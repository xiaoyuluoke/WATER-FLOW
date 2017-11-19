#include "main.h"
#include "key.h"
#include "UI.h"

#include "FreeRTOS.h"
#include "task.h"
/************************************************

*************************************************/
#define START_TASK_PRIO			1
#define START_STK_SIZE			128
TaskHandle_t 				startTask_Handler	;
void start_task(void * pvParameters)	;

#define FLASH_SAVE_ADDR  0X08070000	
/************************************************
开始任务
	创建其他任务
*************************************************/
void start_task(void * pvParameters)
{
	taskENTER_CRITICAL()	;
	
	xTaskCreate((TaskFunction_t		)LED_task,
							(const char *			)"LED_task",
							(uint16_t					)LED_STK_SIZE,
							(void*						)NULL,
							(UBaseType_t			)LED_TASK_PRIO,
							(TaskHandle_t*		)&LEDTask_Handler);
							
	xTaskCreate((TaskFunction_t		)Show_task,
							(const char *			)"Show_task",
							(uint16_t					)Show_STK_SIZE,
							(void*						)NULL,
							(UBaseType_t			)Show_TASK_PRIO,
							(TaskHandle_t*		)&ShowTask_Handler);
							
	xTaskCreate((TaskFunction_t		)Key_task,
							(const char *			)"Key_task",
							(uint16_t					)Key_STK_SIZE,
							(void*						)NULL,
							(UBaseType_t			)Key_TASK_PRIO,
							(TaskHandle_t*		)&KeyTask_Handler);
	vTaskDelete(startTask_Handler);	
	taskEXIT_CRITICAL();
}

/************************************************
_init_ 初始化
	初始化所有配置

************************************************/
void _init_(void)
{
	taskENTER_CRITICAL()	;
	
	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_4); 
	KEY_Init();
	Relay_Init();
	delay_init();	    //延时函数初始化	  
	LED_Init();		  	//LED初始化
	uart_init(115200);
	Lcd_Init();
	RTC_Init();
	delay_ms(300);
	printf("AT+CONA341513CD76A9\r\n");//连接蓝牙设备
	TIM3_PWM_Init(999,72-1);
	delay_ms(1000);
	TIM5_IN_Init(0XFFFF,720-1);
	printf("water flow working !\r\n");

	Lcd_Clear( BLACK );

	tim.time_h =calendar.hour;
	tim.time_m = calendar.min;
	tim.time_s = calendar.sec; 
	
	Show_plan();
	Show_use();
	Show_timing();
	Show_time(tim);
	
	taskEXIT_CRITICAL();

}

/*********************************************************

main:
	主线程：

**********************************************************/
 int main(void)
 {	
	_init_();
	
	xTaskCreate((TaskFunction_t		)start_task,
							(const char *			)"start_task",
							(uint16_t					)START_STK_SIZE,
							(void*						)NULL,
							(UBaseType_t			)START_TASK_PRIO,
							(TaskHandle_t*		)&startTask_Handler);
	vTaskStartScheduler();
	
 }
