#include <stdint.h>
#include <stdio.h>
#include "stm32f4_discovery.h"
#include "stm32f4xx.h"
#include "../FreeRTOS_Source/include/FreeRTOS.h"
#include "../FreeRTOS_Source/include/queue.h"
#include "../FreeRTOS_Source/include/semphr.h"
#include "../FreeRTOS_Source/include/task.h"
#include "../FreeRTOS_Source/include/timers.h"
#include "../Libraries/include/RTOS.h"

#define mainQUEUE_LENGTH 100

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

	xTaskCreate( Traffic_Flow_Task, "Traffic_Flow", configMINIMAL_STACK_SIZE, NULL, 2, NULL);
	xTaskCreate( Stop_Light_Task, "Stop_Light", configMINIMAL_STACK_SIZE, NULL, 1, NULL);
	xTaskCreate( Traffic_Generation_Task, "Traffic_Generation_Task", configMINIMAL_STACK_SIZE, NULL, 1, NULL);
	xTaskCreate( System_Display_Task, "System_Display", configMINIMAL_STACK_SIZE, NULL, 1, NULL);

	vTaskStartScheduler();
}

void Traffic_Flow_Task(void *pvParameters){

	uint16_t Traffic_Flow_Value = ADC_GetConversionValue(ADC1);

	while(1){
		if(xQueueSend(xQueue_handle,&Traffic_Flow_Value,1000)){
			printf("pot %u\n",ADC_GetConversionValue(ADC1));
			vTaskDelay(1000);
		}
	}

}

void Stop_Light_Task(void *pvParameters){

	while(1){}

}

void Traffic_Generation_Task(void *pvParameters){

	while(1){}

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
