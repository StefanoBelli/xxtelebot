#ifndef TGBOT_HTTPS_H
#define TGBOT_HTTPS_H

#include <curl/curl.h>
#include <map>
#include <string>

namespace tgbot {

/*!
 * @brief various utilities
 */
namespace utils {
/*!
 * @brief HTTP utilities, meant for project internal usage
 */
namespace http {

/*!
 * @brief Very easy HTTP GET request using curl (see also: curlEasyInit() )
 * @param c : curl instance
 * @param full : complete URL
 * @return HTTP response body
 */
std::string get(CURL *c, const std::string &full);

/*!
 * @brief HTTP POST multipart file-upload specific to Telegram Bot API
 * (see also: curlEasyInit() )
 * @param c : curl instance
 * @param operation : full Telegram Bot API URL
 * @param chatId : target chat_id
 * @param mimeType : file MIME type (e.g. text/plain)
 * @param type : can be "document", "photo", ...
 * @param filename : file local path
 * @return HTTP response body
 */
std::string multiPartUpload(CURL *c, const std::string &operation,
                            const std::string &chatId,
                            const std::string &mimeType,
                            const std::string &type,
                            const std::string &filename);

// sendVideo
std::string
multiPartUpload(CURL *c, const std::string &operation,
                const std::string &chatId, const std::string &mimeType,
                const std::string &filename, const int &duration,
                const int &width, const int &height, const std::string &caption,
                const bool &disableNotification, const int &replyToMessageId,
                const std::string &replyMarkup);

// sendPhoto
// sendDocument
std::string
multiPartUpload(CURL *c, const std::string &operation,
                const std::string &chatId, const std::string &mimeType,
                const std::string &type, const std::string &filename,
                const std::string &caption, const bool &disableNotification,
                const int &replyToMessageId, const std::string &replyMarkup);

// sendAudio
std::string
multiPartUpload(CURL *c, const std::string &operation,
                const std::string &chatId, const std::string &mimeType,
                const std::string &filename, const std::string &caption,
                const int &duration, const std::string &performer,
                const std::string &title, const bool &disableNotification,
                const int &replyToMessageId, const std::string &replyMarkup);

// sendVoice
// sendVideoNote
std::string
multiPartUpload(CURL *c, const std::string &operation,
                const std::string &chatId, const std::string &mimeType,
                const std::string &type, const std::string &filename,
                const std::string &caption, const int &duration,
                const bool &disableNotification, const int &replyToMessageId,
                const std::string &replyMarkup);

// sendSticker
std::string multiPartUpload(CURL *c, const std::string &operation,
                            const std::string &chatId,
                            const std::string &filename,
                            const bool &disableNotification,
                            const int &replyToMessageId,
                            const std::string &replyMarkup);

/*!
 * @brief HTTP POST multipart file-upload specific to Telegram Bot API
 * self-signed certificates for webhooks (see also: curlEasyInit() )
 * @param c : curl instance
 * @param operation : full Telegram Bot API URL
 * @param cert : self-signed certificate local path
 * @param url : where we should get updates
 * @param maxConn : max connections
 * @param allowedUpdates : allowed updates
 * @return HTTP response body
 */
std::string multiPartUpload(CURL *c, const std::string &operation,
                            const std::string &cert, const std::string &url,
                            const int &maxConn,
                            const std::string &allowedUpdates = "");

/*!
 * @brief HTTP POST multipart sticker file (PNG) upload specific to Telegram Bot
 * API (see also: curlEasyInit() )
 * @param c : curl instance
 * @param operation : full Telegram Bot API URL
 * @param userId : target user_id
 * @param filename : file local path
 * @return HTTP response body
 */
std::string multiPartUpload(CURL *c, const std::string &operation,
                            const int &userId, const std::string &filename);

/*!
 * @brief HTTP POST multipart sticker file (add and create)
 * (PNG) upload specific to Telegram Bot API
 * (see also: curlEasyInit() )
 * @param c : curl instance
 * @param operation : full Telegram Bot API URL
 * @param userId : target user_id
 * @param name : Sticker set name
 * @param emoji : associated emoji with your new sticker
 * @param filename : PNG sticker local path
 * @param title : "" by default
 * @return HTTP response body
 */
std::string multiPartUpload(CURL *c, const std::string &operation,
                            const int &userId, const std::string &name,
                            const std::string &emoji,
                            const std::string &filename,
                            const std::string &title);

/*!
 * @brief HTTP POST multipart sticker file (add and create)
 * (PNG) upload specific to Telegram Bot API
 * (see also: curlEasyInit() )
 * @param c : curl instance
 * @param operation : full Telegram Bot API URL
 * @param userId : target user_id
 * @param name : Sticker set name
 * @param emoji : associated emoji with your new sticker
 * @param serializedMaskPosition : JSON-encoded mask position object
 * @param filename : PNG sticker local path
 * @param title
 * @return HTTP response body
 */
std::string multiPartUpload(CURL *c, const std::string &operation,
                            const int &userId, const std::string &name,
                            const std::string &emoji,
                            const std::string &serializedMaskPosition,
                            const std::string &filename,
                            const std::string &title);

/*!
 * @brief Initialize CURL
 * @return new CURL instance
 */
CURL *curlEasyInit();

} // namespace http

} // namespace utils

} // namespace tgbot

#endif
