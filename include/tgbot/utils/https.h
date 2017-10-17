#ifndef TGBOT_HTTPS_H
#define TGBOT_HTTPS_H

#include <string>
#include <curl/curl.h>

namespace tgbot {

	namespace utils {

		/*!
		 * @brief HTTP utilities, meant for project internal usage
		 */
		namespace http {

			std::string get(CURL* c, const std::string& full);

			std::string multiPartUpload(CURL* c, const std::string& operation,
					const int& chatId, 
					const std::string& mimeType, 
					const std::string& type,
					const std::string& filename);

            std::string multiPartUpload(CURL* c, const std::string& operation,
                                        const std::string& cert,
                                        const std::string& url,
                                        const int& maxConn,
                                        const std::string& allowedUpdates = "");

			CURL* curlEasyInit();

		} //http

	} //utils

} //tgbot

#endif
