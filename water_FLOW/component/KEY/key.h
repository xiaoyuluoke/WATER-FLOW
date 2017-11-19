#ifndef __KEY_H
#define __KEY_H	 
#include "sys.h"
#include "UI.h"
#include "FreeRTOS.h"
#include "task.h"

/*********************************************************/
#define Key_TASK_PRIO			4
#define Key_STK_SIZE			1024

extern TaskHandle_t 				KeyTask_Handler	;
void Key_task(void * pvParameters) ;
/*********************************************************/
#define Set_key1   GPIO_ReadInputDataBit(GPIOA,GPIO_Pin_4)//读取按键1
#define OK_key2    GPIO_ReadInputDataBit(GPIOA,GPIO_Pin_5)//读取按键2
#define Add_key3   GPIO_ReadInputDataBit(GPIOA,GPIO_Pin_6)//读取按键3 
#define Down_key4  GPIO_ReadInputDataBit(GPIOA,GPIO_Pin_7)//读取按键4
#define KEY5	GPIO_ReadInputDataBit(GPIOA,GPIO_Pin_0)//读取按键5 
typedef enum 
{
	Set_key = 0,
	OK_key  = 1,
	Add_key = 2,
	Down_key= 3,
}key_;
typedef struct key_cnt_
{
	s16    cnt   ;
	power  plan  ;
	time_  time  ;
	time_  timeing ;
	s16  set  ;
	s16  ok   ;
}key_cnt_;
typedef enum 
{
	key_no=0,
	key_yes=1,
}key_flag_;

void KEY_Init(void);//IO初始化
void key_scan(void) ;
extern key_ key;
extern key_flag_ key_flag;	
extern key_cnt_ key_cnt ;		    
#endif
