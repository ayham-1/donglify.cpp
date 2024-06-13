#include "donglify/execute.hpp"

#include "donglify/ansi.hpp"

#include <iostream>
#include <stdio.h>
#include <stdlib.h>

int execute(std::string cmd, std::string desc, bool needed, bool ask)
{
	if (ask) {
		std::cout << std::endl;

		std::cout << "You are about to execute the following command as ";
		std::cout << ANSI_COLOR_FG_YELLOW << ANSI_BLINK << "SUDO" << std::endl;
		reset_all_ansi();

		start_new_line();
		std::cout << ANSI_DIM << "> " << ANSI_RESET_ALL;

		std::cout << ANSI_COLOR_BG_RED << ANSI_BLINK << ANSI_BOLD;
		std::cout << cmd << std::endl;
		reset_all_ansi();

		start_new_line();
		std::cout << "Is command needed? ";
		print_yes_or_no(needed);

		start_new_line();
		std::cout << "Command description: " << desc << std::endl;

		start_new_line();
		std::cout << "Do you accept after review? [yes]: ";
		std::string confirmation;
		std::getline(std::cin, confirmation);

		if (confirmation != "yes") {
			start_new_line();
			std::cout << "Not executing by command of user." << std::endl;
			if (needed) {
				start_new_line();
				std::cout << "This was a needed command, refusing to continue.\nFarewell." << std::endl;
				exit(1);
			}
			return -11;
		}

	} else {
		start_new_line();
		std::cout << ANSI_BOLD;
		std::cout << ANSI_COLOR_FG_GREEN << "executing: " << ANSI_COLOR_FG_DEFAULT;
		std::cout << ANSI_COLOR_FG_YELLOW << cmd;
		std::cout << ANSI_COLOR_FG_DEFAULT << ANSI_RESET_ALL;

		std::cout << ANSI_DIM << " # " << desc << ANSI_RESET_ALL << std::endl;
	}

	int retcode = system(cmd.c_str());
	if (retcode != 0 && needed)
		exit(retcode);
	return retcode;
}

std::optional<std::string> execute_cap_return(std::string cmd)
{
	std::string result;
	FILE * pipe = popen(cmd.c_str(), "r");
	if (pipe == NULL) {
		start_new_line();
		start_error_line();
		std::cout << "failed to execute command '" + cmd + "'." << std::endl;
		return {};
	}

	char buff[2048];
	while (fgets(buff, sizeof(buff), pipe) != NULL)
		result += buff;

	pclose(pipe);
	return result;
}
