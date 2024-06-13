#include "donglify/disk.hpp"

#include <filesystem>
#include <string>
#include <sys/mount.h>
#include <unistd.h>
#include <vector>

#include "donglify/ansi.hpp"
#include "donglify/execute.hpp"
#include "donglify/state.hpp"

bool disk_exists(std::string disk) { return std::filesystem::exists(disk); }

bool disk_mount(std::string uuid, std::string target)
{
	if (!disk_exists("/dev/mapper/by-uuid/" + uuid))
		return false;

	std::filesystem::create_directory(target);

	return execute("mount UUID=" + uuid + " " + target) == 0;
}

bool disk_mount_mapper(std::string mapper, std::string target)
{
	if (!disk_exists("/dev/mapper/" + mapper))
		return false;

	std::filesystem::create_directory(target);

	return execute("mount UUID=" + mapper + " " + target) == 0;
}

bool disk_umount(std::string target)
{
	if (!std::filesystem::exists(target))
		return false;

	return execute("umount " + target);
}

bool crypt_unlock_disk(std::string disk, std::string cryptname)
{
	if (disk_exists("/dev/mapper/" + cryptname))
		return false;

	std::string cmd, desc;
	cmd = "cryptsetup open " + disk + " " + cryptname;
	desc = "Unlock disk " + disk + " partition and name it as " + cryptname;
	return execute(cmd, desc) == 0;
}

bool crypt_unlock_uuid(std::string uuid, std::string cryptname)
{
	if (disk_exists("/dev/mapper/" + cryptname))
		return false;

	std::string cmd, desc;
	cmd = "cryptsetup open /dev/disk/by-uuid/" + uuid + " " + cryptname;
	desc = "Unlock UUID=" + uuid + " partition and name it as " + cryptname;
	return execute(cmd, desc) == 0;
}

bool crypt_lock(std::string cryptname)
{
	if (!disk_exists("/dev/mapper/" + cryptname))
		return false;

	return execute("cryptsetup close " + cryptname, "relock encrypted disk");
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

bool dongle_mount_all()
{
	bool result1 = disk_mount(dongle_config_ini["dongle"]["efi_uuid"].as<std::string>(), "/efi");
	bool result2 =
	    crypt_unlock_uuid(dongle_config_ini["dongle"]["locked_boot_uuid"].as<std::string>(), "dongleboot");
	bool result3 = disk_mount(dongle_config_ini["dongle"]["unlocked_boot_uuid"].as<std::string>(), "/boot");
	bool result4 = disk_mount(dongle_config_ini["dongle"]["part_iso_uuid"].as<std::string>(), "/mnt/iso");

	start_new_line();
	good("mounted all necessarily points from donglified usb");
	return result1 && result2 && result3 && result4;
}

bool dongle_umount_all()
{
	bool result1 = disk_umount("/efi");
	bool result2 = disk_umount("/mnt/iso");
	bool result3 = crypt_lock("dongleboot");
	bool result4 = crypt_lock("donglepersist");

	start_new_line();
	good("system mounts are now clean, safe to remove dongle");
	return result1 && result2 && result3 && result4;
}
