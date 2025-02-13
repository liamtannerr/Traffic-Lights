#include "../Libraries/include/Initialization.h"

#include <stdint.h>
#include <stdio.h>
#include "stm32f4_discovery.h"
#include "stm32f4xx.h"
#include "../FreeRTOS_Source/include/FreeRTOS.h"
#include "../FreeRTOS_Source/include/queue.h"
#include "../FreeRTOS_Source/include/semphr.h"
#include "../FreeRTOS_Source/include/task.h"
#include "../FreeRTOS_Source/include/timers.h"

void GPIOC_Init(){

    GPIO_InitTypeDef GPIO_InitStruct;

    // Enable GPIOC clock (check if it's already enabled in your code)
    RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOC, ENABLE);

    // Configure GPIOC pins as output (except Pin 3)
    GPIO_InitStruct.GPIO_Pin = GPIO_Pin_0 |
    		GPIO_Pin_1 |
			GPIO_Pin_2 |
			GPIO_Pin_4 |
			GPIO_Pin_5 |
			GPIO_Pin_6 |
			GPIO_Pin_7 |
			GPIO_Pin_8 |
			GPIO_Pin_9 |
			GPIO_Pin_10 |
			GPIO_Pin_11 |
			GPIO_Pin_12;
    GPIO_InitStruct.GPIO_Mode = GPIO_Mode_OUT;
    GPIO_InitStruct.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_InitStruct.GPIO_OType = GPIO_OType_PP;
    GPIO_InitStruct.GPIO_PuPd = GPIO_PuPd_NOPULL;
    GPIO_Init(GPIOC, &GPIO_InitStruct);

   // Initialize Pin 3 as Input
    GPIO_InitStruct.GPIO_Pin = GPIO_Pin_3;
    GPIO_InitStruct.GPIO_Mode = GPIO_Mode_IN;
    GPIO_InitStruct.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_InitStruct.GPIO_PuPd = GPIO_PuPd_NOPULL;
    GPIO_Init(GPIOC, &GPIO_InitStruct);
}
