#include "donglify/execute.hpp"

#include "donglify/ansi.hpp"

#include <iostream>
#include <stdlib.h>

int execute(std::string cmd, std::string desc, bool ask, bool needed)
{
	if (ask) {
		std::cout << std::endl;

		std::cout << "You are about to execute the following command as ";
		std::cout << ANSI_COLOR_FG_YELLOW << ANSI_BLINK;
		std::cout << "SUDO";
		reset_all_ansi();

		std::cout << ANSI_DIM;
		std::cout << "> ";
		std::cout << ANSI_RESET_ALL;

		std::cout << ANSI_COLOR_BG_RED << ANSI_BLINK << ANSI_BOLD;
		std::cout << cmd;
		reset_all_ansi();

		std::cout << "Is command needed? ";
		print_yes_or_no(needed);

		std::cout << "Command description: " << desc << std::endl;
		std::cout << std::endl;

		std::cout << "Do you accept after review? [yes]: ";
		std::string confirmation;
		std::getline(std::cin, confirmation);

		if (confirmation != "yes") {
			std::cout << "Not executing by command of user." << std::endl;
			if (needed) {
				std::cout << "This was a needed command, refusing to continue.\nFarewell." << std::endl;
				exit(1);
			}
			return -11;
		}

	} else {
		std::cout << ANSI_BOLD;
		std::cout << ANSI_COLOR_FG_GREEN << "executing: " << ANSI_COLOR_FG_DEFAULT;
		std::cout << ANSI_COLOR_FG_YELLOW << cmd;
		std::cout << ANSI_COLOR_FG_DEFAULT << ANSI_RESET_ALL;

		std::cout << ANSI_DIM << "# " << desc << ANSI_RESET_ALL << std::endl;
	}

	return system(cmd.c_str());
}
