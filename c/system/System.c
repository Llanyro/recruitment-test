/*
*	System.c
*
*	Created on: Dec 18, 2023
*		Author: llanyro
*/

#include "System.h"

Temperature_t DEFAULT_TEMPERATURE = (USER_TEMPERATURE_MAX + USER_TEMPERATURE_MIN) / 2;
Temperature_t DEFAULT_FAN_SPEED = (USER_TEMPERATURE_MAX + USER_TEMPERATURE_MIN) / 2;
PressureValue_t DEFAULT_PRESSURE = { STANDBY_PRESSURE, STANDBY_PRESSURE };

void system_init(System_t* sys) {
	sys->temperature = DEFAULT_TEMPERATURE;
	sys->pressure = DEFAULT_PRESSURE;
	sys->evaporatorFanSpeed = DEFAULT_FAN_SPEED;
	cooler_standby(&sys->cooler);
	heater_standby(&sys->heater);
}

int system_set_temperature(const Temperature_t temperature, System_t* sys) {
	// We need to increase heat!
	if (temperature > sys->temperature) {
		Temperature_t diff = (temperature - sys->temperature) / 4;
		// I will increment 1::0.25 tempereature to bar

		Temperature_t hightdiff = sys->pressure.hightPressure - diff;
		Temperature_t lowdiff = sys->pressure.lowPressure + diff;
		if (hightdiff < PRESSURE_MIN || lowdiff > PRESSURE_MAX) {
			// ?? Invalid ??
			return 0;
		}
		// If we can sub/sum bars
		else {
			sys->pressure.hightPressure -= diff;
			sys->pressure.lowPressure += diff;
			sys->temperature = temperature;
			sys->evaporatorFanSpeed = (FanSpeed_t)(DEFAULT_FAN_SPEED + diff);
			heater_start(diff, &sys->heater);
		}
	}
	// We need to cool down
	else if (temperature < sys->temperature) {
		Temperature_t diff = (sys->temperature - temperature) / 4;
		// I will increment 1::0.25 tempereature to bar

		Temperature_t hightdiff = sys->pressure.hightPressure + diff;
		Temperature_t lowdiff = sys->pressure.lowPressure - diff;
		if (hightdiff > PRESSURE_MAX || lowdiff < PRESSURE_MIN) {
			// ?? Invalid ??
			return 0;
		}
		// If we can sub/sum bars
		else {
			sys->pressure.hightPressure += diff;
			sys->pressure.lowPressure -= diff;
			sys->temperature = temperature;
			sys->evaporatorFanSpeed = (FanSpeed_t)(DEFAULT_FAN_SPEED + diff);
			cooler_start(diff, &sys->cooler);
		}
	}
	// If temperature is the same, set system to standby
	else system_standby(sys);
	return 1;
}

void system_standby(System_t* sys) {
	sys->pressure = DEFAULT_PRESSURE;
	cooler_standby(&sys->cooler);
	heater_standby(&sys->heater);
}
