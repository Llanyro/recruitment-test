/*
*	UserInterface.hpp
*
*	Created on: Dec 18, 2023
*		Author: llanyro
*/

#ifndef TEST_CPP_IO_USERINTERFACE_HPP_
#define TEST_CPP_IO_USERINTERFACE_HPP_

#include "../system/types.hpp"

#include <unordered_map>

namespace test {
namespace system { class System; } /* namespace system */
namespace io {

class UserInterface;
typedef void (*Action) (UserInterface&);
typedef std::unordered_map<char, Action> ActionList;

/*!
*	@class UserInterface
*	@brief Creates an easy user interface for console programs
*
*	@sa @ref ui
*
*	@since Added in version 1.0.
*
*	@ingroup io
*/
class UserInterface {
	protected:
		system::System& system;
		ActionList uiActions;
		Action errorAction;
		bool alive;
	public:
		UserInterface(system::System& system) noexcept;
		~UserInterface() noexcept;

		UserInterface(const UserInterface&) = delete;
		UserInterface& operator=(const UserInterface&) = delete;
		UserInterface(UserInterface&&) = delete;
		UserInterface& operator=(UserInterface&&) = delete;

		system::System& getSystem() noexcept;

		void addUserAction(test::system::ui8 key, Action function) noexcept;
		void addOnUserErrorAction(Action errorAction) noexcept;
		void stopMainLoop() noexcept;
		void startMainLoop() noexcept;
};

} /* namespace io */
} /* namespace test */

#endif /* TEST_CPP_IO_USERINTERFACE_HPP_ */
