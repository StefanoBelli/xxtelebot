#ifndef TGBOT_HTTPS_H
#define TGBOT_HTTPS_H

#include <string>
#include <exception>

#include <curl/curl.h>

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

			Response get(CURL* c, const std::string& full);
			Response multiPartUpload(CURL* c, const std::string& operation, 
					const int& chatId, 
					const std::string& mimeType, 
					const std::string& type,
					const std::string& filename);

			CURL* curlEasyInit(const std::string& agent);

			class HttpException : public std::exception {
				public:
					virtual const char* what() const noexcept;
			};

		} //http

	} //utils

} //tgbot

#endif
