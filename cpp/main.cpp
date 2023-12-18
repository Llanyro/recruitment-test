/*
*	main.cpp
*
*	Created on: Dec 18, 2023
*		Author: llanyro
*/

#include "system/System.hpp"
#include "io/DataExporter.hpp"
#include "io/UserInterface.hpp"

#include <iostream>
#include <random>
#include <string>
#include <cstdio>

constexpr test::system::string_t RESULTS_CSV = "./results.csv";

bool getNumber(test::system::Temperature& pos) {
	std::string input;

	try {
		fprintf(stdout, "You need to insert a positive number.\n");
		fprintf(stdout, "Enter the number: ");
		std::cin >> input;
		pos = std::stof(input);
	}
	catch (const std::invalid_argument& e) {
		fprintf(stderr, "Invalid input. Please enter valid float number. %s\n", e.what());
		return false;
	}
	catch (const std::out_of_range& e) {
		fprintf(stderr, "Number out of range. Please enter valid float number. %s\n", e.what());
		return false;
	}
	return true;
}
void help(test::io::UserInterface&) {
	fprintf(stdout, "Help panel (this panel)\n");
	fprintf(stdout, "\tUse 'p' to print system status\n");
	fprintf(stdout, "\tUse 'e' to export system actual status in file '%s'\n", RESULTS_CSV);
	fprintf(stdout, "\tUse 'i' to insert a new temperature\n");
	fprintf(stdout, "\tUse 'r' to insert a random temperature\n");
	fprintf(stdout, "\tUse 's' to set system to standby\n");
	fprintf(stdout, "\tUse 'h' to show this panel\n");
	fprintf(stdout, "\tUse 'x' to exit program\n");
}
void insertUserTemperature(test::io::UserInterface& ui) {
	test::system::Temperature temperature = 0.0;
	if (!getNumber(temperature)) return;
	if (temperature > test::system::USER_TEMPERATURE_MAX) {
		fprintf(stdout,
			"Temperature cannot be greater than '%f' by user: inserted: '%f'\n",
			test::system::USER_TEMPERATURE_MAX,
			temperature
		);
		return;
	}
	else if (temperature < test::system::USER_TEMPERATURE_MIN) {
		fprintf(stdout,
			"Temperature cannot be lower than '%f' by user: inserted: '%f'\n",
			test::system::USER_TEMPERATURE_MIN,
			temperature
		);
		return;
	}

	if (!ui.getSystem().setTemperature(temperature))
		fprintf(stderr, "Temperature '%f' is invalid\n", temperature);
	(void)test::io::exportToCSV(ui.getSystem(), RESULTS_CSV);
	(void)test::io::print(ui.getSystem());
}
void insertRandomTemperature(test::io::UserInterface& ui) {
	std::random_device randomDevice;
	std::mt19937 generator(randomDevice());
	std::uniform_real_distribution<test::system::Temperature> distribution(
		test::system::USER_TEMPERATURE_MIN,
		test::system::USER_TEMPERATURE_MAX
	);
	test::system::Temperature temperature = distribution(generator);
	if (!ui.getSystem().setTemperature(temperature))
		fprintf(stdout, "Temperature '%f' is invalid\n", temperature);
	(void)test::io::exportToCSV(ui.getSystem(), RESULTS_CSV);
	(void)test::io::print(ui.getSystem());
}
void setStandBy(test::io::UserInterface& ui) {
	ui.getSystem().setStandBy();
	(void)test::io::exportToCSV(ui.getSystem(), RESULTS_CSV);
	(void)test::io::print(ui.getSystem());
}
void fillUserActions(test::io::UserInterface& ui) {
	ui.addUserAction('p', [](test::io::UserInterface& ui) { (void)test::io::print(ui.getSystem()); });
	ui.addUserAction('e', [](test::io::UserInterface& ui) { (void)test::io::exportToCSV(ui.getSystem(), RESULTS_CSV); });
	ui.addUserAction('i', insertUserTemperature);
	ui.addUserAction('r', insertRandomTemperature);
	ui.addUserAction('s', setStandBy);
	ui.addUserAction('x', [](test::io::UserInterface& ui) { ui.stopMainLoop(); });

	ui.addUserAction('h', help);
	ui.addUserAction('\0', [](test::io::UserInterface& ui){});
	ui.addUserAction('\n', [](test::io::UserInterface& ui){});
	ui.addUserAction('\r', [](test::io::UserInterface& ui){});
	ui.addOnUserErrorAction(help);
}

int main() {
	test::system::System system;
	test::io::UserInterface ui(system);
	fillUserActions(ui);
	help(ui);
	ui.startMainLoop();
	
	return 0;
}
