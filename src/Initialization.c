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

    // Enable GPIOC clock
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

void TIM1_Init(){


	// Prescaler and period make it so that it triggers every 100ms
	TIM_TimeBaseInitTypeDef TIM1_InitStruct;
	TIM1_InitStruct.TIM_Prescaler = 0xD; // figure out what clock is
	TIM1_InitStruct.TIM_CounterMode = TIM_CounterMode_Up;
	TIM1_InitStruct.TIM_Period = 0xFFFF; // 100ms if that's what it is
	TIM1_InitStruct.TIM_ClockDivision = TIM_CKD_DIV1;
	TIM1_InitStruct.TIM_RepetitionCounter = 0x1; // generate event every time

	TIM_TimeBaseInit(TIM1, TIM1_InitStruct);

}

/*void ADC_Init(){

	ADC_InitTypeDef ADC_InitStruct;

	// Enable ADC Clock
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_ADC1, ENABLE);

	// Configure ADC1
	ADC_InitStruct.ADC_Resolution = ADC_Resolution_12b;
	ADC_InitStruct.ADC_ScanConvMode = DISABLE;
	ADC_InitStruct.ADC_ContinuousConvMode = DISABLE;
	ADC_InitStruct.ADC_ExternalTrigConvEdge = ADC_ExternalTrigConvEdge_Rising;
	ADC_InitStruct.ADC_ExternalTrigConv = ;
	ADC_InitStruct.ADC_DataAlign = ;
	ADC_InitStruct.ADC_NbrOfConversion = ;


	ADC_Init(ADC1, &ADC_InitStruct);



}
