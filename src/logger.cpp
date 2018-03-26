#include <mutex>
#include <sstream>
#include <tgbot/logger.h>
#include <tgbot/utils/time.h>

std::mutex mtx;

tgbot::Logger::~Logger() {
	if(!stream->fail())
		stream->flush();
}

tgbot::Logger::operator bool() const {
	std::lock_guard<std::mutex> guard(mtx);
	return stream->fail();
}

void tgbot::Logger::info(std::string const& sInfo) const {
	if(stream->fail())
		return;
	
	std::stringstream fullLog;
	fullLog << "I: " 
			<< tgbot::utils::get_current_time(dateFormat) 
			<< " - "
			<< sInfo
			<< '\n';

	std::string const& logString = fullLog.str();

	std::lock_guard<std::mutex> guard(mtx);
	stream->write(logString.c_str(), logString.size());
	stream->flush();
}

void tgbot::Logger::error(std::string const& sError) const {
	if(stream->fail())
		return;
	
	std::stringstream fullLog;
	fullLog << "E! " 
			<< tgbot::utils::get_current_time(dateFormat) 
			<< " - "
			<< sError
			<< '\n';
	
	std::string const& logString = fullLog.str();

	std::lock_guard<std::mutex> guard(mtx);
	stream->write(logString.c_str(), logString.size());
	stream->flush();
}
