#include "donglify/disk.hpp"

#include <filesystem>
#include <string>
#include <unistd.h>
#include <vector>

#include "donglify/ansi.hpp"
#include "donglify/execute.hpp"

bool disk_exists(std::string disk) { return std::filesystem::exists(disk); }

void unlock_disk(std::string disk, std::string cryptname)
{
	if (disk_exists("/dev/mapper/" + cryptname))
		return;

	std::string cmd, desc;
	cmd = "cryptsetup open " + disk + " " + cryptname;
	desc = "Unlock disk " + disk + " partition and name it as " + cryptname;
	execute(cmd, desc);
}

void unlock_uuid(std::string uuid, std::string cryptname)
{
	if (disk_exists("/dev/mapper/" + cryptname))
		return;

	std::string cmd, desc;
	cmd = "cryptsetup open /dev/disk/by-uuid/" + uuid + " " + cryptname;
	desc = "Unlock UUID=" + uuid + " partition and name it as " + cryptname;
	execute(cmd, desc);
}

std::string get_uuid_by_disk(std::string disk)
{
	if (!disk_exists(disk)) {
		start_new_line();
		start_warning_line();
		std::cout << "Failed to locate disk " << disk << ", but requested its UUID." << std::endl;
		return disk;
	}

	std::string cmd = "lsblk -n -oNAME,UUID " + disk + " --raw";
	std::optional<std::string> result = execute_cap_return(cmd);
	if (!result.has_value()) {
		start_new_line();
		start_warning_line();
		std::cout << "Failed to locate disk " << disk << ", but requested its UUID." << std::endl;
		return disk;
	}

	std::stringstream ss(result.value());
	std::vector<std::string> parts;

	std::string tmp;
	while (std::getline(ss, tmp, ' '))
		parts.push_back(tmp);

	if (parts.size() < 2) {
		start_new_line();
		start_warning_line();
		std::cout << "failed to parse lsblk output while trying to find UUID of " << disk << std::endl;
	}

	return parts[1];
}
