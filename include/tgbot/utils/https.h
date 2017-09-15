#ifndef TGBOT_HTTPS_H
#define TGBOT_HTTPS_H

#include <string>
#include <exception>

namespace tgbot {

	namespace utils {
		
		/*!
		 * @brief HTTP utilities, meant for project internal usage
		 */
		namespace http {

			struct Response {
				std::string body;
				int code;
			};

			Response get(const std::string& full);
			Response multiPartUpload(const std::string& operation, 
					const int& chatId, 
					const std::string& type, 
					const std::string& filename);

			bool globalCurlInitializer(const std::string& agent);
			bool globalCurlCleanup();

			class HttpException : public std::exception {
				public:
					virtual const char* what() const noexcept;
			};

		} //http

	} //utils

} //tgbot

#endif
