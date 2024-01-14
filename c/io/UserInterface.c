/*
*	DataExporter.c
*
*	Created on: Dec 18, 2023
*		Author: llanyro
*/

#include "UserInterface.h"

#include "../system/System.h"
// #include "../system/Cooler.hpp" already included in System.hpp
// #include "../system/Heater.hpp" already included in System.hpp

#include <stdio.h>
#include <string.h>

void userinterface_init(UserInterface_t* ui, System_t* sys) {
	ui->system = sys;
	memset(ui->uiActions, 0, sizeof(Action) * USER_INTERFACE_ACTIONS);
	ui->errorAction = NULL;
	ui->alive = 1;
}

void userinterface_add_user_action(ui8 key, Action function, UserInterface_t* ui) {
	ui->uiActions[key] = function;
}
void userinterface_add_on_user_error_action(Action errorAction, UserInterface_t* ui) {
	ui->errorAction = errorAction;
}
void userinterface_stop_main_loop(UserInterface_t* ui) {
	ui->alive = 0;
}
void userinterface_start_main_loop(UserInterface_t* ui) {
	ui->alive = 1;
	
	ui8 key = '\0';
	while (ui->alive) {
		if(key != '\n') fprintf(stdout, "Insert next action: ");
		key = getchar();
		if (!ui->uiActions[key]) {
			if (ui->errorAction) ui->errorAction(ui);
			else fprintf(stdout, "Invalid key '%c'\n", key);
		}
		else ui->uiActions[key](ui);
	}
}
