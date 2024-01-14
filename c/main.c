/*
*	main.cpp
*
*	Created on: Dec 18, 2023
*		Author: llanyro
*/

#include "system/System.h"
#include "io/DataExporter.h"
#include "io/UserInterface.h"

#include <stdio.h>
#include <stdlib.h>

#ifdef _WIN32
#pragma warning(disable:4996)
#endif // _WIN32

//#include <random>
//#include <string>

#define RESULTS_CSV "./results.csv"

void clearInputBuffer() {
	int c;
	while ((c = getchar()) != '\n' && c != EOF);
}

void print_system(UserInterface_t* ui) {
	(void)print(&ui->system);
}
void export_system(UserInterface_t* ui) {
	(void)exportToCSV(ui->system, RESULTS_CSV);
}
void ui_null(UserInterface_t* ui) {}


int getNumber(Temperature_t* pos) {
	//clearInputBuffer();

	char input[256]; // Assuming a reasonable input buffer size

	printf("You need to insert a positive number.\n");
	printf("Enter the number: ");

	if (scanf("%s", input) != 1) {
		fprintf(stderr, "Error reading input.\n");
		return 0;
	}

	char* endptr = NULL;
	*pos = strtof(input, &endptr);

	if (*endptr != '\0') {
		fprintf(stderr, "Invalid input. Please enter a valid float number.\n");
		return 0;
	}

	return 1;
}

void help(UserInterface_t* ui) {
	fprintf(stdout, "Help panel (this panel)\n");
	fprintf(stdout, "\tUse 'p' to print system status\n");
	fprintf(stdout, "\tUse 'e' to export system actual status in file '%s'\n", RESULTS_CSV);
	fprintf(stdout, "\tUse 'i' to insert a new temperature\n");
	fprintf(stdout, "\tUse 'r' to insert a random temperature\n");
	fprintf(stdout, "\tUse 's' to set system to standby\n");
	fprintf(stdout, "\tUse 'h' to show this panel\n");
	fprintf(stdout, "\tUse 'x' to exit program\n");
}
void insertUserTemperature(UserInterface_t* ui) {
	Temperature_t temperature = 0.0;
	if (!getNumber(&temperature)) return;
	if (temperature > USER_TEMPERATURE_MAX) {
		fprintf(stdout,
			"Temperature cannot be greater than '%f' by user: inserted: '%f'\n",
			USER_TEMPERATURE_MAX,
			temperature
		);
		return;
	}
	else if (temperature < USER_TEMPERATURE_MIN) {
		fprintf(stdout,
			"Temperature cannot be lower than '%f' by user: inserted: '%f'\n",
			USER_TEMPERATURE_MIN,
			temperature
		);
		return;
	}

	if (!system_set_temperature(temperature, ui->system))
		fprintf(stderr, "Temperature '%f' is invalid\n", temperature);
	export_system(ui);
	print_system(ui);
}
void setStandBy(UserInterface_t* ui) {
	system_standby(ui->system);
	export_system(ui);
	print_system(ui);
}

void fillUserActions(UserInterface_t* ui) {
	userinterface_add_user_action('p', print_system, ui);
	userinterface_add_user_action('e', export_system, ui);
	userinterface_add_user_action('i', insertUserTemperature, ui);
	userinterface_add_user_action('r', ui_null, ui);
	//userinterface_add_user_action('r', insertRandomTemperature, ui);
	userinterface_add_user_action('s', setStandBy, ui);
	userinterface_add_user_action('x', userinterface_stop_main_loop, ui);

	userinterface_add_user_action('h', help, ui);
	userinterface_add_user_action('\0', ui_null, ui);
	userinterface_add_user_action('\n', ui_null, ui);
	userinterface_add_user_action('\r', ui_null, ui);
	userinterface_add_on_user_error_action(help, ui);
}

int main() {
	System_t system;
	system_init(&system);

	UserInterface_t ui;
	userinterface_init(&ui, &system);
	fillUserActions(&ui);
	help(NULL);
	userinterface_start_main_loop(&ui);
	
	return 0;
}
