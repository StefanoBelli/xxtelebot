#ifndef TGBOT_LOGGER_FACILITY_H
#define TGBOT_LOGGER_FACILITY_H

#include <string>
#include <iostream>

namespace tgbot {
	/*!
	 * @brief Logging facility for telegram-bot-api, see also: tgbot::methods::Api::getLogger()
	 */
	class Logger {
	private:
		std::ostream* stream { &std::cout };
		std::string dateFormat { "%Y/%m/%d %H:%M:%S" };
	public:
		Logger() = default;
		~Logger();
		
		/*!
		 * @brief copying by constructor allowed, BUT NOT ENCOURAGED!!
		 */
		Logger(Logger const&) = default; //YOU ARE NOT ENCOURAGED TO COPY THIS
		Logger(Logger&&) = delete;
		Logger& operator=(Logger const&) = delete;
		Logger& operator=(Logger&&) = delete;

		/*!
		 * @brief log some info...
		 * @param logInfo: info string
		 */
		void info(std::string const& logInfo) const;
		
		/*!
		 * @brief log some error...
		 * @param logError: error string
		 */
		void error(std::string const& logError) const;
		 
		/*!
		 * @brief checks for failbit
		 * @return is failbit enabled on the ostream?
		 */
		operator bool() const;

		/*!
		 * @brief set new stream
		 * @param newStream : your new stream (might be std::cout, std::cerr, an std::ofstream or whatever...)
		 */
		inline void setStream(std::ostream& newStream) {
			stream = &newStream;
		}
		
		/*!
		 * @brief set new date format, default is: "%Y/%m/%d %H:%M:%S"
		 * @param newDateFormat: your new date format
		 */
		inline void setDateFormat(std::string& newDateFormat) {
			dateFormat = std::move(newDateFormat);
		}
	};
}

#endif //TGBOT_LOGGER_FACILITY_H
