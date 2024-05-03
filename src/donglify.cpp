#include <iostream>
#include <signal.h>
#include <stdlib.h>
#include <string.h>
#include <vector>

#if defined(_WIN32) || defined(WIN32)

void main() { std::cout << "haha too bad you are running windows!!!!\nno security for you hehe" << endl; }

#else

#define USAGE_STR                                                                                                      \
	"Usage: donglify load /dev/<name of usb><index of encrypted dongleboot>\n"                                     \
	"       donglify init /dev/<name of usb>"

void sigint_handler(sig_atomic_t s)
{
	(void)s;

	std::cout << "Farewell, Traveller." << std::endl;
	exit(0);
}

struct CommandStruct {
	std::string name;
	bool (*cmd_fn)(/*params*/);
};

std::vector<CommandStruct> donglify_cmds = {{"status", NULL},  {"list", NULL},     {"mount", NULL},
					    {"unmount", NULL}, {"add", NULL},      {"reinstall", NULL},
					    {"update", NULL},  {"iso list", NULL}, {"iso templates", NULL}};

void cmd_list()
{
	std::cout << "available commands: ";
	for (auto cmd : donglify_cmds) {
		std::cout << cmd.name << " ";
	}
	std::cout << std::endl;
}

int main(int argc, char ** argv)
{
	std::vector<std::string> args(argv, argv + argc);
	if (args[1] == "init" && args[2].length() == strlen("/dev/xyz")) {
		// dongle init partition
		std::cout << "initializing your dongle" << std::endl;
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

	std::string input;
	while (std::cout << "donglify> " && std::getline(std::cin, input)) {
		for (auto cmd : donglify_cmds) {
			if (cmd.name == input) {
				if (!cmd.cmd_fn()) {
					std::cout << "Execution of the previous command failed, exiting..."
						  << std::endl;
					exit(1);
				} else
					continue;
			}
		}

		std::cout << "Command not found." << std::endl;
		cmd_list();
	}

	system("lsblk");
	return 0;
}

#endif
