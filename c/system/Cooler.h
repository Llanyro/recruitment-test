/*
*	Cooler.h
*
*	Created on: Dec 18, 2023
*		Author: llanyro
*/

#ifndef TEST_CPP_SYSTEM_COOLER_H_
#define TEST_CPP_SYSTEM_COOLER_H_

#include "types.h"

typedef struct {
	CompressorStatus compressorStatus;
	FanSpeed_t fanSpeed;
} Cooler_t;

void cooler_standby(Cooler_t* cooler);
void cooler_start(const Temperature_t diff, Cooler_t* cooler);

#endif // TEST_CPP_SYSTEM_COOLER_H_
