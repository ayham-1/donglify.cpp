#ifndef EXECUTE_HPP
#define EXECUTE_HPP

#include <optional>
#include <string>

int execute(std::string cmd, std::string desc = "", bool needed = true, bool ask = false);
std::optional<std::string> execute_cap_return(std::string cmd);

#endif
