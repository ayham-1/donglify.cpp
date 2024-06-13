#ifndef MISC_HPP
#define MISC_HPP

#include <string>

bool disk_exists(std::string disk);
bool disk_mount(std::string uuid, std::string target);
bool disk_mount_mapper(std::string mapper, std::string target);
bool disk_umount(std::string target);

bool crypt_unlock_disk(std::string disk, std::string cryptname);
bool crypt_unlock_uuid(std::string uuid, std::string cryptname);
bool crypt_lock(std::string cryptname);

std::string get_uuid_by_disk(std::string disk);

bool dongle_mount_all();
bool dongle_umount_all();

#endif
