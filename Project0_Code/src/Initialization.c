#include "../Libraries/include/Initialization.h"

#include <stdint.h>
#include <stdio.h>
#include "stm32f4_discovery.h"
#include "stm32f4xx.h"

#define mainQUEUE_LENGTH 100

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
			GPIO_Pin_6;
    GPIO_InitStruct.GPIO_Mode = GPIO_Mode_OUT;
    GPIO_InitStruct.GPIO_Speed = GPIO_Speed_2MHz;
    GPIO_InitStruct.GPIO_OType = GPIO_OType_PP;
    GPIO_InitStruct.GPIO_PuPd = GPIO_PuPd_NOPULL;
    GPIO_Init(GPIOC, &GPIO_InitStruct);

   // Initialize Pin 3 as Input
    GPIO_InitStruct.GPIO_Pin = GPIO_Pin_3;
    GPIO_InitStruct.GPIO_Mode = GPIO_Mode_AN;
    GPIO_InitStruct.GPIO_Speed = GPIO_Speed_2MHz;
    GPIO_InitStruct.GPIO_PuPd = GPIO_PuPd_NOPULL;
    GPIO_Init(GPIOC, &GPIO_InitStruct);
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

void Clear_SR(){
	GPIO_ResetBits(GPIOC, GPIO_Pin_4); // Set CLR to low
	GPIO_SetBits(GPIOC, GPIO_Pin_4); // Set CLR to high;
}
