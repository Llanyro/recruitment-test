/*
*	Cooler.cpp
*
*	Created on: Dec 18, 2023
*		Author: llanyro
*/

#include "Cooler.hpp"

namespace test {
namespace system {

void Cooler::__clear() noexcept {
	this->compressorStatus = CompressorStatus::Off;
	this->fanSpeed = FAN_SPEED_MIN;
}

Cooler::Cooler() noexcept
	: compressorStatus(CompressorStatus::Off)
	, fanSpeed(FAN_SPEED_MIN)
{}
Cooler::~Cooler() noexcept {}

Cooler::Cooler(const Cooler& other) noexcept
	: compressorStatus(other.compressorStatus) 
	, fanSpeed(other.fanSpeed)
{}
Cooler& Cooler::operator=(const Cooler& other) noexcept {
	this->fanSpeed = other.fanSpeed;
	this->compressorStatus = other.compressorStatus;
	return *this;
}
Cooler::Cooler(Cooler&& other) noexcept
	// Copy like a normal copy constructor && clear other
	: Cooler(other) { other.__clear(); }
Cooler& Cooler::operator=(Cooler&& other) noexcept {
	this->fanSpeed = other.fanSpeed;
	this->compressorStatus = other.compressorStatus;
	other.__clear();
	return *this;
}

CompressorStatus Cooler::getCompressorStatus() const noexcept { return this->compressorStatus; }
FanSpeed Cooler::getFanSpeed() const noexcept { return this->fanSpeed; }

void Cooler::setStandBy() noexcept { this->__clear(); }
void Cooler::start(const Temperature diff) noexcept {
	ui32 value = diff / 4;
	if (static_cast<ui32>(CompressorStatus::Max) < value) value = static_cast<ui32>(CompressorStatus::Max);
	this->compressorStatus = static_cast<CompressorStatus>(value);
	this->fanSpeed = diff;
}

} /* namespace system */
} /* namespace test */
