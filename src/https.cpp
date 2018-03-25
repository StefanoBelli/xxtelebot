#include <sstream>
#include <stdexcept>
#include <tgbot/utils/https.h>

#define unused __attribute__((__unused__))

using namespace tgbot::utils::http;

static size_t write_data(const char *ptr, unused size_t nbs, size_t count,
                         void *dest) {
  static_cast<std::string *>(dest)->append(ptr);
  return count;
}

CURL *tgbot::utils::http::curlEasyInit() {
  CURL *curlInst = curl_easy_init();
  if (!curlInst)
    return nullptr;

  curl_easy_setopt(curlInst, CURLOPT_FOLLOWLOCATION, 1L);
  curl_easy_setopt(curlInst, CURLOPT_WRITEFUNCTION, write_data);

  return curlInst;
}

std::string tgbot::utils::http::get(CURL *c, const std::string &full) {
  if (!c)
    throw std::runtime_error("CURL is actually a null pointer :/");

  std::string body;
  curl_easy_setopt(c, CURLOPT_HTTPGET, 1L);
  curl_easy_setopt(c, CURLOPT_WRITEDATA, &body);
  curl_easy_setopt(c, CURLOPT_URL, full.c_str());

  CURLcode code = curl_easy_perform(c);
  if (code != CURLE_OK && code != CURLE_GOT_NOTHING)
    throw std::runtime_error(curl_easy_strerror(code));

  return body;
}

std::string tgbot::utils::http::multiPartUpload(CURL *c,
                                                const std::string &operation,
                                                const std::string &chatId,
                                                const std::string &mimeType,
                                                const std::string &type,
                                                const std::string &filename) {

  if (!c)
    throw std::runtime_error("CURL is actually a null pointer");

  curl_httppost *multiPost = nullptr;
  curl_httppost *end = nullptr;
  std::string body;

  curl_formadd(&multiPost, &end, CURLFORM_COPYNAME, "chat_id",
               CURLFORM_COPYCONTENTS, chatId.c_str(), CURLFORM_END);

  curl_formadd(&multiPost, &end, CURLFORM_COPYNAME, type.c_str(),
               CURLFORM_CONTENTTYPE, mimeType.c_str(), CURLFORM_FILE,
               filename.c_str(), CURLFORM_END);

  curl_easy_setopt(c, CURLOPT_HTTPPOST, multiPost);
  curl_easy_setopt(c, CURLOPT_WRITEDATA, &body);
  curl_easy_setopt(c, CURLOPT_URL, operation.c_str());

  CURLcode code;
  if ((code = curl_easy_perform(c)) != CURLE_OK)
    throw std::runtime_error(curl_easy_strerror(code));

  return body;
}

std::string
tgbot::utils::http::multiPartUpload(CURL *c, const std::string &operation,
                                    const std::string &cert,
                                    const std::string &url, const int &maxConn,
                                    const std::string &allowedUpdates) {
  if (!c)
    throw std::runtime_error("CURL is actually a null pointer");

  curl_httppost *multiPost = nullptr;
  curl_httppost *end = nullptr;
  std::string body;

  curl_formadd(&multiPost, &end, CURLFORM_COPYNAME, "url",
               CURLFORM_COPYCONTENTS, url.c_str(), CURLFORM_END);

  curl_formadd(&multiPost, &end, CURLFORM_COPYNAME, "certificate",
               CURLFORM_FILE, cert.c_str(), CURLFORM_END);

  curl_formadd(&multiPost, &end, CURLFORM_COPYNAME, "max_connections",
               CURLFORM_COPYCONTENTS, std::to_string(maxConn).c_str(),
               CURLFORM_END);

  if (allowedUpdates != "")
    curl_formadd(&multiPost, &end, CURLFORM_COPYNAME, "allowed_updates",
                 CURLFORM_COPYCONTENTS, allowedUpdates.c_str(), CURLFORM_END);

  curl_easy_setopt(c, CURLOPT_HTTPPOST, multiPost);
  curl_easy_setopt(c, CURLOPT_WRITEDATA, &body);
  curl_easy_setopt(c, CURLOPT_URL, operation.c_str());

  CURLcode code;
  if ((code = curl_easy_perform(c)) != CURLE_OK)
    throw std::runtime_error(curl_easy_strerror(code));

  return body;
}

std::string tgbot::utils::http::multiPartUpload(CURL *c,
                                                const std::string &operation,
                                                const int &userId,
                                                const std::string &filename) {
  if (!c)
    throw std::runtime_error("CURL is actually a null pointer");

  curl_httppost *multiPost = nullptr;
  curl_httppost *end = nullptr;
  std::string body;

  curl_formadd(&multiPost, &end, CURLFORM_COPYNAME, "user_id",
               CURLFORM_COPYCONTENTS, std::to_string(userId).c_str(),
               CURLFORM_END);

  curl_formadd(&multiPost, &end, CURLFORM_COPYNAME, "png_sticker",
               CURLFORM_CONTENTTYPE, "image/png", CURLFORM_FILE,
               filename.c_str(), CURLFORM_END);

  curl_easy_setopt(c, CURLOPT_HTTPPOST, multiPost);
  curl_easy_setopt(c, CURLOPT_WRITEDATA, &body);
  curl_easy_setopt(c, CURLOPT_URL, operation.c_str());

  CURLcode code;
  if ((code = curl_easy_perform(c)) != CURLE_OK)
    throw std::runtime_error(curl_easy_strerror(code));

  return body;
}

std::string tgbot::utils::http::multiPartUpload(
    CURL *c, const std::string &operation, const int &userId,
    const std::string &name, const std::string &emoji,
    const std::string &filename, const std::string &title) {
  if (!c)
    throw std::runtime_error("CURL is actually a null pointer");

  curl_httppost *multiPost = nullptr;
  curl_httppost *end = nullptr;
  std::string body;

  curl_formadd(&multiPost, &end, CURLFORM_COPYNAME, "user_id",
               CURLFORM_COPYCONTENTS, std::to_string(userId).c_str(),
               CURLFORM_END);

  curl_formadd(&multiPost, &end, CURLFORM_COPYNAME, "name",
               CURLFORM_COPYCONTENTS, name.c_str(), CURLFORM_END);

  curl_formadd(&multiPost, &end, CURLFORM_COPYNAME, "emoji",
               CURLFORM_COPYCONTENTS, emoji.c_str(), CURLFORM_END);

  curl_formadd(&multiPost, &end, CURLFORM_COPYNAME, "png_sticker",
               CURLFORM_CONTENTTYPE, "image/png", CURLFORM_FILE,
               filename.c_str(), CURLFORM_END);

  if (title != "")
    curl_formadd(&multiPost, &end, CURLFORM_COPYNAME, "title",
                 CURLFORM_COPYCONTENTS, title.c_str(), CURLFORM_END);

  curl_easy_setopt(c, CURLOPT_HTTPPOST, multiPost);
  curl_easy_setopt(c, CURLOPT_WRITEDATA, &body);
  curl_easy_setopt(c, CURLOPT_URL, operation.c_str());

  CURLcode code;
  if ((code = curl_easy_perform(c)) != CURLE_OK)
    throw std::runtime_error(curl_easy_strerror(code));

  return body;
}

std::string tgbot::utils::http::multiPartUpload(
    CURL *c, const std::string &operation, const int &userId,
    const std::string &name, const std::string &emoji,
    const std::string &serializedMaskPosition, const std::string &filename,
    const std::string &title) {
  if (!c)
    throw std::runtime_error("CURL is actually a null pointer");

  curl_httppost *multiPost = nullptr;
  curl_httppost *end = nullptr;
  std::string body;

  curl_formadd(&multiPost, &end, CURLFORM_COPYNAME, "user_id",
               CURLFORM_COPYCONTENTS, std::to_string(userId).c_str(),
               CURLFORM_END);

  curl_formadd(&multiPost, &end, CURLFORM_COPYNAME, "name",
               CURLFORM_COPYCONTENTS, name.c_str(), CURLFORM_END);

  curl_formadd(&multiPost, &end, CURLFORM_COPYNAME, "emoji",
               CURLFORM_COPYCONTENTS, emoji.c_str(), CURLFORM_END);

  curl_formadd(&multiPost, &end, CURLFORM_COPYNAME, "mask_position",
               CURLFORM_COPYCONTENTS, serializedMaskPosition.c_str(),
               CURLFORM_END);

  curl_formadd(&multiPost, &end, CURLFORM_COPYNAME, "png_sticker",
               CURLFORM_CONTENTTYPE, "image/png", CURLFORM_FILE,
               filename.c_str(), CURLFORM_END);

  if (title != "")
    curl_formadd(&multiPost, &end, CURLFORM_COPYNAME, "title",
                 CURLFORM_COPYCONTENTS, title.c_str(), CURLFORM_END);

  curl_easy_setopt(c, CURLOPT_HTTPPOST, multiPost);
  curl_easy_setopt(c, CURLOPT_WRITEDATA, &body);
  curl_easy_setopt(c, CURLOPT_URL, operation.c_str());

  CURLcode code;
  if ((code = curl_easy_perform(c)) != CURLE_OK)
    throw std::runtime_error(curl_easy_strerror(code));

  return body;
}

std::string tgbot::utils::http::multiPartUpload(
    CURL *c, const std::string &operation, const std::string &chatId,
    const std::string &mimeType, const std::string &filename,
    const int &duration, const int &width, const int &height,
    const std::string &caption, const bool &disableNotification,
    const int &replyToMessageId, const std::string &replyMarkup) {
  if (!c)
    throw std::runtime_error("CURL is actually a null pointer");

  curl_httppost *multiPost = nullptr;
  curl_httppost *end = nullptr;
  std::string body;

  curl_formadd(&multiPost, &end, CURLFORM_COPYNAME, "chat_id",
               CURLFORM_COPYCONTENTS, chatId.c_str(), CURLFORM_END);

  curl_formadd(&multiPost, &end, CURLFORM_COPYNAME, "video",
               CURLFORM_CONTENTTYPE, mimeType.c_str(), CURLFORM_FILE,
               filename.c_str(), CURLFORM_END);

  if (duration != -1)
    curl_formadd(&multiPost, &end, CURLFORM_COPYNAME, "duration",
                 CURLFORM_COPYCONTENTS, std::to_string(duration).c_str(),
                 CURLFORM_END);

  if (width != -1)
    curl_formadd(&multiPost, &end, CURLFORM_COPYNAME, "width",
                 CURLFORM_COPYCONTENTS, std::to_string(width).c_str(),
                 CURLFORM_END);

  if (height != -1)
    curl_formadd(&multiPost, &end, CURLFORM_COPYNAME, "height",
                 CURLFORM_COPYCONTENTS, std::to_string(height).c_str(),
                 CURLFORM_END);

  if (caption != "")
    curl_formadd(&multiPost, &end, CURLFORM_COPYNAME, "caption",
                 CURLFORM_COPYCONTENTS, caption.c_str(), CURLFORM_END);

  if (disableNotification)
    curl_formadd(&multiPost, &end, CURLFORM_COPYNAME, "disable_notification",
                 CURLFORM_COPYCONTENTS, "true", CURLFORM_END);

  if (replyToMessageId != -1)
    curl_formadd(&multiPost, &end, CURLFORM_COPYNAME, "reply_to_message_id",
                 CURLFORM_COPYCONTENTS,
                 std::to_string(replyToMessageId).c_str(), CURLFORM_END);

  if (replyMarkup != "")
    curl_formadd(&multiPost, &end, CURLFORM_COPYNAME, "reply_markup",
                 CURLFORM_COPYCONTENTS, replyMarkup.c_str(), CURLFORM_END);

  curl_easy_setopt(c, CURLOPT_HTTPPOST, multiPost);
  curl_easy_setopt(c, CURLOPT_WRITEDATA, &body);
  curl_easy_setopt(c, CURLOPT_URL, operation.c_str());

  CURLcode code;
  if ((code = curl_easy_perform(c)) != CURLE_OK)
    throw std::runtime_error(curl_easy_strerror(code));

  return body;
}

std::string tgbot::utils::http::multiPartUpload(
    CURL *c, const std::string &operation, const std::string &chatId,
    const std::string &mimeType, const std::string &filename,
    const std::string &caption, const int &duration,
    const std::string &performer, const std::string &title,
    const bool &disableNotification, const int &replyToMessageId,
    const std::string &replyMarkup) {
  if (!c)
    throw std::runtime_error("CURL is actually a null pointer");

  curl_httppost *multiPost = nullptr;
  curl_httppost *end = nullptr;
  std::string body;

  curl_formadd(&multiPost, &end, CURLFORM_COPYNAME, "chat_id",
               CURLFORM_COPYCONTENTS, chatId.c_str(), CURLFORM_END);

  curl_formadd(&multiPost, &end, CURLFORM_COPYNAME, "audio",
               CURLFORM_CONTENTTYPE, mimeType.c_str(), CURLFORM_FILE,
               filename.c_str(), CURLFORM_END);

  if (duration != -1)
    curl_formadd(&multiPost, &end, CURLFORM_COPYNAME, "duration",
                 CURLFORM_COPYCONTENTS, std::to_string(duration).c_str(),
                 CURLFORM_END);

  if (performer != "")
    curl_formadd(&multiPost, &end, CURLFORM_COPYNAME, "performer",
                 CURLFORM_COPYCONTENTS, performer.c_str(), CURLFORM_END);

  if (title != "")
    curl_formadd(&multiPost, &end, CURLFORM_COPYNAME, "title",
                 CURLFORM_COPYCONTENTS, title.c_str(), CURLFORM_END);

  if (caption != "")
    curl_formadd(&multiPost, &end, CURLFORM_COPYNAME, "caption",
                 CURLFORM_COPYCONTENTS, caption.c_str(), CURLFORM_END);

  if (disableNotification)
    curl_formadd(&multiPost, &end, CURLFORM_COPYNAME, "disable_notification",
                 CURLFORM_COPYCONTENTS, "true", CURLFORM_END);

  if (replyToMessageId != -1)
    curl_formadd(&multiPost, &end, CURLFORM_COPYNAME, "reply_to_message_id",
                 CURLFORM_COPYCONTENTS,
                 std::to_string(replyToMessageId).c_str(), CURLFORM_END);

  if (replyMarkup != "")
    curl_formadd(&multiPost, &end, CURLFORM_COPYNAME, "reply_markup",
                 CURLFORM_COPYCONTENTS, replyMarkup.c_str(), CURLFORM_END);

  curl_easy_setopt(c, CURLOPT_HTTPPOST, multiPost);
  curl_easy_setopt(c, CURLOPT_WRITEDATA, &body);
  curl_easy_setopt(c, CURLOPT_URL, operation.c_str());

  CURLcode code;
  if ((code = curl_easy_perform(c)) != CURLE_OK)
    throw std::runtime_error(curl_easy_strerror(code));

  return body;
}

std::string tgbot::utils::http::multiPartUpload(
    CURL *c, const std::string &operation, const std::string &chatId,
    const std::string &filename, const bool &disableNotification,
    const int &replyToMessageId, const std::string &replyMarkup) {
  if (!c)
    throw std::runtime_error("CURL is actually a null pointer");

  curl_httppost *multiPost = nullptr;
  curl_httppost *end = nullptr;
  std::string body;

  curl_formadd(&multiPost, &end, CURLFORM_COPYNAME, "chat_id",
               CURLFORM_COPYCONTENTS, chatId.c_str(), CURLFORM_END);

  curl_formadd(&multiPost, &end, CURLFORM_COPYNAME, "png_sticker",
               CURLFORM_CONTENTTYPE, "image/png", CURLFORM_FILE,
               filename.c_str(), CURLFORM_END);

  if (disableNotification)
    curl_formadd(&multiPost, &end, CURLFORM_COPYNAME, "disable_notification",
                 CURLFORM_COPYCONTENTS, "true", CURLFORM_END);

  if (replyToMessageId != -1)
    curl_formadd(&multiPost, &end, CURLFORM_COPYNAME, "reply_to_message_id",
                 CURLFORM_COPYCONTENTS,
                 std::to_string(replyToMessageId).c_str(), CURLFORM_END);

  if (replyMarkup != "")
    curl_formadd(&multiPost, &end, CURLFORM_COPYNAME, "reply_markup",
                 CURLFORM_COPYCONTENTS, replyMarkup.c_str(), CURLFORM_END);

  curl_easy_setopt(c, CURLOPT_HTTPPOST, multiPost);
  curl_easy_setopt(c, CURLOPT_WRITEDATA, &body);
  curl_easy_setopt(c, CURLOPT_URL, operation.c_str());

  CURLcode code;
  if ((code = curl_easy_perform(c)) != CURLE_OK)
    throw std::runtime_error(curl_easy_strerror(code));

  return body;
}

std::string tgbot::utils::http::multiPartUpload(
    CURL *c, const std::string &operation, const std::string &chatId,
    const std::string &mimeType, const std::string &type,
    const std::string &filename, const std::string &caption,
    const int &duration, const bool &disableNotification,
    const int &replyToMessageId, const std::string &replyMarkup) {
  if (!c)
    throw std::runtime_error("CURL is actually a null pointer");

  curl_httppost *multiPost = nullptr;
  curl_httppost *end = nullptr;
  std::string body;

  curl_formadd(&multiPost, &end, CURLFORM_COPYNAME, "chat_id",
               CURLFORM_COPYCONTENTS, chatId.c_str(), CURLFORM_END);

  curl_formadd(&multiPost, &end, CURLFORM_COPYNAME, type.c_str(),
               CURLFORM_CONTENTTYPE, mimeType.c_str(), CURLFORM_FILE,
               filename.c_str(), CURLFORM_END);

  if (duration != -1)
    curl_formadd(&multiPost, &end, CURLFORM_COPYNAME, "duration",
                 CURLFORM_COPYCONTENTS, std::to_string(duration).c_str(),
                 CURLFORM_END);

  if (caption != "")
    curl_formadd(&multiPost, &end, CURLFORM_COPYNAME, "caption",
                 CURLFORM_COPYCONTENTS, caption.c_str(), CURLFORM_END);

  if (disableNotification)
    curl_formadd(&multiPost, &end, CURLFORM_COPYNAME, "disable_notification",
                 CURLFORM_COPYCONTENTS, "true", CURLFORM_END);

  if (replyToMessageId != -1)
    curl_formadd(&multiPost, &end, CURLFORM_COPYNAME, "reply_to_message_id",
                 CURLFORM_COPYCONTENTS,
                 std::to_string(replyToMessageId).c_str(), CURLFORM_END);

  if (replyMarkup != "")
    curl_formadd(&multiPost, &end, CURLFORM_COPYNAME, "reply_markup",
                 CURLFORM_COPYCONTENTS, replyMarkup.c_str(), CURLFORM_END);

  curl_easy_setopt(c, CURLOPT_HTTPPOST, multiPost);
  curl_easy_setopt(c, CURLOPT_WRITEDATA, &body);
  curl_easy_setopt(c, CURLOPT_URL, operation.c_str());

  CURLcode code;
  if ((code = curl_easy_perform(c)) != CURLE_OK)
    throw std::runtime_error(curl_easy_strerror(code));

  return body;
}

std::string tgbot::utils::http::multiPartUpload(
    CURL *c, const std::string &operation, const std::string &chatId,
    const std::string &mimeType, const std::string &type,
    const std::string &filename, const std::string &caption,
    const bool &disableNotification, const int &replyToMessageId,
    const std::string &replyMarkup) {
  if (!c)
    throw std::runtime_error("CURL is actually a null pointer");

  curl_httppost *multiPost = nullptr;
  curl_httppost *end = nullptr;
  std::string body;

  curl_formadd(&multiPost, &end, CURLFORM_COPYNAME, "chat_id",
               CURLFORM_COPYCONTENTS, chatId.c_str(), CURLFORM_END);

  curl_formadd(&multiPost, &end, CURLFORM_COPYNAME, type.c_str(),
               CURLFORM_CONTENTTYPE, mimeType.c_str(), CURLFORM_FILE,
               filename.c_str(), CURLFORM_END);

  if (caption != "")
    curl_formadd(&multiPost, &end, CURLFORM_COPYNAME, "caption",
                 CURLFORM_COPYCONTENTS, caption.c_str(), CURLFORM_END);

  if (disableNotification)
    curl_formadd(&multiPost, &end, CURLFORM_COPYNAME, "disable_notification",
                 CURLFORM_COPYCONTENTS, "true", CURLFORM_END);

  if (replyToMessageId != -1)
    curl_formadd(&multiPost, &end, CURLFORM_COPYNAME, "reply_to_message_id",
                 CURLFORM_COPYCONTENTS,
                 std::to_string(replyToMessageId).c_str(), CURLFORM_END);

  if (replyMarkup != "")
    curl_formadd(&multiPost, &end, CURLFORM_COPYNAME, "reply_markup",
                 CURLFORM_COPYCONTENTS, replyMarkup.c_str(), CURLFORM_END);

  curl_easy_setopt(c, CURLOPT_HTTPPOST, multiPost);
  curl_easy_setopt(c, CURLOPT_WRITEDATA, &body);
  curl_easy_setopt(c, CURLOPT_URL, operation.c_str());

  CURLcode code;
  if ((code = curl_easy_perform(c)) != CURLE_OK)
    throw std::runtime_error(curl_easy_strerror(code));

  return body;
}
