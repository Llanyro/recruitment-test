/*
*	System.hpp
*
*	Created on: Dec 18, 2023
*		Author: llanyro
*/

#ifndef TEST_CPP_SYSTEM_SYSTEM_HPP_
#define TEST_CPP_SYSTEM_SYSTEM_HPP_

#include "Cooler.hpp"
#include "Heater.hpp"

namespace test {
namespace system {

/*!
*	@class System
*	@brief Class that exports data into files
*
*	This class is to maintain a Model-view-controller classic
*	Also, being this class empty, this will contain only static methods
*
*	@sa @ref system
*
*	@since Added in version 1.0.
*
*	@ingroup system
*/
class System {
	protected:
		Temperature temperature;
		PressureValue pressure;
		FanSpeed evaporatorFanSpeed;
		Cooler cooler;
		Heater heater;
	protected:
		void __clear() noexcept;
	public:
		System() noexcept;
		~System() noexcept;

		// Rule of five

		System(const System& other) noexcept;
		System& operator=(const System& other) noexcept;
		System(System&& other) noexcept;
		System& operator=(System&& other) noexcept;

		__NO_DISCARD__ Temperature getTemperature() const noexcept;
		__NO_DISCARD__ const PressureValue& getPressureValue() const noexcept;
		__NO_DISCARD__ FanSpeed getEvaporatorFanSpeed() const noexcept;
		__NO_DISCARD__ const Cooler& getCooler() const noexcept;
		__NO_DISCARD__ const Heater& getHeater() const noexcept;

		__NO_DISCARD__ bool setTemperature(const Temperature temperature) noexcept;
		__NO_DISCARD__ void setStandBy() noexcept;
};

} /* namespace system */
} /* namespace test */

#endif /* TEST_CPP_SYSTEM_SYSTEM_HPP_ */
