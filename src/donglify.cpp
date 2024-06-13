#include <iostream>
#include <signal.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <vector>

#include "donglify/ansi.hpp"
#include "donglify/execute.hpp"

#include "donglify/cmds/initialize_partitions.hpp"

#if defined(_WIN32) || defined(WIN32)

void main() { std::cout << "haha too bad you are running windows!!!!\nno security for you hehe" << endl; }

#else

#define USAGE_STR                                                                                                      \
	"Usage: donglify load /dev/<name of usb><index of encrypted dongleboot>\n"                                     \
	"       donglify init /dev/<name of usb>"

void sigint_handler(sig_atomic_t s)
{
	(void)s;

	std::cout << std::endl << "Farewell, Traveller." << std::endl;
	exit(0);
}

struct CommandStruct {
	std::string name;
	bool (*cmd_fn)(/*params*/);
};

std::vector<CommandStruct> donglify_cmds = {
    {"status", NULL},    {"list", NULL},   {"mount", NULL},    {"unmount", NULL},       {"add", NULL},
    {"reinstall", NULL}, {"update", NULL}, {"iso list", NULL}, {"iso templates", NULL}, {"exit", NULL}};

void cmd_help()
{
	std::cout << "available commands: ";
	std::cout << ANSI_COLOR_FG_LIGHT_CYAN << ANSI_DIM;
	for (auto cmd : donglify_cmds) {
		std::cout << cmd.name << " ";
	}
	std::cout << ANSI_COLOR_FG_DEFAULT << ANSI_RESET_ALL;
	std::cout << std::endl;
}

int main(int argc, char ** argv)
{
	if (geteuid() != 0) {
		std::cout << "This program does big boy stuff, and therefore it requires privileged permissions."
			  << std::endl;
		std::cout << "-- chad program" << std::endl;
		exit(1);
	}
	std::vector<std::string> args(argv, argv + argc);
	if (argc == 1) {
		std::cout << USAGE_STR << std::endl;
		exit(127);
	} else if (args[1] == "init" && args[2].length() == strlen("/dev/xyz")) {
		// dongle init partition
		std::cout << "initializing your dongle" << std::endl;
		/* TODO(ayham-1): initialize_partiions(path) */
		cmd_initialize_partitions(args[2]);
	} else if (args[1] == "load" && args[2].length() >= strlen("/dev/xyz0")) {
		// dongle load partition
		std::cout << "loading your dongle" << std::endl;
	} else {
		std::cout << USAGE_STR << std::endl;
		exit(127);
	}
	signal(SIGINT, sigint_handler);

	std::cout << "Welcome to donglify!" << std::endl;

	/* TODO(ayham-1): locate_and_load_config() */

	cmd_help();
	std::string input;
	while (true) {
		std::cout << std::endl << ANSI_COLOR_FG_DARK_GRAY << "donglify> " << ANSI_COLOR_FG_DEFAULT;
		if (!std::getline(std::cin, input))
			raise(SIGINT);

		if (input == "exit")
			raise(SIGINT);

		std::cout << execute("sudo lsblk", "", true, false) << std::endl;

		bool command_not_found = false;
		for (auto cmd : donglify_cmds) {
			if (cmd.name == input) {
				if (!cmd.cmd_fn) {
					std::cout << std::endl;
					std::cout << "Command is not implemented yet!" << std::endl;
				} else if (!cmd.cmd_fn || !cmd.cmd_fn()) {
					std::cout << std::endl;
					std::cout << "Execution of the previous command failed, exiting..."
						  << std::endl;
					exit(1);
				} else {
					command_not_found = true;
					break;
				}
			}
		}

		if (command_not_found) {
			cmd_help();
		}
	}
	return 0;
}

#endif
