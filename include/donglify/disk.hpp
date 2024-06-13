#ifndef MISC_HPP
#define MISC_HPP

#include <string>

bool disk_exists(std::string disk);

void unlock_disk(std::string disk, std::string cryptname);
void unlock_uuid(std::string uuid, std::string cryptname);

std::string get_uuid_by_disk(std::string disk);

#endif
