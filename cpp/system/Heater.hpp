/*
*	Heater.hpp
*
*	Created on: Dec 18, 2023
*		Author: llanyro
*/

#ifndef TEST_CPP_SYSTEM_HEATER_HPP_
#define TEST_CPP_SYSTEM_HEATER_HPP_

#include "types.hpp"

namespace test {
namespace system {

/*!
*	@class Heater
*	@brief Stores information about heating module
*
*	@sa @ref heater
*
*	@since Added in version 1.0.
*
*	@ingroup system
*/
class Heater {
	protected:
		ElectricResistanceStatus electricResistanceStatus;
		PumpFlow pumpFlow;
	protected:
		void __clear() noexcept;
	public:
		Heater() noexcept;
		~Heater() noexcept;

		// Rule of five

		Heater(const Heater& other) noexcept;
		Heater& operator=(const Heater& other) noexcept;
		Heater(Heater&& other) noexcept;
		Heater& operator=(Heater&& other) noexcept;

		__NO_DISCARD__ ElectricResistanceStatus getElectricResistanceStatus() const noexcept;
		__NO_DISCARD__ PumpFlow getPumpFlow() const noexcept;

		void setStandBy() noexcept;
		void start(const Temperature diff) noexcept;
};

} /* namespace system */
} /* namespace test */

#endif /* TEST_CPP_SYSTEM_HEATER_HPP_ */
