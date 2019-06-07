#ifndef TGBOT_HTTPS_H
#define TGBOT_HTTPS_H

#include <curl/curl.h>
#include <unordered_map>
#include <map>
#include <string>
#include "../methods/types.h"

namespace tgbot {

/*!
 * @brief various utilities
 */
namespace utils {
/*!
 * @brief HTTP utilities, meant for project internal usage
 */
namespace http {

	struct value {
		const char* basicValue;
		const char* file;
		const char* mimeType;
	};

	using PostForms = std::unordered_map<const char*, value>;

	void __internal_Curl_GlobalInit();

	/*!
 	* @brief Very easy HTTP GET request using curl (see also: curlEasyInit() )
 	* @param c : curl instance
 	* @param full : complete URL
 	* @return HTTP response body
 	*/
	std::string get(CURL *c, const std::string &full);

	/*!
	 * @brief Multi part upload utils
	 * @param c : curl instance
	 * @param full : complete URL
	 * @param forms : see PostForms
	 * @return HTTP response body
	 */
	std::string multiPartUpload(CURL *c, const std::string& full, PostForms const& forms);

	/*!
 	* @brief Initialize CURL
 	* @return new CURL instance
 	*/
	CURL *curlEasyInit();

}  // namespace http

}  // namespace utils

}  // namespace tgbot

#endif
