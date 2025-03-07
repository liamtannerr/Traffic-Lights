The objective of this project is to create a traffic light simulation using hardware, middleware and, FreeRTOS using C code implemented on an STM32 microcontroller. The traffic lights are simulated by a green, yellow and, red LED. The road is simulated by 19 individual green LEDs, where LEDs that are on represent cars, and LEDs that are off represent the gaps between cars. It follows that when the light is green, the cars progress at a consistent rate along the road, and when the light is yellow or red, the cars behind the stop light stop, and the cars after the light continue at a consistent rate. Traffic flow is controlled by a potentiometer, which when set to a minimum resistance produces cars with a 5-6 car gap and a maximum red light length. When set to maximum resistance, bumper-to-bumper traffic is produced, and the green light length is at a maximum.

The full hardware, software and middleare implementation of our system can be found in Project 1 - Lab Report.pdf.

![IMG_C1BCFAE1B868-1](https://github.com/user-attachments/assets/af10a294-caf4-4382-ab16-3a7146957d85)

The breadboard wiring of our system.
