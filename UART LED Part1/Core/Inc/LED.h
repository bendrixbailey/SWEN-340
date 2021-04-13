#ifndef __NUCLEO476_LED_H
#define __NUCLEO476_LED_H

#include "stm32l476xx.h"

void GPIO_Output_Init(GPIO_TypeDef*, uint32_t);
void LED_Init(void);
void LED_r_Off(void);
void LED_r_On(void);
void LED_g_Off(void);
void LED_g_On(void);
void LED_Toggle_R(void);
void LED_Toggle_G(void);

#endif /* __NUCLEO476_LED_H */
