#ifndef ANSI_HPP
#define ANSI_HPP

#include <string>

/* formatting: set */

const std::string ANSI_BOLD = "\033[1m";
const std::string ANSI_DIM = "\033[2m";
const std::string ANSI_UNDERLINED = "\033[4m";
const std::string ANSI_BLINK = "\033[5m";
const std::string ANSI_REVERSE = "\033[7m";
const std::string ANSI_HIDDEN = "\033[8m";

/* formatting: reset */
const std::string ANSI_RESET_ALL = "\033[0m";
const std::string ANSI_RESET_BOLD = "\033[21m";
const std::string ANSI_RESET_DIM = "\033[22m";
const std::string ANSI_RESET_UNDERLINED = "\033[24m";
const std::string ANSI_RESET_BLINK = "\033[25m";
const std::string ANSI_RESET_REVERSE = "\033[27m";
const std::string ANSI_RESET_HIDDEN = "\033[28m";

/* colors: foreground */
const std::string ANSI_COLOR_FG_DEFAULT = "\033[39m";
const std::string ANSI_COLOR_FG_BLACK = "\033[30m";
const std::string ANSI_COLOR_FG_RED = "\033[31m";
const std::string ANSI_COLOR_FG_GREEN = "\033[32m";
const std::string ANSI_COLOR_FG_YELLOW = "\033[33m";
const std::string ANSI_COLOR_FG_BLUE = "\033[34m";
const std::string ANSI_COLOR_FG_MAGENTA = "\033[35m";
const std::string ANSI_COLOR_FG_CYAN = "\033[36m";
const std::string ANSI_COLOR_FG_LIGHT_GRAY = "\033[37m";
const std::string ANSI_COLOR_FG_DARK_GRAY = "\033[38m";
const std::string ANSI_COLOR_FG_LIGHT_RED = "\033[91m";
const std::string ANSI_COLOR_FG_LIGHT_GREEN = "\033[92m";
const std::string ANSI_COLOR_FG_LIGHT_YELLOW = "\033[93m";
const std::string ANSI_COLOR_FG_LIGHT_BLUE = "\033[94m";
const std::string ANSI_COLOR_FG_LIGHT_MAGENTA = "\033[95m";
const std::string ANSI_COLOR_FG_LIGHT_CYAN = "\033[96m";
const std::string ANSI_COLOR_FG_WHITE = "\033[97m";

/* colors: background */
const std::string ANSI_COLOR_BG_DEFAULT = "\033[49m";
const std::string ANSI_COLOR_BG_BLACK = "\033[40m";
const std::string ANSI_COLOR_BG_RED = "\033[41m";
const std::string ANSI_COLOR_BG_GREEN = "\033[42m";
const std::string ANSI_COLOR_BG_YELLOW = "\033[43m";
const std::string ANSI_COLOR_BG_BLUE = "\033[44m";
const std::string ANSI_COLOR_BG_MAGENTA = "\033[45m";
const std::string ANSI_COLOR_BG_CYAN = "\033[46m";
const std::string ANSI_COLOR_BG_LIGHT_GRAY = "\033[47m";
const std::string ANSI_COLOR_BG_DARK_GRAY = "\033[48m";
const std::string ANSI_COLOR_BG_LIGHT_RED = "\033[101m";
const std::string ANSI_COLOR_BG_LIGHT_GREEN = "\033[102m";
const std::string ANSI_COLOR_BG_LIGHT_YELLOW = "\033[103m";
const std::string ANSI_COLOR_BG_LIGHT_BLUE = "\033[104m";
const std::string ANSI_COLOR_BG_LIGHT_MAGENTA = "\033[105m";
const std::string ANSI_COLOR_BG_LIGHT_CYAN = "\033[106m";
const std::string ANSI_COLOR_BG_WHITE = "\033[107m";

#endif
