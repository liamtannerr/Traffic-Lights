#include <stdint.h>
#include <stdio.h>
#include "stm32f4_discovery.h"
#include "stm32f4xx.h"

int Get_Flow(int Traffic_Flow_Value){
	int low_pot = 1; // min pot value
	int high_pot = 4096; // max pot value
	int low_flow = 1; // min flow
	int high_flow = 10; // max flow

	return (low_flow + (Traffic_Flow_Value - low_pot) * (high_flow - low_flow) / (high_pot - low_pot));
}

uint32_t Get_LSB_Mask(uint32_t beforeLights){
	beforeLights >>= 11;
	uint16_t mask = 0;
	while(beforeLights & 1){
		mask <<= 1;
		mask |= 1;
		beforeLights >>= 1;
	}
	return mask;
}
