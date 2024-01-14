/*
*	System.h
*
*	Created on: Dec 18, 2023
*		Author: llanyro
*/

#ifndef TEST_CPP_SYSTEM_SYSTEM_H_
#define TEST_CPP_SYSTEM_SYSTEM_H_

#include "Cooler.h"
#include "Heater.h"

typedef struct {
	Temperature_t temperature;
	PressureValue_t pressure;
	FanSpeed_t evaporatorFanSpeed;
	Cooler_t cooler;
	Heater_t heater;
} System_t;

void system_init(System_t* sys);
int system_set_temperature(const Temperature_t temperature, System_t* sys);
void system_standby(System_t* sys);

#endif // TEST_CPP_SYSTEM_SYSTEM_H_
