/*
*	Heater.c
*
*	Created on: Dec 18, 2023
*		Author: llanyro
*/

#include "Heater.h"

void heater_standby(Heater_t* heater) {
	heater->electricResistanceStatus = ElectricResistanceStatus_Off;
	heater->pumpFlow = WATER_PUMP_FLOW_MIN;
}

void heater_start(const Temperature_t diff, Heater_t* heater) {
	ui32 value = diff / 4;
	if (ElectricResistanceStatus_Max < value) value = ElectricResistanceStatus_Max;
	heater->electricResistanceStatus = value;
	heater->pumpFlow = (PumpFlow_t)diff;
}
