#ifndef _MAIN_H
#define _MAIN_H

#include "sys.h"
#include "delay.h"
#include "usart.h"
#include "led.h"
#include  "Lcd_Driver.h"
#include "GUI.h"
#include "rtc.h" 
#include "UI.h"
#include "stmflash.h"
#include "pwm_in.h"
//#define Debug_ 

#define DEBUG_(str,data,len) {\
	u8 data_i;\
	printf("data:%s  %d\r\n",__FILE__,__LINE__);\
	printf("%s ",str);\
	for(data_i=0;data_i<len;data_i++){\
	printf("%d ",data[data_i]);}\
	printf("%\r\n");\
	printf("%s 0x ",str);\
	for(data_i=0;data_i<len;data_i++){\
	printf("%02X ",data[data_i]);}\
	printf("%\r\n");}


#endif
