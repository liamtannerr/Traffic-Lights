#include <stdint.h>
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

#define mainQUEUE_LENGTH 100
#define maxTicks 13000
#define roadLength 19

void Start_RTOS();

void Traffic_Flow_Task(void *pvParameters);

void Stop_Light_Task(void *pvParameters);

void Traffic_Generation_Task(void *pvParameters);

void System_Display_Task(void *pvParameters);

xQueueHandle xQueue_handle = 0;

void Start_RTOS(){
	xQueue_handle = xQueueCreate( 	mainQUEUE_LENGTH,		/* The number of items the queue can hold. */
							sizeof( uint16_t ) );	/* The size of each item the queue holds. */

	/* Add to the registry, for the benefit of kernel aware debugging. */
	vQueueAddToRegistry( xQueue_handle, "MainQueue" );

	//xTaskCreate( Traffic_Flow_Task, "Traffic_Flow", configMINIMAL_STACK_SIZE, NULL, 2, NULL);
	xTaskCreate( Stop_Light_Task, "Stop_Light", configMINIMAL_STACK_SIZE, NULL, 1, NULL);
	xTaskCreate( Traffic_Generation_Task, "Traffic_Generation_Task", configMINIMAL_STACK_SIZE, NULL, 1, NULL);
	xTaskCreate( System_Display_Task, "System_Display", configMINIMAL_STACK_SIZE, NULL, 1, NULL);

	vTaskStartScheduler();
}

/*void Traffic_Flow_Task(void *pvParameters){

	uint16_t Traffic_Flow_Value = ADC_GetConversionValue(ADC1);

	while(1){
		if(xQueueSend(xQueue_handle,&Traffic_Flow_Value,1000)){
			printf("pot %u\n",ADC_GetConversionValue(ADC1));
			vTaskDelay(1000);
		}
	}

}*/

void Stop_Light_Task(void *pvParameters){

	Set_Colour(0);

	int delay = 0;

	while(1){
		delay = Get_Delay(ADC_GetConversionValue(ADC1)+1);
		Set_Colour(0);
		xQueueSend(xQueue_handle, 0, 1000);
		vTaskDelay(delay);
		Set_Colour(1);
		xQueueSend(xQueue_handle, 2, 1000);
		vTaskDelay(3000);
		Set_Colour(2);
		vTaskDelay(maxTicks - delay); // clean this up
	}

}

void Traffic_Generation_Task(void *pvParameters){

	int minValue = 0;
	int maxValue = 10;
	int flow_value = 0;
	uint32_t road = 0x0;
	uint16_t rx_data;

	srand(time(NULL));

	GPIO_SetBits(GPIOC, GPIO_Pin_4);

	while(1){
		xQueueReceive(xQueue_handle, &rx_data, 500);
		if(rx_data == 0)
			printf("Light is green!\n");
		else
			printf("Light is red!\n");
		int rand_value = rand() % (maxValue - minValue + 1) + minValue;
		flow_value = Get_Flow(ADC_GetConversionValue(ADC1)+1);
		if(rand_value <= flow_value){
			road = (road >> 1) | (1<<(roadLength-1));
			//printf("Generate Car! %u\n",road);
		} else{
			road = (road >> 1);
			//printf("No Car. %u\n",road);
		}
		for(int i = 7; i>=0; i--){
	        if (road & (1 << i)) {
	        	GPIO_SetBits(GPIOC, GPIO_Pin_6);
	        } else {
	        	GPIO_ResetBits(GPIOC, GPIO_Pin_6);
	        }
	        GPIO_SetBits(GPIOC, GPIO_Pin_5);
	        GPIO_ResetBits(GPIOC, GPIO_Pin_5);
		}
		vTaskDelay(1000);

	}

}

void System_Display_Task(void *pvParameters){

	while(1){}

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
