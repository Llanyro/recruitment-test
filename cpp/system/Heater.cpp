/*
*	Heater.cpp
*
*	Created on: Dec 18, 2023
*		Author: llanyro
*/

#include "Heater.hpp"

namespace test {
namespace system {

void Heater::__clear() noexcept {
	this->electricResistanceStatus = ElectricResistanceStatus::Off;
	this->pumpFlow = WATER_PUMP_FLOW_MIN;
}

Heater::Heater() noexcept
	: electricResistanceStatus(ElectricResistanceStatus::Off)
	, pumpFlow(WATER_PUMP_FLOW_MIN)
{}
Heater::~Heater() noexcept {}

Heater::Heater(const Heater& other) noexcept
	: electricResistanceStatus(other.electricResistanceStatus)
	, pumpFlow(other.pumpFlow)
{}
Heater& Heater::operator=(const Heater& other) noexcept {
	this->pumpFlow = other.pumpFlow;
	this->electricResistanceStatus = other.electricResistanceStatus;
	return *this;
}
Heater::Heater(Heater&& other) noexcept
	// Copy like a normal copy constructor && clear other
	: Heater(other) { other.__clear(); }
Heater& Heater::operator=(Heater&& other) noexcept {
	this->pumpFlow = other.pumpFlow;
	this->electricResistanceStatus = other.electricResistanceStatus;
	other.__clear();
	return *this;
}

ElectricResistanceStatus Heater::getElectricResistanceStatus() const noexcept { return this->electricResistanceStatus; }
PumpFlow Heater::getPumpFlow() const noexcept { return this->pumpFlow; }

void Heater::setStandBy() noexcept { this->__clear(); }
void Heater::start(const Temperature diff) noexcept {
	ui32 value = diff / 4;
	if (static_cast<ui32>(ElectricResistanceStatus::Max) < value) value = static_cast<ui32>(ElectricResistanceStatus::Max);
	this->electricResistanceStatus = static_cast<ElectricResistanceStatus>(value);
	this->pumpFlow = diff;
}

} /* namespace system */
} /* namespace test */
