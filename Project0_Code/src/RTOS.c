#include <stdint.h>
#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include "stm32f4_discovery.h"
#include "stm32f4xx.h"
#include "../FreeRTOS_Source/include/FreeRTOS.h"
#include "../FreeRTOS_Source/include/queue.h"
#include "../FreeRTOS_Source/include/semphr.h"
#include "../FreeRTOS_Source/include/task.h"
#include "../FreeRTOS_Source/include/timers.h"
#include "../Libraries/include/RTOS.h"
#include "../Libraries/include/StopLight.h"
#include "../Libraries/include/TrafficGeneration.h"
#include "../Libraries/include/Initialization.h"

#define mainQUEUE_LENGTH 100
#define maxTicks 13000
#define roadLength 19
#define preLightsLength 8

void Start_RTOS();

void Stop_Light_Task(void *pvParameters);

void Traffic_Generation_Task(void *pvParameters);

xQueueHandle xQueue_handle = 0;

void Start_RTOS(){
	xQueue_handle = xQueueCreate( 	mainQUEUE_LENGTH,		/* The number of items the queue can hold. */
							sizeof( uint16_t ) );	/* The size of each item the queue holds. */

	/* Add to the registry, for the benefit of kernel aware debugging. */
	vQueueAddToRegistry( xQueue_handle, "MainQueue" );

	xTaskCreate( Stop_Light_Task, "Stop_Light", configMINIMAL_STACK_SIZE, NULL, 1, NULL);
	xTaskCreate( Traffic_Generation_Task, "Traffic_Generation_Task", configMINIMAL_STACK_SIZE, NULL, 1, NULL);

	vTaskStartScheduler();
}

void Stop_Light_Task(void *pvParameters){

	Set_Colour(0); // stop light starts green

	int delay = 0;

	uint16_t tx_data = 0;

	while(1){
		delay = Get_Delay(ADC_GetConversionValue(ADC1)+1); // get pot value
		Set_Colour(0);
		if(xQueueSend(xQueue_handle, &tx_data, 1000)){ // tell the road that the light is turning red
			tx_data = 2;
		}
		vTaskDelay(delay); // delay for time proportional to pot
		Set_Colour(1);
		if(xQueueSend(xQueue_handle, &tx_data, 1000)){ // tell the road that the light is turning green
			tx_data = 0;
		}
		vTaskDelay(3000); // 3 seconds
		Set_Colour(2);
		vTaskDelay(maxTicks - delay); // delay for time inversely proportional to pot
	}

}

void Traffic_Generation_Task(void *pvParameters){

	int minValue = 0;
	int maxValue = 10;
	int flow_value = 0;
	uint32_t road = 0x0;
	uint32_t beforeLight = 0x0;
	uint32_t afterLight = 0x0;
	uint16_t rx_data = 0;
	int colour = 0;

	srand(time(NULL));

	GPIO_SetBits(GPIOC, GPIO_Pin_4); // Set CLR to high

	while(1){ // red light shift
		if(xQueueReceive(xQueue_handle, &rx_data, 500)){ // check for new light colour
			if(rx_data == 0)
				colour = 0;
			else
				colour = 1;
		}

		int rand_value = rand() % (maxValue - minValue + 1) + minValue;
		flow_value = Get_Flow(ADC_GetConversionValue(ADC1)+1);
		if(colour == 0){ // LIGHT IS GREEN
			if(rand_value <= flow_value){ // advance light as normal
				road = (road >> 1);
				road |= 0b1000000000000000000;
			} else{
				road = (road >> 1);
			}
		} else { // LIGHT IS RED
			beforeLight = road & 0b1111111100000000000; // get cars before intersection
			uint32_t overflowMask = Get_LSB_Mask(beforeLight); // get the cars at the stop line
			if(rand_value <= flow_value){ // generate traffic for cars before light
				beforeLight >>= 1;
				beforeLight |= 0b1000000000000000000;
			} else {
				beforeLight >>= 1;
			}
			beforeLight |= (overflowMask << 11); // ensure cars remain at light
			beforeLight &= 0b1111111100000000000; // ensure no cars have passed light
			afterLight = road & 0b0000000011111111111; // get cars after light
			afterLight >>= 1; // advance as normal
			road = beforeLight | afterLight; // combine two sets of cars to create road

		}
		Clear_SR();
		for(int i = 0; i<19; i++){ // push 19 bits (cars) of info to SR
	        if (road & (1 << i)) {
	        	GPIO_SetBits(GPIOC, GPIO_Pin_6);
	        } else {
	        	GPIO_ResetBits(GPIOC, GPIO_Pin_6);
	        }
	        GPIO_ResetBits(GPIOC, GPIO_Pin_5);
	        GPIO_SetBits(GPIOC, GPIO_Pin_5);
	        GPIO_ResetBits(GPIOC, GPIO_Pin_5);
		}
		vTaskDelay(1000); // 1 second

	}


}

void vApplicationMallocFailedHook( void )
{
	/* The malloc failed hook is enabled by setting
	configUSE_MALLOC_FAILED_HOOK to 1 in FreeRTOSConfig.h.

	Called if a call to pvPortMalloc() fails because there is insufficient
	free memory available in the FreeRTOS heap.  pvPortMalloc() is called
	internally by FreeRTOS API functions that create tasks, queues, software
	timers, and semaphores.  The size of the FreeRTOS heap is set by the
	configTOTAL_HEAP_SIZE configuration constant in FreeRTOSConfig.h. */
	for( ;; );
}
/*-----------------------------------------------------------*/

void vApplicationStackOverflowHook( xTaskHandle pxTask, signed char *pcTaskName )
{
	( void ) pcTaskName;
	( void ) pxTask;

	/* Run time stack overflow checking is performed if
	configconfigCHECK_FOR_STACK_OVERFLOW is defined to 1 or 2.  This hook
	function is called if a stack overflow is detected.  pxCurrentTCB can be
	inspected in the debugger if the task name passed into this function is
	corrupt. */
	for( ;; );
}
/*-----------------------------------------------------------*/

void vApplicationIdleHook( void )
{
volatile size_t xFreeStackSpace;

	/* The idle task hook is enabled by setting configUSE_IDLE_HOOK to 1 in
	FreeRTOSConfig.h.

	This function is called on each cycle of the idle task.  In this case it
	does nothing useful, other than report the amount of FreeRTOS heap that
	remains unallocated. */
	xFreeStackSpace = xPortGetFreeHeapSize();

	if( xFreeStackSpace > 100 )
	{
		/* By now, the kernel has allocated everything it is going to, so
		if there is a lot of heap remaining unallocated then
		the value of configTOTAL_HEAP_SIZE in FreeRTOSConfig.h can be
		reduced accordingly. */
	}
}
