#include "stm32f10x.h"
#include "key.h"
#include "sys.h" 
#include "delay.h"
#include "stdio.h"
#include "main.h"
/*********************************************************

按键初始化函数

**********************************************************/

key_ key;
key_flag_ key_flag;
key_flag_ Set_key_state;
key_cnt_ key_cnt={0,0,0,};
/*********************************************************/

TaskHandle_t 				KeyTask_Handler	;
/*********************************************************
按键初始化：
	A4：设置按键
		A5：确认按键
			A6：增加按键
				A7：减少按键
**********************************************************/
void KEY_Init(void) //IO初始化
{ 
 	GPIO_InitTypeDef GPIO_InitStructure;
	
 	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA,ENABLE);//使能PORTA,PORTE时钟
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_AFIO,ENABLE);	//使能复用功能时钟
	
	
	GPIO_InitStructure.GPIO_Pin  = GPIO_Pin_4|GPIO_Pin_5|GPIO_Pin_6|GPIO_Pin_7;//KEY0-KEY2
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPD; //设置成下拉输入
 	GPIO_Init(GPIOA, &GPIO_InitStructure);//初始化GPIOA4,5,6,7
	
}
/*********************************************************

**********************************************************/
void key_scan(void)
{
		if((Set_key1==1) || (Add_key3==1)\
			||(Down_key4==1) || (OK_key2==1))	 	 //设置按键
		{		

			delay_ms(10);//消抖
			if(Set_key1==1)
				{	
				  show_Refresh = 0 ;
					if(key_cnt.set >= 7){key_cnt.set = -1;}
					key_flag=key_yes;
					key_cnt.set ++ ;
				}
						
			else if(Add_key3==1) //增加按键
			 {
				 show_Refresh = 0 ;
				 if(key_cnt.cnt >= 100){key_cnt.cnt = -1;}
				 key_flag=key_yes;
				 key_cnt.cnt ++ ;
				 if(key_cnt.set == 1)
				{
					key_cnt.plan.power_h = tmp_plan.power_h;
					if(key_cnt.plan.power_h >= 100){key_cnt.plan.power_h = 0 ;}
					key_cnt.plan.power_h  ++ ;
					tmp_plan.power_h =  key_cnt.plan.power_h;
				}
				if(key_cnt.set == 2)
				{
					key_cnt.plan.power_l = tmp_plan.power_l/10;
					if(key_cnt.plan.power_l >= 100){key_cnt.plan.power_l = 0 ;}			
					key_cnt.plan.power_l  ++ ;
					tmp_plan.power_l = key_cnt.plan.power_l*10 ;
				}
				if(key_cnt.set == 5)
				{
				  key_cnt.time.time_h = tmp_tim.time_h ;
					if(key_cnt.time.time_h >= 24){key_cnt.time.time_h = 0 ;}
					key_cnt.time.time_h ++ ;
					tmp_tim.time_h = key_cnt.time.time_h ;
				}
				if(key_cnt.set == 6)
				{
				  key_cnt.time.time_m = tmp_tim.time_m ;
					if(key_cnt.time.time_m >= 60){key_cnt.time.time_m = 0 ;}
					key_cnt.time.time_m ++ ;
					tmp_tim.time_m = key_cnt.time.time_m ;
				}
				if(key_cnt.set == 7)
				{
				  key_cnt.time.time_s = tmp_tim.time_s ;
					if(key_cnt.time.time_s >= 60){key_cnt.time.time_s = 0 ;}
					key_cnt.time.time_s ++ ;
					tmp_tim.time_s =  key_cnt.time.time_s;
				}
				if(key_cnt.set == 3)
				{
					key_cnt.timeing.time_h = timeing_tmp.time_h  ;
					if(key_cnt.timeing.time_h >= 24){key_cnt.timeing.time_h = 0 ;}
					key_cnt.timeing.time_h ++ ;
					timeing_tmp.time_h  = key_cnt.timeing.time_h ;
				}
				if(key_cnt.set == 4)
				{
					key_cnt.timeing.time_m = timeing_tmp.time_m  ;
					if(key_cnt.timeing.time_m >= 60){key_cnt.timeing.time_m = 0 ;}
					key_cnt.timeing.time_m ++ ;
					timeing_tmp.time_m  = key_cnt.timeing.time_m ;
				}

			 } 
			else if(Down_key4==1) //减少按键
			 {
				show_Refresh = 0 ;
				if(key_cnt.cnt <= 0){key_cnt.cnt = 100;}
				key_flag=key_yes;
				key_cnt.cnt -- ;
				
				if(key_cnt.set == 1)
				{
				  key_cnt.plan.power_h = tmp_plan.power_h ;
					if(key_cnt.plan.power_h <= 0){key_cnt.plan.power_h = 100 ;}
					key_cnt.plan.power_h  -- ;
					tmp_plan.power_h  = key_cnt.plan.power_h ;
				}
				if(key_cnt.set == 2)
				{
					key_cnt.plan.power_l = tmp_plan.power_l/10 ;
					if(key_cnt.plan.power_l <= 0){key_cnt.plan.power_l = 100 ;}			
					key_cnt.plan.power_l  -- ;
					tmp_plan.power_l = key_cnt.plan.power_l*10 ;
				}
				if(key_cnt.set == 5)
				{
					key_cnt.time.time_h = tmp_tim.time_h ;
					if(key_cnt.time.time_h <= 0){key_cnt.time.time_h = 24 ;}
					key_cnt.time.time_h -- ;
					tmp_tim.time_h = key_cnt.time.time_h ;
				}
				if(key_cnt.set == 6)
				{
					key_cnt.time.time_m = tmp_tim.time_m ;
					if(key_cnt.time.time_m <= 0){key_cnt.time.time_m = 60 ;}
					key_cnt.time.time_m -- ;
					tmp_tim.time_m = key_cnt.time.time_m ;
				}
				if(key_cnt.set == 7)
				{
					key_cnt.time.time_s = tmp_tim.time_s ;
					if(key_cnt.time.time_s <= 0){key_cnt.time.time_s = 60 ;}
					key_cnt.time.time_s -- ;
					tmp_tim.time_s = key_cnt.time.time_s ;
				}
				
				if(key_cnt.set == 3)
				{
					key_cnt.timeing.time_h = timeing_tmp.time_h  ;
					if(key_cnt.timeing.time_h <= 0){key_cnt.timeing.time_h = 24 ;}
					key_cnt.timeing.time_h -- ;
					timeing_tmp.time_h  = key_cnt.timeing.time_h ;
				}
				if(key_cnt.set == 4)
				{
					key_cnt.timeing.time_m = timeing_tmp.time_m  ;
					if(key_cnt.timeing.time_m <= 0){key_cnt.timeing.time_m = 60 ;}
					key_cnt.timeing.time_m -- ;
					timeing_tmp.time_m  = key_cnt.timeing.time_m ;
				}

			 }
			else if(OK_key2==1) //确认按键
			 { 
					key_flag = key_yes;
					key_cnt.ok = OK_key2 ;	
					
					plan.power_h = tmp_plan.power_h ;
					plan.power_l = tmp_plan.power_l ;
					plan.amp = plan.power_h*1000 + plan.power_l ;
					
					timeing.time_h = timeing_tmp.time_h ;
					timeing.time_m = timeing_tmp.time_m ;
					timeing.time_s = timeing_tmp.time_s ;		
					timeing.time_amp = timeing.time_h *100*100 \
						+timeing.time_m*100+timeing.time_s ; ;
					
					show_Refresh = 1 ;
					clear_cursor(); 					
				}
			 
			}
		 else 
		 {key_flag = key_no;}
	 cursor();
}
/*********************************************************
按键任务
	处理按键和按键响应
**********************************************************/
void Key_task(void * pvParameters)
{
	while(1)
	{ 
		vTaskDelay(200);
    key_scan();
 

	}	 
}


