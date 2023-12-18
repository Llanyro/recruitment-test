/*
*	DataExporter.cpp
*
*	Created on: Dec 18, 2023
*		Author: llanyro
*/

#include "UserInterface.hpp"

#include "../system/System.hpp"
// #include "../system/Cooler.hpp" already included in System.hpp
// #include "../system/Heater.hpp" already included in System.hpp

#include <cstdio>

namespace test {
namespace io {

UserInterface::UserInterface(system::System& system) noexcept
	: system(system)
	, uiActions(), errorAction(nullptr)
	, alive(true)
{}
UserInterface::~UserInterface() noexcept {}

system::System& UserInterface::getSystem() noexcept { return this->system; }

void UserInterface::addUserAction(test::system::ui8 key, Action function) noexcept {
	this->uiActions[key] = function;
}
void UserInterface::addOnUserErrorAction(Action errorAction) noexcept {
	this->errorAction = errorAction;
}
void UserInterface::stopMainLoop() noexcept {
	this->alive = false;
}
void UserInterface::startMainLoop() noexcept {
	this->alive = true;
	
	test::system::ui8 key = '\0';
	while (this->alive) {
		if(key != '\n') fprintf(stdout, "Insert next action: ");
		key = std::getchar();
		auto it = this->uiActions.find(key);
		if (it == this->uiActions.end()) {
			if (this->errorAction) this->errorAction(*this);
			else fprintf(stdout, "Invalid key '%c'\n", key);
		}
		else it->second(*this);
	}
}

} /* namespace io */
} /* namespace test */
