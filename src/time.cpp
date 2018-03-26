#include <ctime>
#include <tgbot/utils/time.h>

std::string tgbot::utils::get_current_time(const std::string& format) {
	const std::time_t current_time = std::time(nullptr);
	const std::tm *local = std::localtime(&current_time);

	if(local) {
		char timebuf[100];
		if(std::strftime(timebuf, 100, format.c_str(), local))
			return timebuf;
		else
			return "clock: bad result";
	} 

	return "clock: failure";
}
