
/* Standard includes. */
#include <stdint.h>
#include <stdio.h>
#include "stm32f4_discovery.h"
/* Kernel includes. */
#include "stm32f4xx.h"
#include "../FreeRTOS_Source/include/FreeRTOS.h"
#include "../FreeRTOS_Source/include/queue.h"
#include "../FreeRTOS_Source/include/semphr.h"
#include "../FreeRTOS_Source/include/task.h"
#include "../FreeRTOS_Source/include/timers.h"
#include "../Libraries/include/Initialization.h"
#include "../Libraries/include/StopLight.h"
#include "../Libraries/include/SystemDisplay.h"
#include "../Libraries/include/TrafficFlow.h"
#include "../Libraries/include/TrafficGeneration.h"
#include "../Libraries/include/RTOS.h"


unsigned char digits[10] = { 0x3f, 0x06, 0x5B, 0x4F, 0x66, 0x6D, 0x7D, 0x07, 0x7F, 0x6F };

/*-----------------------------------------------------------*/

int main(void)
{

	SystemInit();
	SystemCoreClockUpdate();

	printf("System Clock: %u Hz\n", SystemCoreClock);

	GPIOC_Init();
	TIM1_Init();
	ADC1_Init();
	Clear_SR();
	Start_RTOS();


	//uint32_t counterValue;
	//int count = 0;


	/*while(1){
		int target_value = (ADC_GetConversionValue(ADC1) * 65535 + 1) / 4095;
		GPIO_SetBits(GPIOC, GPIO_Pin_0);
		while(TIM1->CNT != target_value){}
		GPIO_ResetBits(GPIOC, GPIO_Pin_0);
		GPIO_SetBits(GPIOC, GPIO_Pin_1);
		while(TIM1->CNT != target_value){}
		GPIO_ResetBits(GPIOC, GPIO_Pin_1);
		GPIO_SetBits(GPIOC, GPIO_Pin_2);
		while(TIM1->CNT != target_value){}
		GPIO_ResetBits(GPIOC, GPIO_Pin_2);
		printf("time %u\n",ADC_GetConversionValue(ADC1));
	}*/


	return 0;
}

