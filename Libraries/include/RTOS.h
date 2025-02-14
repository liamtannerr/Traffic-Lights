void Start_RTOS();

void Traffic_Flow_Task(void *pvParameters);

void Stop_Light_Task(void *pvParameters);

void Traffic_Generation_Task(void *pvParameters);

void System_Display_Task(void *pvParameters);

void vApplicationMallocFailedHook( void );

void vApplicationStackOverflowHook( xTaskHandle pxTask, signed char *pcTaskName );

void vApplicationIdleHook( void );
