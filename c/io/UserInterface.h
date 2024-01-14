/*
*	UserInterface.hpp
*
*	Created on: Dec 18, 2023
*		Author: llanyro
*/

#ifndef TEST_CPP_IO_USERINTERFACE_H_
#define TEST_CPP_IO_USERINTERFACE_H_

#include "../system/System.h"

typedef void (*Action) (struct UserInterface*);

#define USER_INTERFACE_ACTIONS 255

typedef struct UserInterface {
	System_t* system;
	Action uiActions[USER_INTERFACE_ACTIONS];
	Action errorAction;
	char alive;
} UserInterface_t;

void userinterface_init(UserInterface_t* ui, System_t* sys);

void userinterface_add_user_action(ui8 key, Action function, UserInterface_t* ui);
void userinterface_add_on_user_error_action(Action errorAction, UserInterface_t* ui);
void userinterface_stop_main_loop(UserInterface_t* ui);
void userinterface_start_main_loop(UserInterface_t* ui);

#endif /* TEST_CPP_IO_USERINTERFACE_H_ */
