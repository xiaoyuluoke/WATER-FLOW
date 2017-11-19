#ifndef _TIMER_PWM_IN_H_
#define _TIMER_PWM_IN_H_

#include "main.h"

extern u32	_VAL; 
void TIM3_PWM_Init(u16 arr,u16 psc);
void TIM5_IN_Init(u16 arr,u16 psc) ;
void TIM5_IRQHandler(void) ;
void TIM3_Int_Init(u16 arr,u16 psc) ;
#endif
