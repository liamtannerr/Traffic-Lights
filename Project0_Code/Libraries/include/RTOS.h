void Start_RTOS();

void Stop_Light_Task(void *pvParameters);

void Traffic_Generation_Task(void *pvParameters);

void vApplicationMallocFailedHook( void );

void vApplicationStackOverflowHook( xTaskHandle pxTask, signed char *pcTaskName );

void vApplicationIdleHook( void );
