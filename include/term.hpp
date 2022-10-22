#ifndef ICPP_TERM_H
#define ICPP_TERM_H

namespace icpp {
namespace term {
static const char *CLEAR_LINE = {"\33[2K"};
namespace color {
static const char *NO_COLOR = {"\033[0m"};
static const char *BLACK = {"\033[0;30m"};
static const char *GRAY = {"\033[1;30m"};
static const char *RED = {"\033[0;31m"};
static const char *LIGHT_RED = {"\033[1;31m"};
static const char *GREEN = {"\033[0;32m"};
static const char *LIGHT_GREEN = {"\033[1;32m"};
static const char *BROWN = {"\033[0;33m"};
static const char *YELLOW = {"\033[1;33m"};
static const char *BLUE = {"\033[0;34m"};
static const char *LIGHT_BLUE = {"\033[1;34m"};
static const char *PURPLE = {"\033[0;35m"};
static const char *LIGHT_PURPLE = {"\033[1;35m"};
static const char *CYAN = {"\033[0;36m"};
static const char *LIGHT_CYAN = {"\033[1;36m"};
static const char *LIGHT_GRAY = {"\033[1;37m"};
static const char *WHITE = {"\033[0;37m"};
}  // namespace color
}  // namespace term

}  // namespace icpp

#endif