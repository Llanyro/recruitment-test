/*
*	Heater.h
*
*	Created on: Dec 18, 2023
*		Author: llanyro
*/

#ifndef TEST_CPP_SYSTEM_HEATER_H_
#define TEST_CPP_SYSTEM_HEATER_H_

#include "types.h"

typedef struct {
	ElectricResistanceStatus electricResistanceStatus;
	PumpFlow_t pumpFlow;
} Heater_t;

void heater_standby(Heater_t* heater);
void heater_start(const Temperature_t diff, Heater_t* heater);

#endif // TEST_CPP_SYSTEM_HEATER_H_
