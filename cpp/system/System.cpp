/*
*	System.cpp
*
*	Created on: Dec 18, 2023
*		Author: llanyro
*/

#include "System.hpp"

namespace test {
namespace system {

template<class T>
__NO_DISCARD__ T min(const T v1, const T v2) noexcept {
	return (v1 > v2) ? v2 : v1;
}


constexpr Temperature DEFAULT_TEMPERATURE = (USER_TEMPERATURE_MAX + USER_TEMPERATURE_MIN) / 2;
constexpr Temperature DEFAULT_FAN_SPEED = (USER_TEMPERATURE_MAX + USER_TEMPERATURE_MIN) / 2;

void System::__clear() noexcept {
	this->temperature = DEFAULT_TEMPERATURE;
	this->pressure = { STANDBY_PRESSURE, STANDBY_PRESSURE };
	this->evaporatorFanSpeed = DEFAULT_FAN_SPEED;
}

System::System() noexcept
	: temperature(DEFAULT_TEMPERATURE)
	, pressure({ STANDBY_PRESSURE, STANDBY_PRESSURE })
	, evaporatorFanSpeed(DEFAULT_FAN_SPEED)
	, cooler(), heater()
{}
System::~System() {}

System::System(const System& other) noexcept
	: temperature(other.temperature)
	, pressure(other.pressure)
	, evaporatorFanSpeed(other.evaporatorFanSpeed)
	, cooler(other.cooler)
	, heater(other.heater)
{}
System& System::operator=(const System& other) noexcept {
	this->temperature = other.temperature;
	this->pressure = other.pressure;
	this->evaporatorFanSpeed = other.evaporatorFanSpeed;
	this->cooler = other.cooler;
	this->heater = other.heater;
	return *this;
}
System::System(System&& other) noexcept
	: temperature(other.temperature)
	, pressure(other.pressure)
	, evaporatorFanSpeed(other.evaporatorFanSpeed)
	, cooler(std::move(other.cooler))
	, heater(std::move(other.heater))
{ other.__clear(); }
System& System::operator=(System&& other) noexcept {
	this->temperature = other.temperature;
	this->pressure = other.pressure;
	this->evaporatorFanSpeed = other.evaporatorFanSpeed;
	this->cooler = std::move(other.cooler);
	this->heater = std::move(other.heater);
	other.__clear();
	return *this;
}

Temperature System::getTemperature() const noexcept { return this->temperature; }
const PressureValue& System::getPressureValue() const noexcept { return this->pressure; }
FanSpeed System::getEvaporatorFanSpeed() const noexcept { return this->evaporatorFanSpeed; }
const Cooler& System::getCooler() const noexcept { return this->cooler; }
const Heater& System::getHeater() const noexcept { return this->heater; }

bool System::setTemperature(const Temperature temperature) noexcept {
	// We need to increase heat!
	if (temperature > this->temperature) {
		Temperature diff = (temperature - this->temperature) / 4;
		// I will increment 1::0.25 tempereature to bar

		Temperature hightdiff = this->pressure.first - diff;
		Temperature lowdiff = this->pressure.second + diff;
		if (hightdiff < PRESSURE_MIN || lowdiff > PRESSURE_MAX) {
			// ?? Invalid ??
			return false;
		}
		// If we can sub/sum bars
		else {
			this->pressure.first -= diff;
			this->pressure.second += diff;
			this->temperature = temperature;
			this->evaporatorFanSpeed = DEFAULT_FAN_SPEED + diff;
			this->heater.start(diff);
		}
	}
	// We need to cool down
	else if (temperature < this->temperature) {
		Temperature diff = (this->temperature - temperature) / 4;
		// I will increment 1::0.25 tempereature to bar

		Temperature hightdiff = this->pressure.first + diff;
		Temperature lowdiff = this->pressure.second - diff;
		if (hightdiff > PRESSURE_MAX || lowdiff < PRESSURE_MIN) {
			// ?? Invalid ??
			return false;
		}
		// If we can sub/sum bars
		else {
			this->pressure.first += diff;
			this->pressure.second -= diff;
			this->temperature = temperature;
			this->evaporatorFanSpeed = DEFAULT_FAN_SPEED + diff;
			this->cooler.start(diff);
		}
	}
	// If temperature is the same, set system to standby
	else this->setStandBy();
	return true;
}

void System::setStandBy() noexcept {
	this->pressure = { STANDBY_PRESSURE, STANDBY_PRESSURE };
	this->cooler.setStandBy();
	this->heater.setStandBy();
}

} /* namespace system */
} /* namespace test */
