/*
*	DataExporter.cpp
*
*	Created on: Dec 18, 2023
*		Author: llanyro
*/

#include "DataExporter.h"

#include "../system/System.h"
// #include "../system/Cooler.hpp" already included in System.hpp
// #include "../system/Heater.hpp" already included in System.hpp

#include <stdio.h>
#include <string.h>
#include <sys/stat.h>

#ifdef _WIN32
#pragma warning(disable:6029)

#pragma warning(disable:6011)
#pragma warning(disable:6387)
#pragma warning(disable:4996)


#pragma warning(disable:4251)
#pragma warning(disable:4244)
#pragma warning(disable:6031)
#endif // _WIN32

int existFile(string_t filename) {
	struct stat st;
	memset(&st, 0, sizeof(st));
	return stat(filename, &st) == 0;
}

string_t parseCompressorStatus(const CompressorStatus status) {
	switch (status) {
		case CompressorStatus_Off: return "Off";
		case CompressorStatus_Max: return "Max";
		case CompressorStatus_Med: return "Med";
		case CompressorStatus_Min: return "Min";
		default: return "ERROR";
	}
}
string_t parseElectricResistanceStatus(const ElectricResistanceStatus status) {
	switch (status) {
		case ElectricResistanceStatus_Off: return "Off";
		case ElectricResistanceStatus_Max: return "Max";
		case ElectricResistanceStatus_Med: return "Med";
		case ElectricResistanceStatus_Min: return "Min";
		default: return "ERROR";
	}
}

int exportToCSV(const System_t* system, string_t filename) {
	FILE* f = NULL;

	// First check if file exist before opening it (opening file will generate a file if it does not exist)
	int exist = existFile(filename);

	// Now we open the file
	f = fopen(filename, "a");
	if (!f) {
		fprintf(stderr, "Error opening/creaing file '%s'", filename);
		return 0;
	}


	// If file does not exist, we create it with a CSV header
	if (!exist) {
		fprintf(f, "Temperature,HightPressure,LowPressure,EvaporatorFanSpeed,CompressorStatus,FanSpeed,ElectricResistanceStatus,PumpFlow\n");
	}

	const Cooler_t* cooler = &system->cooler;
	const Heater_t* heater = &system->heater;

	fprintf(f, "%f,%f,%f,%i,%s,%i,%s,%i\n",
		system->temperature,
		system->pressure.hightPressure,
		system->pressure.lowPressure,
		system->evaporatorFanSpeed,

		parseCompressorStatus(cooler->compressorStatus),
		cooler->fanSpeed,

		parseElectricResistanceStatus(heater->electricResistanceStatus),
		heater->pumpFlow
	);

	fclose(f);
	return 1;
}
int print(const System_t* system) {
	const Cooler_t* cooler = &system->cooler;
	const Heater_t* heater = &system->heater;

	fprintf(stdout, "System status:\n");
	fprintf(stdout, "\tTemperature: %f\n", system->temperature);
	fprintf(stdout, "\tHightPressure: %f\n", system->pressure.hightPressure);
	fprintf(stdout, "\tLowPressure: %f\n", system->pressure.lowPressure);
	fprintf(stdout, "\tEvaporatorFanSpeed: %i\n", system->evaporatorFanSpeed);

	fprintf(stdout, "System cooler status:\n");
	fprintf(stdout, "\tCompressorStatus: %s\n", parseCompressorStatus(cooler->compressorStatus));
	fprintf(stdout, "\tFanSpeed: %i\n", cooler->fanSpeed);

	fprintf(stdout, "System heater status:\n");
	fprintf(stdout, "\tElectricResistanceStatus: %s\n", parseElectricResistanceStatus(heater->electricResistanceStatus));
	fprintf(stdout, "\tPumpFlow: %i\n", heater->pumpFlow);

	return 1;
}
