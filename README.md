## Traffic Light Simulation on STM32

This project simulates a traffic light system using **C**, **FreeRTOS**, and an **STM32 microcontroller**, integrating hardware, middleware, and software components.

### Objective

The goal is to realistically simulate traffic flow controlled by a three-light traffic signal. Key components include:

- **Traffic Lights:** Represented by three LEDs (green, yellow, red)
- **Road:** Simulated by 19 individual green LEDs
  - **On** = car present
  - **Off** = gap between cars

### System Behavior

- **Green Light:** Cars (LEDs) advance at a consistent rate.
- **Yellow/Red Light:** Cars before the light stop; cars beyond the light continue.
- **Traffic Density:** Controlled by a potentiometer.
  - **Low Resistance:** Sparse traffic (5–6 car gaps), longer red light duration.
  - **High Resistance:** Bumper-to-bumper traffic, longer green light duration.

### Deliverables

The full **hardware**, **software**, and **middleware** implementation is documented in:

📄 `Project 1 - Lab Report.pdf`

### Hardware Overview

![IMG_C1BCFAE1B868-1](https://github.com/user-attachments/assets/af10a294-caf4-4382-ab16-3a7146957d85)

The breadboard setup for the complete traffic light simulation system.
