#include "donglify/cmds/initialize_partitions.hpp"

#include "donglify/ansi.hpp"
#include "donglify/disk.hpp"
#include "donglify/execute.hpp"
#include "donglify/state.hpp"

bool cmd_initialize_partitions(std::string dongle_path)
{
	start_new_line();
	std::cout << ANSI_REVERSE << ANSI_BLINK << ANSI_BOLD;
	std::cout << ANSI_COLOR_FG_RED;
	std::cout << "Acknowledge that the following procedure *will* destroy ALL data on ";
	std::cout << dongle_path << std::endl;
	std::cout << ANSI_COLOR_FG_DEFAULT;
	std::cout << ANSI_RESET_ALL;
	start_new_line();
	std::cout << "YOU WILL NOT BE ASKED AGAIN" << std::endl;

	start_new_line();
	std::cout << "Acknowledge by writing the following in caps: DESTROY MY DONGLE" << std::endl;
	std::string ack;
	std::getline(std::cin, ack);
	if (ack != "DESTROY MY DONGLE") {
		start_new_line();
		std::cout << "Stopping procedure by user command. No data was lost." << std::endl;
		start_new_line();
		std::cout << "Farewell." << std::endl;
		exit(-11);
	}

	std::string cmd, desc, cmd_output;

	cmd = "parted " + dongle_path + " mklabel gpt";
	desc = "set USB partition table as GPT";
	execute(cmd, desc);

	cmd = "lsblk -n -oNAME,SIZE " + dongle_path;
	std::optional<std::string> cmd_result = execute_cap_return(cmd);
	if (!cmd_result.has_value()) {
		start_new_line();
		start_error_line();
		std::cout << "failed determining size of dongle" << std::endl;
		exit(1);
	}
	cmd_output = cmd_result.value();

	double dongle_size =
	    std::stod(cmd_output.substr(cmd_output.find(" "), cmd_output.length() - cmd_output.find(" ") - 1));

	start_new_line();
	std::cout << "dongle has size: " << dongle_size << "GB" << std::endl;

	int dongle_isos_size = int(0.5 * float(dongle_size) * 1024);
	int dongle_persistent_size = int(0.5 * float(dongle_size) * 1024);

	start_new_line();
	std::cout << "recommended partition scheme: " << std::endl;
	start_new_line();
	std::cout << "DONGLE_EFI partition: 256 MB" << std::endl;
	start_new_line();
	std::cout << "DONGLE_BOOT partition: 2048 MB" << std::endl;
	start_new_line();
	std::cout << "DONGLE_ISOs partition: " << dongle_isos_size << " MB" << std::endl;
	start_new_line();
	std::cout << "DONGLE_PERSISTENT partition: " << dongle_persistent_size << " MB" << std::endl;

	std::string requested_iso_size, requested_persistent_size;
	start_new_line();
	std::cout << "What would you like to have for ISO partition size in MB? [empty for same] ";
	std::getline(std::cin, requested_iso_size);
	start_new_line();
	std::cout << "What would you like to have for persistent partition size in MB? [empty for same] ";
	std::getline(std::cin, requested_persistent_size);

	if (requested_iso_size != "")
		dongle_isos_size = stoi(requested_iso_size);
	if (requested_persistent_size != "")
		dongle_persistent_size = stoi(requested_persistent_size);

	int current_offset = 8;
	std::string cmd_parted = "parted -a optimal";
	cmd = cmd_parted + " " + dongle_path + " mkpart \"DONGLE_EFI\" fat32 " + std::to_string(current_offset) +
	      "MB 256MB";
	desc = "create efi partition on dongle";
	execute(cmd, desc);

	cmd = cmd_parted + " " + dongle_path + " set 1 esp on";
	desc = "mark /efi as esp";
	execute(cmd, desc);

	current_offset += 256 + 8;

	cmd = cmd_parted + " " + dongle_path + " mkpart \"DONGLE_BOOT\" " + std::to_string(current_offset) + "MB " +
	      std::to_string(2048 + current_offset) + "MB";
	desc = "create boot partition on dongle";
	execute(cmd, desc);

	cmd = cmd_parted + " " + dongle_path + " set 2 boot on";
	desc = "mark /boot as boot";
	execute(cmd, desc);

	current_offset += 2048 + 8;

	if (dongle_isos_size != 0) {
		cmd = cmd_parted + " " + dongle_path + " mkpart \"DONGLE_ISOs\" " + std::to_string(current_offset) +
		      "MB " + std::to_string(dongle_isos_size + current_offset) + "MB";
		desc = "create ISOs partition on dongle";
		execute(cmd, desc);
		current_offset += dongle_isos_size + 8;
	}

	if (dongle_persistent_size != 0) {
		cmd = cmd_parted + " " + dongle_path + " mkpart \"DONGLE_PERSISTENT\" " +
		      std::to_string(current_offset) + "MB 100%";
		desc = "create persistent partition on dongle";
		execute(cmd, desc);
	}

	cmd = "mkfs.vfat -n DONGLE_EFI -F 32 " + dongle_path + "1";
	desc = "format DONGLE_EFI as FAT16";
	execute(cmd, desc);

	cmd = "cryptsetup luksFormat --type luks1 " + dongle_path + "2";
	desc = "encrypt dongle's /boot partition, user will be asked for passphrase automatically";
	execute(cmd, desc);

	unlock_disk(dongle_path + "2", "dongleboot");

	cmd = "mkfs.ext4 /dev/mapper/dongleboot";
	desc = "format dongle's /boot partition as ext4";
	execute(cmd, desc);

	cmd = "mkfs.ext4 " + dongle_path + "3";
	desc = "format dongle's ISOs partition as ext4";
	execute(cmd, desc);

	cmd = "cryptsetup luksFormat --type luks2 " + dongle_path + "4";
	desc = "encrypt dongle's persistent partition, user will be asked for passphrase automatically";
	execute(cmd, desc);

	unlock_disk(dongle_path + "4", "donglepersist");

	cmd = "mkfs.ext4 /dev/mapper/donglepersist";
	desc = "format dongle's persistent partition";
	execute(cmd, desc);

	/* TODO(ayham-1): dongle.ini */

	// # grub-install
	//     dongle_mount_all()
	//     grub_encrypted_install()
	//
	//     dongle_save_config()
	system("lsblk -f");
	start_new_line();
	good("dongle's partition initialization done");
	start_new_line();
	std::cout << "you are recommended to start adding system installs onto your dongle" << std::endl;
	exit(0);

	return true;
}
