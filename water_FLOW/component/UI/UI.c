#include "UI.h"
#include "main.h"
#include "key.h"

/*********************************************************/
TaskHandle_t 				ShowTask_Handler	;
/*********************************************************/
error_ err;
power plan ;
power tmp_plan ;
power use  ;
power tmp_use;
time_ timeing ;
time_ timeing_tmp ;
time_ tim  ;
time_ tmp_tim ;
u8 show_Refresh = 1 ;
cursor_ plan_coord,use_coord,time_coord ,timeing_coord;
/*********************************************************/
void Show_task(void * pvParameters)
{
	while(1)
	{
		if(use.amp < plan.amp )
		{
			use.power_h = (u16)flow /1000 ;
			use.power_l = (u16)flow %1000 ;
			use.amp = use.power_h*1000 + use.power_l ; 
			Relay = 0;
		}
		else {	Relay = 1;}
		if( tim.time_amp == timeing.time_amp)
		{flow = 0;use.amp =0 ; Relay = 0;}
		if(show_Refresh){Show_use();}
		time_show();
		vTaskDelay(850);
		}
}
/********************************************************/
void clear_cursor(void)
{
//	Gui_DrawLine(plan_coord.sx_h , 
//		plan_coord.sy_h ,
//		plan_coord.end_x_h ,
//		plan_coord.end_y_h ,BLACK);
//		
//	Gui_DrawLine(plan_coord.sx_l ,  
//		plan_coord.sy_l ,
//		plan_coord.end_x_l ,
//		plan_coord.end_y_l ,BLACK);

//	Gui_DrawLine(use_coord.sx_h , 
//		timeing_coord.sy_h ,
//		timeing_coord.end_x_h ,
//		timeing_coord.end_y_h ,BLACK);
//		
//	Gui_DrawLine(use_coord.sx_l , 
//		timeing_coord.sy_l ,
//		timeing_coord.end_x_l ,
//		timeing_coord.end_y_l ,BLACK);

//	Gui_DrawLine(time_coord.sx_h , 
//		time_coord.sy_h ,
//		time_coord.end_x_h ,
//		time_coord.end_y_h ,BLACK);
//		
//	Gui_DrawLine(time_coord.sx_m , 
//		time_coord.sy_m ,
//		time_coord.end_x_m ,
//		time_coord.end_y_m ,BLACK);
//		
//	Gui_DrawLine(time_coord.sx_l , 
//		time_coord.sy_l ,
//		time_coord.end_x_l ,
//		time_coord.end_y_l ,BLACK);
			
//	Show_plan();
//	Show_use();
//	Show_timing();
//	Show_time(tmp_tim);
	
	LCD_ShowxNum(plan_coord.sx_h,
		plan_coord.sy_h-24,
		plan.power_h,2,24,128);
	LCD_ShowxNum(plan_coord.sx_l,
		plan_coord.sy_l-24,
		plan.power_l ,3,24,128);
		
	LCD_ShowxNum(timeing_coord.sx_h,
		timeing_coord.sy_h-24,
		timeing.time_h ,2,24,128);
	LCD_ShowxNum(timeing_coord.sx_l,
		timeing_coord.sy_l-24,
		timeing.time_m,2,24,128);

	show_num_32(time_coord.sx_h-10,
		time_coord.sy_h-35,
		GREEN,
		tim.time_h);
	show_num_32(time_coord.sx_m-10,
		time_coord.sy_m-35,
		GREEN,
		tmp_tim.time_m);
	show_num_32(time_coord.sx_l-10,
		time_coord.sy_l-35,
		GREEN,
		tim.time_s);				
		
}
/********************************************************/
void cursor(void)
{

if(key_flag && (show_Refresh == 0))
{
 clear_cursor();
 switch(key_cnt.set)
 {
		case 1 :
			{
				LCD_ShowxNum_(plan_coord.sx_h,
					plan_coord.sy_h-24,
					tmp_plan.power_h,2,RED,24,128);//整数
//				Gui_DrawLine(plan_coord.sx_h , 
//					plan_coord.sy_h ,
//					plan_coord.end_x_h ,
//					plan_coord.end_y_h ,RED);
			}
			break ;
			
		case 2 :
				LCD_ShowxNum_(plan_coord.sx_l,
					plan_coord.sy_l-24,
					tmp_plan.power_l ,3,RED,24,128);//小数			
//				Gui_DrawLine(plan_coord.sx_l ,  
//					plan_coord.sy_l ,
//					plan_coord.end_x_l ,
//					plan_coord.end_y_l ,RED);
			break ;
			
		case 3 :
				LCD_ShowxNum_(timeing_coord.sx_h,
					timeing_coord.sy_h-24,
					timeing_tmp.time_h ,2,RED,24,128);//整数
//				Gui_DrawLine(timeing_coord.sx_h , 
//					timeing_coord.sy_h ,
//					timeing_coord.end_x_h ,
//					timeing_coord.end_y_h ,RED);
				break ;
						
		case 4 :
				LCD_ShowxNum_(timeing_coord.sx_l,
					timeing_coord.sy_l-24,
					timeing_tmp.time_m,2,RED,24,128);//小数
//				Gui_DrawLine(timeing_coord.sx_l , 
//					timeing_coord.sy_l ,
//					timeing_coord.end_x_l ,
//					timeing_coord.end_y_l ,RED);
						break ;
		case 5 :
				show_num_32(time_coord.sx_h-10,
					time_coord.sy_h-35,
					RED,
					tmp_tim.time_h);
				RTC_Set(2017,9,23,
					tmp_tim.time_h,
					calendar.min,
					calendar.sec);
//				Gui_DrawLine(time_coord.sx_h , 
//					time_coord.sy_h ,
//					time_coord.end_x_h ,
//					time_coord.end_y_h ,RED);
						break ;
		case 6 :
				show_num_32(time_coord.sx_m-10,
					time_coord.sy_m-35,
					RED,
					tmp_tim.time_m);
				RTC_Set(2017,9,23,
					calendar.hour,
					tmp_tim.time_m,
					calendar.sec);
//				Gui_DrawLine(time_coord.sx_m , 
//					time_coord.sy_m ,
//					time_coord.end_x_m ,
//					time_coord.end_y_m ,RED);
						break ;
						
		case 7 :
				show_num_32(time_coord.sx_l-10,
					time_coord.sy_l-35,
					RED,
					tmp_tim.time_s);
				RTC_Set(2017,9,23,
					calendar.hour,
					calendar.min,
					tmp_tim.time_s);
//				Gui_DrawLine(time_coord.sx_l , 
//					time_coord.sy_l ,
//					time_coord.end_x_l ,
//					time_coord.end_y_l ,RED);
						break ;
						
			default:
				break ;
	}
	key_flag=key_no;
 }
}
/*********************************************************/
void Show_plan(void)
{
	char str1[50];
  char str3[50];
	u8 sx,sy;
	 
	sprintf(str1,"定量");
	sx = 20;sy = 10;
	Gui_DrawFont_GBK24(sx,sy,GREEN,BLACK,(u8 *)str1);//汉字
	sx += 24*2;sy = 10;
	LCD_ShowChar(sx,10,':',24,0);//:
	sx += 24; sy = 10; 

	LCD_ShowxNum(sx,sy,plan.power_h,2,24,128);//整数
  plan_coord.sx_h = sx;plan_coord.sy_h = sy+24;
	plan_coord.end_x_h = sx+12*2;plan_coord.end_y_h = sy+24;
	sx += 12*2;sy = 10;
	LCD_ShowChar(sx,sy,'.',24,0);//小数点
	sx += 12; sy = 10;

	LCD_ShowxNum(sx,sy,plan.power_l ,3,24,128);//小数
	plan_coord.sx_l = sx;plan_coord.sy_l =sy+24;
	plan_coord.end_x_l = sx+12*3;plan_coord.end_y_l = sy+24;
	sprintf(str3,"m3");
	sx += 12*3;sx += 10; sy += 10;
	Gui_DrawFont_GBK24(sx,sy,GREEN,BLACK,(u8 *)str3);//m3
}
/*********************************************************/
void Show_use(void)
{
  char str2[50];
  char str3[50];
	u8 sx,sy;
	
	sprintf(str2,"已用");
	sx = 20; sy = 50;
	Gui_DrawFont_GBK24(sx,sy,GREEN,BLACK,(u8 *)str2);
	sx += 24*2;
	LCD_ShowChar(sx,sy,':',24,0);//:
	sx += 24;

	LCD_ShowxNum(sx,sy,use.power_h,2,24,128);//整数
	use_coord.sx_h = sx;use_coord.sy_h = sy+24;
	use_coord.end_x_h = sx+12*2;use_coord.end_y_h = sy+24;
	sx +=12*2;
	LCD_ShowChar(sx,sy,'.',24,0);//小数点
	sx += 12;
	LCD_ShowxNum(sx,sy,use.power_l,3,24,128);//小数
	use_coord.sx_l = sx;use_coord.sy_l = sy+24;
	use_coord.end_x_l = sx+12*3;use_coord.end_y_l = sy+24;
	sprintf(str3,"m3");
	sx += 12*3;sx +=10; sy +=10;
	Gui_DrawFont_GBK24(sx,sy,GREEN,BLACK,(u8 *)str3);//m3
	

}
/*********************************************************/
void Show_timing(void)
{
  char str2[50];
	u8 sx,sy;
	
	sprintf(str2,"定时");
	sx = 20; sy = 80;
	Gui_DrawFont_GBK24(sx,sy,GREEN,BLACK,(u8 *)str2);
	sx += 24*2;
	LCD_ShowChar(sx,sy,':',24,0);//:
	sx += 24;

	LCD_ShowxNum(sx,sy,timeing.time_h ,2,24,128);//整数
	timeing_coord.sx_h = sx;timeing_coord.sy_h = sy+24;
	timeing_coord.end_x_h = sx+12*2;timeing_coord.end_y_h = sy+24;
	sx +=12*2;
	LCD_ShowChar(sx,sy,':',24,0);//小数点
	sx += 12;
	LCD_ShowxNum(sx,sy,timeing.time_m ,2,24,128);//小数

	timeing_coord.sx_l = sx;timeing_coord.sy_l = sy+24;
	timeing_coord.end_x_l = sx+12*3;timeing_coord.end_y_l = sy+24;
}
/*********************************************************/
void Show_time(time_ tim)
{

	u8 sx,sy;
	sx =10;sy=120;
	
	if(tim.time_h <=24)
	{
	  show_num_32(sx,sy,GREEN,tim.time_h);
		
	}
	 else
	 {
	  err.type = tim_err;
		err.tim_ =tim_h;
#ifdef Debug_
		printf("time set hour error\r\n");
#endif
	 }
	time_coord.sx_h = sx+10;time_coord.sy_h = sy+35;
	time_coord.end_x_h = sx+24*2;time_coord.end_y_h = sy+35;
	sx += 24*2;sx +=12;
	
	LCD_ShowChar(sx,sy,':',24,1);//:
	sx +=16;
  if(tim.time_m <=60)
	{
	  show_num_32(sx,sy,GREEN,tim.time_m);
		
	 }
	 else
	 {
	  err.type = tim_err;
		err.tim_ =tim_m;
		printf("time set minute error\r\n");
	 }
	time_coord.sx_m = sx+10;time_coord.sy_m =sy+35;
	time_coord.end_x_m = sx+24*2;time_coord.end_y_m = sy+35;
	sx += 24*2;
	LCD_ShowChar(sx,sy,':',24,1);//:
	
	sx +=16;
	if(tim.time_s <=60)
	{
	  show_num_32(sx,sy,GREEN,tim.time_s);
		
	 }
	 else
	 {
	  err.type = tim_err;
		err.tim_ =tim_s;
		printf("time set second error\r\n");
	 }
	time_coord.sx_l =sx+10;time_coord.sy_l =sy+35 ;
	time_coord.end_x_l =sx+24*2;time_coord.end_y_l = sy+35;
	sx += 24*2 ;
}
/*********************************************************/
void time_show(void)
{
  if(show_Refresh)
	{

		tim.time_h =	tmp_tim.time_h = calendar.hour ;
		tim.time_m =	tmp_tim.time_m = calendar.min  ;
		tim.time_s =	tmp_tim.time_s = calendar.sec  ;
		tim.time_amp = tim.time_h *100*100 +tim.time_m*100 +tim.time_s ;
		
		Show_time(tim);
	}

}
