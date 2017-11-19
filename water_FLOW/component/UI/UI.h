#ifndef _UI_H
#define _UI_H

#include "sys.h"
#include "FreeRTOS.h"
#include "task.h"
/*********************************************************/
#define Show_TASK_PRIO			3
#define Show_STK_SIZE				2048

extern TaskHandle_t 				ShowTask_Handler	;
void Show_task(void * pvParameters)		;
/*********************************************************/
typedef struct power
{
	u16 power;
	u16 amp;
	u16 power_h;
	u16 power_l;
	
}power;
typedef struct error_
{
	enum
	{
		tim_err=0,
	}type;
	enum
	{ 
		tim_h=0,
		tim_m=1,
		tim_s=2,
	}tim_;
}error_;

typedef struct cursor_
{
	u16 sx_h;
	u16 sy_h;
	u8 end_x_h;
	u8 end_y_h;
	u16 sx_m;
	u16 sy_m;
	u8 end_x_m;
	u8 end_y_m;
	u16 sx_l;
	u16 sy_l;
	u8 end_x_l;
	u8 end_y_l;
	
}cursor_;
typedef struct time_
{
u32 time_amp ;
u16 time_h;
u16 time_m;
u16 time_s;
}time_;

extern error_ err;
extern power plan;
extern power tmp_plan ;
extern power use;
extern time_ tim;
extern time_ tmp_tim ;
extern time_ timeing ;
extern time_ timeing_tmp ;
extern u8  show_Refresh  ;
extern cursor_ plan_coord,use_coord,time_coord;

void cursor(void);
void clear_cursor(void) ;
void Show_plan(void);
void Show_use(void) ;
void Show_timing(void) ;
void Show_time(time_ tim);
void time_show(void);
#endif
