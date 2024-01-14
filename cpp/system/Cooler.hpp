/*
*	Cooler.hpp
*
*	Created on: Dec 18, 2023
*		Author: llanyro
*/

#ifndef TEST_CPP_SYSTEM_COOLER_HPP_
#define TEST_CPP_SYSTEM_COOLER_HPP_

#include "types.hpp"

namespace test {
namespace system {

/*!
*	@class Cooler
*	@brief Stores information about cooling modoule
*
*	@sa @ref cooler
*
*	@since Added in version 1.0.
*
*	@ingroup system
*/
class Cooler {
	protected:
		CompressorStatus compressorStatus;
		FanSpeed fanSpeed;
	protected:
		void __clear() noexcept;
	public:
		Cooler() noexcept;
		~Cooler() noexcept;

		// Rule of five

		Cooler(const Cooler& other) noexcept;
		Cooler& operator=(const Cooler& other) noexcept;
		Cooler(Cooler&& other) noexcept;
		Cooler& operator=(Cooler&& other) noexcept;

		__NO_DISCARD__ CompressorStatus getCompressorStatus() const noexcept;
		__NO_DISCARD__ FanSpeed getFanSpeed() const noexcept;

		void setStandBy() noexcept;
		void start(const Temperature diff) noexcept;
};

} /* namespace system */
} /* namespace test */

#endif /* TEST_CPP_SYSTEM_COOLER_HPP_ */
