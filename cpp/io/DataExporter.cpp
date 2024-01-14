/*
*	DataExporter.cpp
*
*	Created on: Dec 18, 2023
*		Author: llanyro
*/

#include "DataExporter.hpp"

#include "../system/System.hpp"
// #include "../system/Cooler.hpp" already included in System.hpp
// #include "../system/Heater.hpp" already included in System.hpp

#include <cstdio>
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


namespace test {

/*
*	Making a internal namespace when we can create a real namespace is usually not good
*	In other words, util namespace should be in other file, but this time i will not create it
*	Not only because this does not belongs here, but for avoiding duplicating code
*	A lot of functions could use this code, so, making a utils libray is a good way to do that
*/
namespace util {

bool existFile(system::string_t filename) {
	struct stat st = {};
	return stat(filename, &st) == 0;
}

} /* namespace io */


namespace io {

system::string_t parseEnum(const system::CompressorStatus status) {
	switch (status) {
		case system::CompressorStatus::Off: return "Off";
		case system::CompressorStatus::Max: return "Max";
		case system::CompressorStatus::Med: return "Med";
		case system::CompressorStatus::Min: return "Min";
		default: return "ERROR";
	}
}
system::string_t parseEnum(const system::ElectricResistanceStatus status) {
	switch (status) {
		case system::ElectricResistanceStatus::Off: return "Off";
		case system::ElectricResistanceStatus::Max: return "Max";
		case system::ElectricResistanceStatus::Med: return "Med";
		case system::ElectricResistanceStatus::Min: return "Min";
		default: return "ERROR";
	}
}

bool exportToCSV(const system::System& system, system::string_t filename) {
	FILE* f = nullptr;

	// First check if file exist before opening it (opening file will generate a file if it does not exist)
	bool exist = util::existFile(filename);

	// Now we open the file
	f = std::fopen(filename, "a");
	if (!f) {
		std::fprintf(stderr, "Error opening/creaing file '%s'", filename);
		return false;
	}


	// If file does not exist, we create it with a CSV header
	if (!exist) {
		std::fprintf(f, "Temperature,HightPressure,LowPressure,EvaporatorFanSpeed,CompressorStatus,FanSpeed,ElectricResistanceStatus,PumpFlow\n");
	}

	const system::PressureValue& pressure = system.getPressureValue();
	const system::Cooler& cooler = system.getCooler();
	const system::Heater& heater = system.getHeater();

	std::fprintf(f, "%f,%f,%f,%f,%s,%i,%s,%i\n",
		system.getTemperature(),
		pressure.first,
		pressure.second,
		system.getEvaporatorFanSpeed(),
		parseEnum(cooler.getCompressorStatus()),
		cooler.getFanSpeed(),
		parseEnum(heater.getElectricResistanceStatus()),
		heater.getPumpFlow()
	);

	std::fclose(f);
	return true;
}
bool print(const system::System& system) {
	const system::PressureValue& pressure = system.getPressureValue();
	const system::Cooler& cooler = system.getCooler();
	const system::Heater& heater = system.getHeater();

	fprintf(stdout, "System status:\n");
	fprintf(stdout, "\tTemperature: %f\n", system.getTemperature());
	fprintf(stdout, "\tHightPressure: %f\n", pressure.first);
	fprintf(stdout, "\tLowPressure: %f\n", pressure.second);
	fprintf(stdout, "\tEvaporatorFanSpeed: %f\n", system.getEvaporatorFanSpeed());

	fprintf(stdout, "System cooler status:\n");
	fprintf(stdout, "\tCompressorStatus: %s\n", parseEnum(cooler.getCompressorStatus()));
	fprintf(stdout, "\tFanSpeed: %i\n", cooler.getFanSpeed());

	fprintf(stdout, "System heater status:\n");
	fprintf(stdout, "\tElectricResistanceStatus: %s\n", parseEnum(heater.getElectricResistanceStatus()));
	fprintf(stdout, "\tPumpFlow: %i\n", heater.getPumpFlow());

	return true;
}

} /* namespace io */
} /* namespace test */
