#ifndef ANSI_HPP
#define ANSI_HPP

#include <string>

/* formatting: set */

const std::string ANSI_BOLD = "\e[1m";
const std::string ANSI_DIM = "\e[2m";
const std::string ANSI_UNDERLINED = "\e[4m";
const std::string ANSI_BLINK = "\e[5m";
const std::string ANSI_REVERSE = "\e[7m";
const std::string ANSI_HIDDEN = "\e[8m";

/* formatting: reset */
const std::string ANSI_RESET_ALL = "\e[0m";
const std::string ANSI_RESET_BOLD = "\e[21m";
const std::string ANSI_RESET_DIM = "\e[22m";
const std::string ANSI_RESET_UNDERLINED = "\e[24m";
const std::string ANSI_RESET_BLINK = "\e[25m";
const std::string ANSI_RESET_REVERSE = "\e[27m";
const std::string ANSI_RESET_HIDDEN = "\e[28m";

/* colors: foreground */
const std::string ANSI_COLOR_FG_DEFAULT = "\e[39m";
const std::string ANSI_COLOR_FG_BLACK = "\e[30m";
const std::string ANSI_COLOR_FG_RED = "\e[31m";
const std::string ANSI_COLOR_FG_GREEN = "\e[32m";
const std::string ANSI_COLOR_FG_YELLOW = "\e[33m";
const std::string ANSI_COLOR_FG_BLUE = "\e[34m";
const std::string ANSI_COLOR_FG_MAGENTA = "\e[35m";
const std::string ANSI_COLOR_FG_CYAN = "\e[36m";
const std::string ANSI_COLOR_FG_LIGHT_GRAY = "\e[37m";
const std::string ANSI_COLOR_FG_DARK_GRAY = "\e[38m";
const std::string ANSI_COLOR_FG_LIGHT_RED = "\e[91m";
const std::string ANSI_COLOR_FG_LIGHT_GREEN = "\e[92m";
const std::string ANSI_COLOR_FG_LIGHT_YELLOW = "\e[93m";
const std::string ANSI_COLOR_FG_LIGHT_BLUE = "\e[94m";
const std::string ANSI_COLOR_FG_LIGHT_MAGENTA = "\e[95m";
const std::string ANSI_COLOR_FG_LIGHT_CYAN = "\e[96m";
const std::string ANSI_COLOR_FG_WHITE = "\e[97m";

/* colors: background */
const std::string ANSI_COLOR_BG_DEFAULT = "\e[49m";
const std::string ANSI_COLOR_BG_BLACK = "\e[40m";
const std::string ANSI_COLOR_BG_RED = "\e[41m";
const std::string ANSI_COLOR_BG_GREEN = "\e[42m";
const std::string ANSI_COLOR_BG_YELLOW = "\e[43m";
const std::string ANSI_COLOR_BG_BLUE = "\e[44m";
const std::string ANSI_COLOR_BG_MAGENTA = "\e[45m";
const std::string ANSI_COLOR_BG_CYAN = "\e[46m";
const std::string ANSI_COLOR_BG_LIGHT_GRAY = "\e[47m";
const std::string ANSI_COLOR_BG_DARK_GRAY = "\e[48m";
const std::string ANSI_COLOR_BG_LIGHT_RED = "\e[101m";
const std::string ANSI_COLOR_BG_LIGHT_GREEN = "\e[102m";
const std::string ANSI_COLOR_BG_LIGHT_YELLOW = "\e[103m";
const std::string ANSI_COLOR_BG_LIGHT_BLUE = "\e[104m";
const std::string ANSI_COLOR_BG_LIGHT_MAGENTA = "\e[105m";
const std::string ANSI_COLOR_BG_LIGHT_CYAN = "\e[106m";
const std::string ANSI_COLOR_BG_WHITE = "\e[107m";

#endif
