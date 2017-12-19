#include "led.h"
#include "pwm_in.h"
/*********************************************************

初始化PB11出口.并使能这个口的时钟		    
LED IO初始化

**********************************************************/

TaskHandle_t LEDTask_Handler	;

void LED_Init(void)
{
 
 GPIO_InitTypeDef  GPIO_InitStructure;
 	
 RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB, ENABLE);	 //使能PB
	
 GPIO_InitStructure.GPIO_Pin = GPIO_Pin_11;					//LED0-->PB.11 端口配置
 GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP; 	//推挽输出
 GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;	//IO口速度为50MHz
 GPIO_Init(GPIOB, &GPIO_InitStructure);					 		//根据设定参数初始化GPIOB.11
 GPIO_SetBits(GPIOB,GPIO_Pin_11);										//PB.11 输出高

 }
 
/*********************************************************

**********************************************************/
void Relay_Init(void)
{
 
 GPIO_InitTypeDef  GPIO_InitStructure;
 	
 RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOC, ENABLE);	 //使能C4
	
 GPIO_InitStructure.GPIO_Pin = GPIO_Pin_4;					//Relay-->PC.4端口配置
 GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_OD; 			//上拉输出
 GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;	//IO口速度为50MHz
 GPIO_Init(GPIOC, &GPIO_InitStructure);					 		//根据设定参数初始化GPIOB.11
 GPIO_SetBits(GPIOC,GPIO_Pin_4);										//PC.4 输出高

 }
/*********************************************************

**********************************************************/
float flow ;
/*********************************************************/
float Flow_(void)
{
	float k = 830.25f ;
	float v_flow ;
	float kT ;
	float ts =100*1000;

//	float VAL_[3];
//	assert(_VAL);
	if(show_Refresh)
		{
			if(_VAL != 0)
			{
				kT = k*_VAL ;
				v_flow = ts/(kT) ;
				flow += v_flow ;
				return flow ;
			}
		}
	else
	return flow ;
}
 /********************************************************/
void LED_task(void * pvParameters)
{
	u8 i = 0 ;
	while(1)
	{
		LED0=0;
		vTaskDelay(500);
		LED0=1;
		
		vTaskDelay(500);if(i == 50){i = 0 ;}
//		a = TIM_GetCapture3(TIM3);
//		printf("pwm%d\r\n",a);
		printf("PWM:%e L\r\n",Flow_());
		i ++ ;
	}
}
