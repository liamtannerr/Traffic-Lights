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
    GPIO_InitStruct.GPIO_Mode = GPIO_Mode_AN;
    GPIO_InitStruct.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_InitStruct.GPIO_PuPd = GPIO_PuPd_NOPULL;
    GPIO_Init(GPIOC, &GPIO_InitStruct);
}

void TIM1_Init(){


	// Prescaler and period make it so that it triggers every 100ms
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_TIM1, ENABLE);

	TIM_TimeBaseInitTypeDef TIM1_InitStruct;
	//TIM1_InitStruct.TIM_Prescaler = 0x4C; // figure out what clock is, this should be 100ms
	TIM1_InitStruct.TIM_Prescaler = 0x2FA; // 1s
	//TIM1_InitStruct.TIM_Prescaler = 0x1DCD; // 10s
	TIM1_InitStruct.TIM_CounterMode = TIM_CounterMode_Up;
	TIM1_InitStruct.TIM_Period = 0xFFFF; // 100ms if that's what it is
	TIM1_InitStruct.TIM_ClockDivision = TIM_CKD_DIV1;
	TIM1_InitStruct.TIM_RepetitionCounter = 0x1; // generate event every time


	TIM_TimeBaseInit(TIM1, &TIM1_InitStruct);
	TIM_SetAutoreload(TIM1, 0xFFFF);
	TIM_Cmd(TIM1, ENABLE);
	TIM_SelectOutputTrigger(TIM1, TIM_TRGOSource_Update);

}

void ADC1_Init(){

	// Enable ADC Clock
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_ADC1, ENABLE);

	ADC_InitTypeDef ADC_InitStruct;
	ADC_StructInit(&ADC_InitStruct);

	// Configure ADC1
	ADC_InitStruct.ADC_Resolution = ADC_Resolution_12b;
	ADC_InitStruct.ADC_ScanConvMode = DISABLE;
	ADC_InitStruct.ADC_ContinuousConvMode = ENABLE;
    ADC_InitStruct.ADC_ExternalTrigConv = ADC_ExternalTrigConv_T1_CC1; // Trigger by TIM1 Update event
    ADC_InitStruct.ADC_DataAlign = ADC_DataAlign_Right; // Right alignment of data
    ADC_InitStruct.ADC_NbrOfConversion = 1;  // Single conversion (for one channel)


	ADC_Init(ADC1, &ADC_InitStruct);
	ADC_RegularChannelConfig(ADC1, ADC_Channel_13, 1, ADC_SampleTime_3Cycles);
	ADC_Cmd(ADC1, ENABLE);
    ADC_SoftwareStartConv(ADC1);

}
