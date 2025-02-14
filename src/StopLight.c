#include <stdint.h>
#include <stdio.h>
#include "stm32f4_discovery.h"
#include "stm32f4xx.h"

#define green  	0
#define yellow  1
#define red  	2

void Set_Colour(int colour){
	if(colour == green){ // set green pin clear everything else
		GPIO_ResetBits(GPIOC, GPIO_Pin_0);
		GPIO_ResetBits(GPIOC, GPIO_Pin_1);
		GPIO_SetBits(GPIOC, GPIO_Pin_2);
	} else if(colour == yellow){ // set yellow pin clear everything else
		GPIO_ResetBits(GPIOC, GPIO_Pin_0);
		GPIO_ResetBits(GPIOC, GPIO_Pin_2);
		GPIO_SetBits(GPIOC, GPIO_Pin_1);
	} else if(colour == red){ // set red pin clear everything else
		GPIO_ResetBits(GPIOC, GPIO_Pin_1);
		GPIO_ResetBits(GPIOC, GPIO_Pin_2);
		GPIO_SetBits(GPIOC, GPIO_Pin_0);
	}

}

int Get_Delay(int Traffic_Flow_Value){
	int low_pot = 1; // min pot value
	int high_pot = 4096; // max pot value
	int low_time = 4; // min light time (3 seconds)
	int high_time = 10; // max light time (10 seconds)

	return (low_time + (Traffic_Flow_Value - low_pot) * (high_time - low_time) / (high_pot - low_pot)) * 1000;
}
