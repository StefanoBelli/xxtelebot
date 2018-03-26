#ifndef TGBOT_UTILS_TIME_H
#define TGBOT_UTILS_TIME_H

#include <string>

namespace tgbot {
namespace utils {
	/*!
	 * @brief get current localtime, with specific formatting
	 * @param fmt: format string for time
	 * @return current localtime with "fmt" formatting
	 */
	std::string get_current_time(const std::string& fmt);
	
} //namespace utils
} //namespace tgbot

#endif //TGBOT_UTILS_TIME_H
