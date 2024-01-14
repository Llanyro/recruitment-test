/*
*	Cooler.c
*
*	Created on: Dec 18, 2023
*		Author: llanyro
*/

#include "Cooler.h"

void cooler_standby(Cooler_t* cooler) {
	cooler->compressorStatus = CompressorStatus_Off;
	cooler->fanSpeed = FAN_SPEED_MIN;
}
void cooler_start(const Temperature_t diff, Cooler_t* cooler) {
	ui32 value = diff / 4;
	if (CompressorStatus_Max < value) value = CompressorStatus_Max;
	cooler->compressorStatus = value;
	cooler->fanSpeed = (FanSpeed_t)diff;
}
