#include <json/json.h>
#include <tgbot/bot.h>
#include <tgbot/methods/api.h>
#include <tgbot/utils/encode.h>
#include <tgbot/utils/https.h>

#define BOOL_TOSTR(xvalue) ((xvalue) ? "true" : "false")

#define SEPARATE(k, sstr)                                                      \
  if (k)                                                                       \
  sstr << ','

using namespace tgbot::methods;
using namespace tgbot::utils;

template <typename _Ty> using Ptr = ::tgbot::types::Ptr<_Ty>;

static inline std::string
toString(const types::ShippingOption &shippingOption) {
  std::stringstream jsonify;
  jsonify << "{ \"id\": \"" << shippingOption.id << "\", \"title\": \""
          << shippingOption.title << "\""
          << ", \"prices\": [";

  const size_t &nPrices = shippingOption.prices.size();
  for (size_t i = 0; i < nPrices; i++) {
    SEPARATE(i, jsonify);

    const types::LabeledPrice &price = shippingOption.prices.at(i);
    jsonify << "{ \"amount\":" << price.amount << ", \"label\":\""
            << price.label << "\" }";
  }

  jsonify << "]}";

  return jsonify.str();
}

static inline void
allowedUpdatesToString(const std::vector<api_types::UpdateType> &updates,
                       std::stringstream &stream) {
  stream << "[";
  for (auto const &update : updates) {
    switch (update) {
    case api_types::UpdateType::MESSAGE:
      stream << "\"message\",";
      break;
    case api_types::UpdateType::CALLBACK_QUERY:
      stream << "\"callback_query\",";
      break;
    case api_types::UpdateType::INLINE_QUERY:
      stream << "\"inline_query\",";
      break;
    case api_types::UpdateType::CHOSEN_INLINE_RESULT:
      stream << "\"chosen_inline_result\",";
      break;
    case api_types::UpdateType::PRE_CHECKOUT_QUERY:
      stream << "\"pre_checkout_query\",";
      break;
    case api_types::UpdateType::SHIPPING_QUERY:
      stream << "\"shipping_query\",";
      break;
    case api_types::UpdateType::EDITED_CHANNEL_POST:
      stream << "\"edited_channel_post\",";
      break;
    case api_types::UpdateType::EDITED_MESSAGE:
      stream << "\"edited_message\",";
      break;
    case api_types::UpdateType::CHANNEL_POST:
      stream << "\"channel_post\",";
      break;
    }
  }
}

static inline void removeComma(const std::stringstream &stream,
                               std::string &target) {
  std::string &&req = stream.str();
  char &endpos = req.at(req.size() - 1);
  if (endpos == ',')
    endpos = ']';
  target = req;
}

static inline std::string
toString(const api_types::MaskPosition &maskPosition) {
  std::stringstream jsonify;
  jsonify << "{ \"point\": \"" << maskPosition.point
          << "\",\"x_shift\": " << maskPosition.xShift
          << ",\"y_shift\": " << maskPosition.yShift
          << ",\"scale\": " << maskPosition.scale;

  return jsonify.str();
}

static void invoiceParams(std::stringstream &stream,
                          const types::Invoice &params) {
  stream << "&title=";
  encode(stream, params.title);

  stream << "&description=";
  encode(stream, params.description);

  stream << "&currency=" << params.currency;

  stream << "&provider_token=";
  encode(stream, params.providerToken);

  stream << "&start_parameter=";
  encode(stream, params.startParameter);

  stream << "&payload=";
  encode(stream, params.payload);

  if (params.isFlexible)
    stream << "&is_flexible=true";

  if (params.needEmail)
    stream << "&need_email=true";

  if (params.needName)
    stream << "&need_name=true";

  if (params.needPhoneNumber)
    stream << "&need_phone_number=true";

  if (params.needShippingAddress)
    stream << "&need_shipping_address=true";

  if (params.photoHeight)
    stream << "&photo_height=" << params.photoHeight;

  if (params.photoSize)
    stream << "&photo_size=" << params.photoSize;

  if (params.photoWidth)
    stream << "&photo_width=" << params.photoWidth;

  if (params.photoUrl)
    stream << "&photo_url=" << *params.photoUrl;

  stream << "&prices=%5B";

  std::stringstream pricesStream;
  
  for (std::size_t i = 0; i < params.prices.size(); ++i) { 
    SEPARATE(i, pricesStream);
    pricesStream << "{\"label\":" << params.prices.at(i).label
                 << ",\"amount\":" << params.prices.at(i).amount << "}";
  }

  encode(stream, pricesStream.str());
  stream << "%5D";
}

// Api constructors

// Webhook, no further action
tgbot::methods::Api::Api(const std::string &token)
    : baseApi("https://api.telegram.org/bot" + token) {}

// Webhook
tgbot::methods::Api::Api(
    const std::string &token, const std::string &url, const int &maxConnections,
    const std::vector<api_types::UpdateType> &allowedUpdates)
    : baseApi("https://api.telegram.org/bot" + token) {

  if (!setWebhook(url, maxConnections, allowedUpdates))
    throw TelegramException("Unable to set webhook");
}

// Webhook with cert
tgbot::methods::Api::Api(
    const std::string &token, const std::string &url,
    const std::string &certificate, const int &maxConnections,
    const std::vector<api_types::UpdateType> &allowedUpdates)
    : baseApi("https://api.telegram.org/bot" + token) {

  if (!setWebhook(url, certificate, maxConnections, allowedUpdates))
    throw TelegramException("Unable to set webhook");
}

// HTTP Long polling
tgbot::methods::Api::Api(
    const std::string &token,
    const std::vector<api_types::UpdateType> &allowedUpdates,
    const int &timeout, const int &limit)
    : baseApi("https://api.telegram.org/bot" + token), currentOffset(0) {

  std::stringstream fullApiRequest;
  fullApiRequest << baseApi << "/getUpdates?limit=" << limit
                 << "&timeout=" << timeout;

  if (allowedUpdates.size()) {
    fullApiRequest << "&allowed_updates=";
    allowedUpdatesToString(allowedUpdates, fullApiRequest);
    removeComma(fullApiRequest, updateApiRequest);
  } else
    updateApiRequest = fullApiRequest.str();
}

//
// API implementations
//

// getUpdates (internal usage)
int tgbot::methods::Api::getUpdates(void *c,
                                    std::vector<api_types::Update> &updates) {
  std::stringstream updatesRequest;
  updatesRequest << updateApiRequest << "&offset=" << currentOffset;

  Json::Value rootUpdate;
  Json::Reader parser;

  const std::string& responseBody { utils::http::get(c, updatesRequest.str()) };

  if(!responseBody.size())
  	  return 0;

  parser.parse(responseBody, rootUpdate);

  if (!rootUpdate.get("ok", "").asBool()) {
  	const std::string description(rootUpdate.get("description","").asCString());
  	logger.error(description);
    throw TelegramException(description);
  }

  Json::Value valueUpdates = rootUpdate.get("result", "");
  const int &updatesCount = valueUpdates.size();
  if (!updatesCount)
    return 0;

  for (auto const &singleUpdate : valueUpdates)
    updates.emplace_back(singleUpdate);

  currentOffset =
      1 + valueUpdates[updatesCount - 1].get("update_id", "").asInt();
  
  return updatesCount;
}

//
// Availible API Methods
//

// setWebhook
bool tgbot::methods::Api::setWebhook(
    const std::string &url, const int &maxConnections,
    const std::vector<api_types::UpdateType> &allowedUpdates) {
  std::stringstream request;
  request << baseApi << "/setWebhook?url=" << url
          << "&max_connections=" << maxConnections;

  std::string setWebhookRequest;
  if (allowedUpdates.size()) {
    request << "&allowed_updates=";
    allowedUpdatesToString(allowedUpdates, request);
    removeComma(request, setWebhookRequest);
  } else
    setWebhookRequest = request.str();

  CURL *inst = http::curlEasyInit();
  Json::Value value;
  Json::Reader reader;

  reader.parse(http::get(inst, setWebhookRequest), value);
  curl_easy_cleanup(inst);

  if (!value.get("ok", "").asBool())
    throw TelegramException(value.get("description", "").asCString());

  urlWebhook = url;
  return true;
}

bool tgbot::methods::Api::setWebhook(
    const std::string &url, const std::string &certificate,
    const int &maxConnections,
    const std::vector<api_types::UpdateType> &allowedUpdates) {
  CURL *inst = http::curlEasyInit();
  Json::Value value;
  Json::Reader reader;

  if (!allowedUpdates.size())
    reader.parse(http::multiPartUpload(inst, baseApi + "/setWebhook",
                                       certificate, url, maxConnections),
                 value);
  else {
    std::stringstream request;
    std::string final;

    allowedUpdatesToString(allowedUpdates, request);
    removeComma(request, final);

    reader.parse(http::multiPartUpload(inst, baseApi + "/setWebhook",
                                       certificate, url, maxConnections, final),
                 value);
  }

  curl_easy_cleanup(inst);

  if (!value.get("ok", "").asBool())
    throw TelegramException(value.get("description", "").asCString());

  urlWebhook = url;
  return true;
}

// deleteWebhook
bool tgbot::methods::Api::deleteWebhook() const {
  CURL *inst = http::curlEasyInit();
  bool isOk =
      (http::get(inst, baseApi + "/deleteWebhook").find("\"ok\":true") !=
       std::string::npos);
  curl_easy_cleanup(inst);

  if (!isOk)
    throw TelegramException("Cannot delete webhook");

  return true;
}

// getWebhookInfo
api_types::WebhookInfo tgbot::methods::Api::getWebhookInfo() const {
  CURL *inst = http::curlEasyInit();
  Json::Value value;
  Json::Reader reader;

  reader.parse(http::get(inst, baseApi + "/getWebhookInfo"), value);
  curl_easy_cleanup(inst);

  if (!value.get("ok", "").asBool())
    throw TelegramException(value.get("description", "").asCString());

  return api_types::WebhookInfo(value.get("result", ""));
}

// getMe
api_types::User tgbot::methods::Api::getMe() const {
  CURL *inst = http::curlEasyInit();
  Json::Value value;
  Json::Reader reader;

  reader.parse(http::get(inst, baseApi + "/getMe"), value);
  curl_easy_cleanup(inst);

  if (!value.get("ok", "").asBool())
    throw TelegramException(value.get("description", "").asCString());

  return api_types::User(value.get("result", ""));
}

// getChat
api_types::Chat tgbot::methods::Api::getChat(const std::string &chatId) const {
  CURL *inst = http::curlEasyInit();
  Json::Value value;
  Json::Reader reader;

  reader.parse(http::get(inst, baseApi + "/getChat?chat_id=" + chatId), value);
  curl_easy_cleanup(inst);

  if (!value.get("ok", "").asBool())
    throw TelegramException(value.get("description", "").asCString());

  return api_types::Chat(value.get("result", ""));
}

// getChatMembersCount
unsigned
tgbot::methods::Api::getChatMembersCount(const std::string &chatId) const {
  CURL *inst = http::curlEasyInit();
  Json::Value value;
  Json::Reader reader;

  reader.parse(
      http::get(inst, baseApi + "/getChatMembersCount?chat_id=" + chatId),
      value);
  curl_easy_cleanup(inst);

  if (!value.get("ok", "").asBool())
    throw TelegramException(value.get("description", "").asCString());

  return value.get("result", "").asUInt();
}

// getFile
api_types::File tgbot::methods::Api::getFile(const std::string &fileId) const {
  CURL *inst = http::curlEasyInit();
  Json::Value value;
  Json::Reader reader;

  reader.parse(http::get(inst, baseApi + "/getFile?file_id=" + fileId), value);
  curl_easy_cleanup(inst);

  if (!value.get("ok", "").asBool())
    throw TelegramException(value.get("description", "").asCString());

  return api_types::File(value.get("result", ""));
}

// getChatMember
api_types::ChatMember
tgbot::methods::Api::getChatMember(const std::string &chatId,
                                   const int &userId) const {
  CURL *inst = http::curlEasyInit();
  Json::Value value;
  Json::Reader reader;

  std::stringstream url;
  url << baseApi << "/getChatMember?chat_id=" << chatId
      << "&user_id=" << userId;

  reader.parse(http::get(inst, url.str()), value);
  curl_easy_cleanup(inst);

  if (!value.get("ok", "").asBool())
    throw TelegramException(value.get("description", "").asCString());

  return api_types::ChatMember(value.get("result", ""));
}

// getStickerSet
api_types::StickerSet
tgbot::methods::Api::getStickerSet(const std::string &name) const {
  CURL *inst = http::curlEasyInit();
  Json::Value value;
  Json::Reader reader;

  reader.parse(http::get(inst, baseApi + "/getStickerSet?name=" + encode(name)),
               value);
  curl_easy_cleanup(inst);

  if (!value.get("ok", "").asBool())
    throw TelegramException(value.get("description", "").asCString());

  return api_types::StickerSet(value.get("result", ""));
}

// getUserProfilePhotos
api_types::UserProfilePhotos
tgbot::methods::Api::getUserProfilePhotos(const int &userId,
                                          const unsigned int &offset,
                                          const unsigned int &limit) const {
  CURL *inst = http::curlEasyInit();
  Json::Value value;
  Json::Reader reader;

  std::stringstream url;
  url << baseApi << "/getUserProfilePhotos?user_id=" << userId
      << "&offset=" << offset << "&limit=" << limit;

  reader.parse(http::get(inst, url.str()), value);
  curl_easy_cleanup(inst);

  if (!value.get("ok", "").asBool())
    throw TelegramException(value.get("description", "").asCString());

  return api_types::UserProfilePhotos(value.get("result", ""));
}

// getChatAdministrators
std::vector<api_types::ChatMember>
tgbot::methods::Api::getChatAdministrators(const std::string &chatId) const {
  CURL *inst = http::curlEasyInit();
  Json::Value value;
  Json::Reader reader;

  reader.parse(
      http::get(inst, baseApi + "/getChatAdministrators?chat_id=" + chatId),
      value);
  curl_easy_cleanup(inst);

  if (!value.get("ok", "").asBool())
    throw TelegramException(value.get("description", "").asCString());

  std::vector<api_types::ChatMember> members;
  for (auto const member : value.get("result", ""))
    members.emplace_back(member);

  return members;
}

// getGameHighScores
std::vector<api_types::GameHighScore>
tgbot::methods::Api::getGameHighScores(const int &userId, const int &chatId,
                                       const int &messageId) const {
  CURL *inst = http::curlEasyInit();
  Json::Value value;
  Json::Reader reader;

  std::stringstream url;
  url << baseApi << "/getGameHighScores?user_id=" << userId
      << "&chat_id=" << chatId << "&message_id=" << messageId;

  reader.parse(http::get(inst, url.str()), value);
  curl_easy_cleanup(inst);

  if (!value.get("ok", "").asBool())
    throw TelegramException(value.get("description", "").asCString());

  std::vector<api_types::GameHighScore> members;
  for (auto const member : value.get("result", ""))
    members.emplace_back(member);

  return members;
}

std::vector<api_types::GameHighScore> tgbot::methods::Api::getGameHighScores(
    const int &userId, const std::string &inlineMessageId) const {
  CURL *inst = http::curlEasyInit();
  Json::Value value;
  Json::Reader reader;

  std::stringstream url;
  url << baseApi << "/getGameHighScores?user_id=" << userId
      << "&inline_message_id=" << inlineMessageId;

  reader.parse(http::get(inst, url.str()), value);
  curl_easy_cleanup(inst);

  if (!value.get("ok", "").asBool())
    throw TelegramException(value.get("description", "").asCString());

  std::vector<api_types::GameHighScore> members;
  for (auto const member : value.get("result", ""))
    members.emplace_back(member);

  return members;
}

// deleteChatPhoto
bool tgbot::methods::Api::deleteChatPhoto(const std::string &chatId) const {
  CURL *inst = http::curlEasyInit();
  Json::Value value;
  Json::Reader reader;

  reader.parse(http::get(inst, baseApi + "/deleteChatPhoto?chat_id=" + chatId),
               value);
  curl_easy_cleanup(inst);

  if (!value.get("ok", "").asBool())
    throw TelegramException(value.get("description", "").asCString());

  return true;
}

// deleteMessage
bool tgbot::methods::Api::deleteMessage(const std::string &chatId,
                                        const std::string &messageId) const {
  CURL *inst = http::curlEasyInit();
  Json::Value value;
  Json::Reader reader;

  std::stringstream url;
  url << baseApi << "/deleteMessage?chat_id=" << chatId
      << "&message_id=" << messageId;

  reader.parse(http::get(inst, url.str()), value);
  curl_easy_cleanup(inst);

  if (!value.get("ok", "").asBool())
    throw TelegramException(value.get("description", "").asCString());

  return true;
}

// deleteStickerFromSet
bool tgbot::methods::Api::deleteStickerFromSet(
    const std::string &sticker) const {
  CURL *inst = http::curlEasyInit();
  Json::Value value;
  Json::Reader reader;

  reader.parse(
      http::get(inst, baseApi + "/deleteStickerFromSet?sticker=" + sticker),
      value);
  curl_easy_cleanup(inst);

  if (!value.get("ok", "").asBool())
    throw TelegramException(value.get("description", "").asCString());

  return true;
}

// exportChatInviteLink
std::string
tgbot::methods::Api::exportChatInviteLink(const std::string &chatId) const {
  CURL *inst = http::curlEasyInit();
  Json::Value value;
  Json::Reader reader;

  reader.parse(
      http::get(inst, baseApi + "/exportChatInviteLink?chat_id=" + chatId),
      value);
  curl_easy_cleanup(inst);

  if (!value.get("ok", "").asBool())
    throw TelegramException(value.get("description", "").asCString());

  return value.get("result", "").asCString();
}

// kickChatMember
bool tgbot::methods::Api::kickChatMember(const std::string &chatId,
                                         const int &userId,
                                         const int &untilDate) const {
  CURL *inst = http::curlEasyInit();
  Json::Value value;
  Json::Reader reader;

  std::stringstream url;
  url << baseApi << "/kickChatMember?chat_id=" << chatId
      << "&user_id=" << userId;

  if (untilDate != -1)
    url << "&until_date=" << untilDate;

  reader.parse(http::get(inst, url.str()), value);
  curl_easy_cleanup(inst);

  if (!value.get("ok", "").asBool())
    throw TelegramException(value.get("description", "").asCString());

  return true;
}

// leaveChat
bool tgbot::methods::Api::leaveChat(const std::string &chatId) const {
  CURL *inst = http::curlEasyInit();
  Json::Value value;
  Json::Reader reader;

  reader.parse(http::get(inst, baseApi + "/leaveChat?chat_id=" + chatId),
               value);
  curl_easy_cleanup(inst);

  if (!value.get("ok", "").asBool())
    throw TelegramException(value.get("description", "").asCString());

  return true;
}

// pinChatMessage
bool tgbot::methods::Api::pinChatMessage(
    const std::string &chatId, const std::string &messageId,
    const bool &disableNotification) const {
  CURL *inst = http::curlEasyInit();
  Json::Value value;
  Json::Reader reader;

  std::stringstream url;
  url << baseApi << "/pinChatMessage?chat_id=" << chatId
      << "&message_id=" << messageId;

  if (disableNotification)
    url << "&disable_notification=true";

  reader.parse(http::get(inst, url.str()), value);
  curl_easy_cleanup(inst);

  if (!value.get("ok", "").asBool())
    throw TelegramException(value.get("description", "").asCString());

  return true;
}

// promoteChatMember
bool tgbot::methods::Api::promoteChatMember(
    const std::string &chatId, const int &userId,
    const types::ChatMemberPromote &permissions) const {
  CURL *inst = http::curlEasyInit();
  Json::Value value;
  Json::Reader reader;

  std::stringstream url;
  url << baseApi << "/promoteChatMember?chat_id=" << chatId
      << "&user_id=" << userId
      << "&can_post_messages=" << BOOL_TOSTR(permissions.canPostMessages)
      << "&can_change_info=" << BOOL_TOSTR(permissions.canChangeInfo)
      << "&can_edit_messages=" << BOOL_TOSTR(permissions.canEditMessages)
      << "&can_delete_messages=" << BOOL_TOSTR(permissions.canDeleteMessages)
      << "&can_invite_users=" << BOOL_TOSTR(permissions.canInviteUsers)
      << "&can_restrict_members=" << BOOL_TOSTR(permissions.canRestrictMembers)
      << "&can_pin_messages=" << BOOL_TOSTR(permissions.canPinMessages)
      << "&can_promote_members=" << BOOL_TOSTR(permissions.canPromoteMembers);

  reader.parse(http::get(inst, url.str()), value);
  curl_easy_cleanup(inst);

  if (!value.get("ok", "").asBool())
    throw TelegramException(value.get("description", "").asCString());

  return true;
}

// restrictChatMember
bool tgbot::methods::Api::restrictChatMember(
    const std::string &chatId, const int &userId,
    const types::ChatMemberRestrict &permissions, const int &untilDate) const {
  CURL *inst = http::curlEasyInit();
  Json::Value value;
  Json::Reader reader;

  std::stringstream url;
  url << baseApi << "/restrictChatMember?chat_id=" << chatId
      << "&user_id=" << userId
      << "&can_send_messages=" << BOOL_TOSTR(permissions.canSendMessages)
      << "&can_send_media_messages="
      << BOOL_TOSTR(permissions.canSendMediaMessages)
      << "&can_send_other_messages="
      << BOOL_TOSTR(permissions.canSendOtherMessages)
      << "&can_add_web_page_previews="
      << BOOL_TOSTR(permissions.canAddWebPagePreviews);

  if (untilDate != -1)
    url << "&until_date=" << untilDate;

  reader.parse(http::get(inst, url.str()), value);
  curl_easy_cleanup(inst);

  if (!value.get("ok", "").asBool())
    throw TelegramException(value.get("description", "").asCString());

  return true;
}

// unbanChatMember
bool tgbot::methods::Api::unbanChatMember(const std::string &chatId,
                                          const int &userId) const {
  CURL *inst = http::curlEasyInit();
  Json::Value value;
  Json::Reader reader;

  std::stringstream url;
  url << baseApi << "/unbanChatMember?chat_id=" << chatId
      << "&user_id=" << userId;

  reader.parse(http::get(inst, url.str()), value);
  curl_easy_cleanup(inst);

  if (!value.get("ok", "").asBool())
    throw TelegramException(value.get("description", "").asCString());

  return true;
}

// unpinChatMessage
bool tgbot::methods::Api::unpinChatMessage(const std::string &chatId) const {
  CURL *inst = http::curlEasyInit();
  Json::Value value;
  Json::Reader reader;

  std::stringstream url;
  url << baseApi << "/unpinChatMessage?chat_id=" << chatId;

  reader.parse(http::get(inst, url.str()), value);
  curl_easy_cleanup(inst);

  if (!value.get("ok", "").asBool())
    throw TelegramException(value.get("description", "").asCString());

  return true;
}

// setChatDescription
bool tgbot::methods::Api::setChatDescription(
    const std::string &chatId, const std::string &description) const {
  CURL *inst = http::curlEasyInit();
  Json::Value value;
  Json::Reader reader;

  std::stringstream url;
  url << baseApi << "/setChatDescription?chat_id=" << chatId << "&description=";
  encode(url, description);

  reader.parse(http::get(inst, url.str()), value);
  curl_easy_cleanup(inst);

  if (!value.get("ok", "").asBool())
    throw TelegramException(value.get("description", "").asCString());

  return true;
}

// setChatTitle
bool tgbot::methods::Api::setChatTitle(const std::string &chatId,
                                       const std::string &title) const {
  CURL *inst = http::curlEasyInit();
  Json::Value value;
  Json::Reader reader;

  std::stringstream url;
  url << baseApi << "/setChatTitle?chat_id=" << chatId << "&title=";
  encode(url, title);

  reader.parse(http::get(inst, url.str()), value);
  curl_easy_cleanup(inst);

  if (!value.get("ok", "").asBool())
    throw TelegramException(value.get("description", "").asCString());

  return true;
}

// setChatPhoto
bool tgbot::methods::Api::setChatPhoto(const std::string &chatId,
                                       const std::string &filename,
                                       const std::string &mimeType) const {
  CURL *inst = http::curlEasyInit();
  Json::Value value;
  Json::Reader reader;

  reader.parse(http::multiPartUpload(inst, baseApi + "/setChatPhoto", chatId,
                                     mimeType, "photo", filename),
               value);
  curl_easy_cleanup(inst);

  if (!value.get("ok", "").asBool())
    throw TelegramException(value.get("description", "").asCString());

  return true;
}

// setGameScore
api_types::Message
tgbot::methods::Api::setGameScore(const std::string &userId, const int &score,
                                  const int &chatId, const int &messageId,
                                  const bool &force,
                                  const bool &disableEditMessage) const {
  CURL *inst = http::curlEasyInit();
  Json::Value value;
  Json::Reader reader;

  std::stringstream url;
  url << baseApi << "/setGameScore?user_id=" << userId << "&score=" << score
      << "&chat_id=" << chatId << "&message_id=" << messageId;

  if (force)
    url << "&force=true";

  if (disableEditMessage)
    url << "&disable_edit_message=true";

  reader.parse(http::get(inst, url.str()), value);
  curl_easy_cleanup(inst);

  if (!value.get("ok", "").asBool())
    throw TelegramException(value.get("description", "").asCString());

  return api_types::Message(value.get("result", ""));
}

api_types::Message
tgbot::methods::Api::setGameScore(const std::string &userId, const int &score,
                                  const std::string &inlineMessageId,
                                  const bool &force,
                                  const bool &disableEditMessage) const {
  CURL *inst = http::curlEasyInit();
  Json::Value value;
  Json::Reader reader;

  std::stringstream url;
  url << baseApi << "/setGameScore?user_id=" << userId << "&score=" << score
      << "&inline_message_id=" << inlineMessageId;

  if (force)
    url << "&force=true";

  if (disableEditMessage)
    url << "&disable_edit_message=true";

  reader.parse(http::get(inst, url.str()), value);
  curl_easy_cleanup(inst);

  if (!value.get("ok", "").asBool())
    throw TelegramException(value.get("description", "").asCString());

  return api_types::Message(value.get("result", ""));
}

// setStickerPositionInSet
bool tgbot::methods::Api::setStickerPositionInSet(const std::string &sticker,
                                                  const int position) const {
  CURL *inst = http::curlEasyInit();
  Json::Value value;
  Json::Reader reader;

  std::stringstream url;
  url << baseApi << "/setStickerPositionInSet?sticker=" << sticker
      << "&position=" << position;

  reader.parse(http::get(inst, url.str()), value);
  curl_easy_cleanup(inst);

  if (!value.get("ok", "").asBool())
    throw TelegramException(value.get("description", "").asCString());

  return true;
}

// uploadStickerFile
api_types::File
tgbot::methods::Api::uploadStickerFile(const int &userId,
                                       const std::string &pngSticker,
                                       const types::FileSource &source) const {
  CURL *inst = http::curlEasyInit();
  Json::Value value;
  Json::Reader reader;

  if (source == types::FileSource::EXTERNAL) {
    std::stringstream url;
    url << baseApi << "/uploadStickerFile?user_id=" << userId
        << "&png_sticker=" << pngSticker;

    reader.parse(http::get(inst, url.str()), value);
  } else
    reader.parse(http::multiPartUpload(inst, baseApi + "/uploadStickerFile",
                                       userId, pngSticker),
                 value);
  curl_easy_cleanup(inst);

  if (!value.get("ok", "").asBool())
    throw TelegramException(value.get("description", "").asCString());

  return api_types::File(value.get("result", ""));
}

// addStickerToSet
bool tgbot::methods::Api::addStickerToSet(
    const int &userId, const std::string &name, const std::string &emoji,
    const std::string &pngSticker, const types::FileSource &source) const {
  CURL *inst = http::curlEasyInit();
  Json::Value value;
  Json::Reader reader;

  if (source == types::FileSource::EXTERNAL) {
    std::stringstream url;
    url << baseApi << "/addStickerToSet?user_id=" << userId
        << "&png_sticker=" << pngSticker << "&name=";
    encode(url, name);
    url << "&emoji=" << emoji;

    reader.parse(http::get(inst, url.str()), value);
  } else
    reader.parse(http::multiPartUpload(inst, baseApi + "/addStickerToSet",
                                       userId, name, emoji, pngSticker, ""),
                 value);
  curl_easy_cleanup(inst);

  if (!value.get("ok", "").asBool())
    throw TelegramException(value.get("description", "").asCString());

  return true;
}

bool tgbot::methods::Api::addStickerToSet(
    const int &userId, const std::string &name, const std::string &emoji,
    const std::string &pngSticker, const api_types::MaskPosition &maskPosition,
    const types::FileSource &source) const {
  CURL *inst = http::curlEasyInit();
  Json::Value value;
  Json::Reader reader;

  const std::string &&serMaskPosition = toString(maskPosition);

  if (source == types::FileSource::EXTERNAL) {
    std::stringstream url;
    url << baseApi << "/addStickerToSet?user_id=" << userId
        << "&png_sticker=" << pngSticker << "&name=";
    encode(url, name);
    url << "&emoji=" << emoji << "&mask_position=" << serMaskPosition;

    reader.parse(http::get(inst, url.str()), value);
  } else
    reader.parse(http::multiPartUpload(inst, baseApi + "/addStickerToSet",
                                       userId, name, emoji, serMaskPosition,
                                       pngSticker, ""),
                 value);
  curl_easy_cleanup(inst);

  if (!value.get("ok", "").asBool())
    throw TelegramException(value.get("description", "").asCString());

  return true;
}

// createNewStickerSet
bool tgbot::methods::Api::createNewStickerSet(
    const int &userId, const std::string &name, const std::string &title,
    const std::string &emoji, const std::string &pngSticker,
    const types::FileSource &source) const {
  CURL *inst = http::curlEasyInit();
  Json::Value value;
  Json::Reader reader;

  if (source == types::FileSource::EXTERNAL) {
    std::stringstream url;
    url << baseApi << "/createNewStickerSet?user_id=" << userId
        << "&png_sticker=" << pngSticker << "&name=";
    encode(url, name);
    url << "&emoji=" << emoji << "&title=" << title;

    reader.parse(http::get(inst, url.str()), value);
  } else
    reader.parse(http::multiPartUpload(inst, baseApi + "/addStickerToSet",
                                       userId, name, emoji, pngSticker, title),
                 value);

  curl_easy_cleanup(inst);

  if (!value.get("ok", "").asBool())
    throw TelegramException(value.get("description", "").asCString());

  return true;
}

bool tgbot::methods::Api::createNewStickerSet(
    const int &userId, const std::string &name, const std::string &title,
    const std::string &emoji, const std::string &pngSticker,
    const api_types::MaskPosition &maskPosition,
    const types::FileSource &source) const {
  CURL *inst = http::curlEasyInit();
  Json::Value value;
  Json::Reader reader;

  const std::string &&serMaskPosition = toString(maskPosition);

  if (source == types::FileSource::EXTERNAL) {
    std::stringstream url;
    url << baseApi << "/createNewStickerSet?user_id=" << userId
        << "&png_sticker=" << pngSticker << "&name=";
    encode(url, name);
    url << "&emoji=" << emoji << "&title=" << title
        << "&mask_position=" << serMaskPosition;

    reader.parse(http::get(inst, url.str()), value);
  } else
    reader.parse(http::multiPartUpload(inst, baseApi + "/addStickerToSet",
                                       userId, name, emoji, serMaskPosition,
                                       pngSticker, title),
                 value);

  curl_easy_cleanup(inst);

  if (!value.get("ok", "").asBool())
    throw TelegramException(value.get("description", "").asCString());

  return true;
}

// answerPreCheckoutQuery
bool tgbot::methods::Api::answerPreCheckoutQuery(
    const std::string &preCheckoutQueryId) const {
  CURL *inst = http::curlEasyInit();
  Json::Value value;
  Json::Reader reader;

  std::stringstream url;
  url << baseApi
      << "/answerPreCheckoutQuery?pre_checkout_query_id=" << preCheckoutQueryId
      << "&ok=true";

  reader.parse(http::get(inst, url.str()), value);
  curl_easy_cleanup(inst);

  if (!value.get("ok", "").asBool())
    throw TelegramException(value.get("description", "").asCString());

  return true;
}

bool tgbot::methods::Api::answerPreCheckoutQuery(
    const std::string &preCheckoutQueryId,
    const std::string &errorMessage) const {
  CURL *inst = http::curlEasyInit();
  Json::Value value;
  Json::Reader reader;

  std::stringstream url;
  url << baseApi
      << "/answerPreCheckoutQuery?pre_checkout_query_id=" << preCheckoutQueryId
      << "&ok=false"
      << "&error_message=" << errorMessage;

  reader.parse(http::get(inst, url.str()), value);
  curl_easy_cleanup(inst);

  if (!value.get("ok", "").asBool())
    throw TelegramException(value.get("description", "").asCString());

  return true;
}

// answerShippingQuery
bool tgbot::methods::Api::answerShippingQuery(
    const std::string &shippingQueryId, const std::string &errorMessage) const {
  CURL *inst = http::curlEasyInit();
  Json::Value value;
  Json::Reader reader;

  std::stringstream url;
  url << baseApi << "/answerShippingQuery?shipping_query_id=" << shippingQueryId
      << "&ok=false"
      << "&error_message=";
  encode(url, errorMessage);

  reader.parse(http::get(inst, url.str()), value);
  curl_easy_cleanup(inst);

  if (!value.get("ok", "").asBool())
    throw TelegramException(value.get("description", "").asCString());

  return true;
}

bool tgbot::methods::Api::answerShippingQuery(
    const std::string &shippingQueryId,
    const std::vector<types::ShippingOption> &shippingOptions) const {
  CURL *inst = http::curlEasyInit();
  Json::Value value;
  Json::Reader reader;

  std::stringstream url;
  url << baseApi << "/answerShippingQuery?shipping_query_id=" << shippingQueryId
      << "&ok=true&shipping_options=%5B";

  std::stringstream optionsStream;
  const size_t &nOptions = shippingOptions.size();
  for (size_t i = 0; i < nOptions; i++) {
    SEPARATE(i, optionsStream);
    optionsStream << toString(shippingOptions.at(i));
  }

  encode(url, optionsStream.str());
  url << "%5D";

  reader.parse(http::get(inst, url.str()), value);
  curl_easy_cleanup(inst);

  if (!value.get("ok", "").asBool())
    throw TelegramException(value.get("description", "").asCString());

  return true;
}

// answerCallbackQuery
bool tgbot::methods::Api::answerCallbackQuery(
    const std::string &callbackQueryId, const std::string &text,
    const bool &showAlert, const std::string &url, const int &cacheTime) const {
  CURL *inst = http::curlEasyInit();
  Json::Value value;
  Json::Reader reader;

  std::stringstream surl;
  surl << baseApi
       << "/answerCallbackQuery?callback_query_id=" << callbackQueryId;

  if (text != "") {
    surl << "&text=";
    encode(surl, text);
  }

  if (showAlert)
    surl << "&show_alert=true";

  if (url != "")
    surl << "&url=" << url;

  if (cacheTime)
    surl << "&cache_time=" << cacheTime;

  reader.parse(http::get(inst, surl.str()), value);
  curl_easy_cleanup(inst);

  if (!value.get("ok", "").asBool())
    throw TelegramException(value.get("description", "").asCString());

  return true;
}

// answerInlineQuery
bool tgbot::methods::Api::answerInlineQuery(
    const std::string &inlineQueryId,
    const std::vector<Ptr<types::InlineQueryResult>> &results,
    const int &cacheTime, const bool &isPersonal, const std::string &nextOffset,
    const std::string &switchPmText,
    const std::string &switchPmParameter) const {
  CURL *inst = http::curlEasyInit();
  Json::Value value;
  Json::Reader reader;

  std::stringstream url;
  url << baseApi << "/answerInlineQuery?inline_query_id=" << inlineQueryId
      << "&results=%5B";

  std::stringstream resultsStream;
  const size_t &nResults = results.size();
  for (size_t i = 0; i < nResults; i++) {
    SEPARATE(i, resultsStream);
    resultsStream << results.at(i)->toString();
  }

  encode(url, resultsStream.str());
  url << "%5D";

  if (cacheTime)
    url << "&cache_time=" << cacheTime;

  if (isPersonal)
    url << "&is_personal=true";

  if (nextOffset != "")
    url << "&next_offset=" << nextOffset;

  if (switchPmText != "") {
    url << "&switch_pm_text=";
    encode(url, switchPmText);
  }

  if (switchPmParameter != "") {
    url << "&switch_pm_parameter=";
    encode(url, switchPmParameter);
  }

  reader.parse(http::get(inst, url.str()), value);
  curl_easy_cleanup(inst);

  if (!value.get("ok", "").asBool())
    throw TelegramException(value.get("description", "").asCString());

  return true;
}

// sendMessage
api_types::Message tgbot::methods::Api::sendMessage(
    const std::string &chatId, const std::string &text,
    const types::ParseMode &parseMode, const bool &disableWebPagePreview,
    const bool &disableNotification,
    const types::ReplyMarkup &replyMarkup) const {
  CURL *inst = http::curlEasyInit();
  Json::Value value;
  Json::Reader reader;

  std::stringstream url;
  url << baseApi << "/sendMessage?chat_id=" << chatId << "&text=";
  encode(url, text);

  if (parseMode == types::ParseMode::HTML)
    url << "&parse_mode=HTML";
  else if (parseMode == types::ParseMode::MARKDOWN)
    url << "&parse_mode=Markdown";

  if (disableWebPagePreview)
    url << "&disable_web_page_preview=true";

  if (disableNotification)
    url << "&disable_notificatiton=true";

  const std::string &&markup = replyMarkup.toString();
  if (markup != "") {
    url << "&reply_markup=";
    encode(url, markup);
  }

  reader.parse(http::get(inst, url.str()), value);
  curl_easy_cleanup(inst);

  if (!value.get("ok", "").asBool())
    throw TelegramException(value.get("description", "").asCString());

  return api_types::Message(value.get("result", ""));
}

api_types::Message tgbot::methods::Api::sendMessage(
    const std::string &chatId, const std::string &text,
    const int replyToMessageId, const types::ParseMode &parseMode,
    const bool &disableWebPagePreview, const bool &disableNotification,
    const types::ReplyMarkup &replyMarkup) const {
  CURL *inst = http::curlEasyInit();
  Json::Value value;
  Json::Reader reader;

  std::stringstream url;
  url << baseApi << "/sendMessage?chat_id=" << chatId << "&text=";
  encode(url, text);
  url << "&reply_to_message_id=" << replyToMessageId;

  if (parseMode == types::ParseMode::HTML)
    url << "&parse_mode=HTML";
  else if (parseMode == types::ParseMode::MARKDOWN)
    url << "&parse_mode=Markdown";

  if (disableWebPagePreview)
    url << "&disable_web_page_preview=true";

  if (disableNotification)
    url << "&disable_notificatiton=true";

  const std::string &&markup = replyMarkup.toString();
  if (markup != "") {
    url << "&reply_markup=";
    encode(url, markup);
  }

  reader.parse(http::get(inst, url.str()), value);
  curl_easy_cleanup(inst);

  if (!value.get("ok", "").asBool())
    throw TelegramException(value.get("description", "").asCString());

  return api_types::Message(value.get("result", ""));
}

// forwardMessage
api_types::Message tgbot::methods::Api::forwardMessage(
    const std::string &chatId, const std::string &fromChatId,
    const int &messageId, const bool &disableNotification) const {
  CURL *inst = http::curlEasyInit();
  Json::Value value;
  Json::Reader reader;

  std::stringstream url;
  url << baseApi << "/forwardMessage?chat_id=" << chatId
      << "&from_chat_id=" << fromChatId << "&message_id=" << messageId;

  if (disableNotification)
    url << "&disable_notification=true";

  reader.parse(http::get(inst, url.str()), value);
  curl_easy_cleanup(inst);

  if (!value.get("ok", "").asBool())
    throw TelegramException(value.get("description", "").asCString());

  return api_types::Message(value.get("result", ""));
}

// editMessageText
api_types::Message tgbot::methods::Api::editMessageText(
    const std::string &chatId, const std::string &messageId,
    const std::string &text, const types::ParseMode &parseMode,
    const bool &disableWebPagePreview) const {
  CURL *inst = http::curlEasyInit();
  Json::Value value;
  Json::Reader reader;

  std::stringstream url;
  url << baseApi << "/editMessageText?chat_id=" << chatId
      << "&message_id=" << messageId << "&text=";
  encode(url, text);

  if (parseMode == types::ParseMode::HTML)
    url << "&parse_mode=HTML";
  else if (parseMode == types::ParseMode::MARKDOWN)
    url << "&parse_mode=Markdown";

  if (disableWebPagePreview)
    url << "&disable_web_page_preview=true";

  reader.parse(http::get(inst, url.str()), value);
  curl_easy_cleanup(inst);

  if (!value.get("ok", "").asBool())
    throw TelegramException(value.get("description", "").asCString());

  return api_types::Message(value.get("result", ""));
}

api_types::Message tgbot::methods::Api::editMessageText(
    const std::string &chatId, const std::string &messageId,
    const types::InlineKeyboardMarkup &replyMarkup, const std::string &text,
    const types::ParseMode &parseMode,
    const bool &disableWebPagePreview) const {
  CURL *inst = http::curlEasyInit();
  Json::Value value;
  Json::Reader reader;

  std::stringstream url;

  url << baseApi << "/editMessageText?chat_id=" << chatId
      << "&message_id=" << messageId << "&text=";
  encode(url, text);
  url << "&reply_markup=";
  encode(url, replyMarkup.toString());

  if (parseMode == types::ParseMode::HTML)
    url << "&parse_mode=HTML";
  else if (parseMode == types::ParseMode::MARKDOWN)
    url << "&parse_mode=Markdown";

  if (disableWebPagePreview)
    url << "&disable_web_page_preview=true";

  reader.parse(http::get(inst, url.str()), value);
  curl_easy_cleanup(inst);

  if (!value.get("ok", "").asBool())
    throw TelegramException(value.get("description", "").asCString());

  return api_types::Message(value.get("result", ""));
}

api_types::Message
tgbot::methods::Api::editMessageText(const std::string &inlineMessageId,
                                     const std::string &text,
                                     const types::ParseMode &parseMode,
                                     const bool &disableWebPagePreview) const {
  CURL *inst = http::curlEasyInit();
  Json::Value value;
  Json::Reader reader;

  std::stringstream url;
  url << baseApi << "/editMessageText?inline_message_id=" << inlineMessageId
      << "&text=";
  encode(url, text);

  if (parseMode == types::ParseMode::HTML)
    url << "&parse_mode=HTML";
  else if (parseMode == types::ParseMode::MARKDOWN)
    url << "&parse_mode=Markdown";

  if (disableWebPagePreview)
    url << "&disable_web_page_preview=true";

  reader.parse(http::get(inst, url.str()), value);
  curl_easy_cleanup(inst);

  if (!value.get("ok", "").asBool())
    throw TelegramException(value.get("description", "").asCString());

  return api_types::Message(value.get("result", ""));
}

api_types::Message tgbot::methods::Api::editMessageText(
    const std::string &inlineMessageId,
    const types::InlineKeyboardMarkup &replyMarkup, const std::string &text,
    const types::ParseMode &parseMode,
    const bool &disableWebPagePreview) const {
  CURL *inst = http::curlEasyInit();
  Json::Value value;
  Json::Reader reader;

  std::stringstream url;
  url << baseApi << "/editMessageText?inline_message_id=" << inlineMessageId
      << "&text=";
  encode(url, text);
  url << "&reply_markup=";
  encode(url, replyMarkup.toString());

  if (parseMode == types::ParseMode::HTML)
    url << "&parse_mode=HTML";
  else if (parseMode == types::ParseMode::MARKDOWN)
    url << "&parse_mode=Markdown";

  if (disableWebPagePreview)
    url << "&disable_web_page_preview=true";

  reader.parse(http::get(inst, url.str()), value);
  curl_easy_cleanup(inst);

  if (!value.get("ok", "").asBool())
    throw TelegramException(value.get("description", "").asCString());

  return api_types::Message(value.get("result", ""));
}

// editMessageCaption
api_types::Message
tgbot::methods::Api::editMessageCaption(const std::string &chatId,
                                        const std::string &messageId,
                                        const std::string &caption) const {
  CURL *inst = http::curlEasyInit();
  Json::Value value;
  Json::Reader reader;

  std::stringstream url;
  url << baseApi << "/editMessageCaption?chat_id=" << chatId
      << "&message_id=" << messageId << "&caption=";
  encode(url, caption);

  reader.parse(http::get(inst, url.str()), value);
  curl_easy_cleanup(inst);

  if (!value.get("ok", "").asBool())
    throw TelegramException(value.get("description", "").asCString());

  return api_types::Message(value.get("result", ""));
}

api_types::Message tgbot::methods::Api::editMessageCaption(
    const std::string &chatId, const std::string &messageId,
    const types::InlineKeyboardMarkup &replyMarkup,
    const std::string &caption) const {
  CURL *inst = http::curlEasyInit();
  Json::Value value;
  Json::Reader reader;

  std::stringstream url;
  url << baseApi << "/editMessageCaption?chat_id=" << chatId
      << "&message_id=" << messageId << "&caption=";
  encode(url, caption);
  url << "&reply_markup=";
  encode(url, replyMarkup.toString());

  reader.parse(http::get(inst, url.str()), value);
  curl_easy_cleanup(inst);

  if (!value.get("ok", "").asBool())
    throw TelegramException(value.get("description", "").asCString());

  return api_types::Message(value.get("result", ""));
}

api_types::Message
tgbot::methods::Api::editMessageCaption(const std::string &inlineMessageId,
                                        const std::string &caption) const {
  CURL *inst = http::curlEasyInit();
  Json::Value value;
  Json::Reader reader;

  std::stringstream url;
  url << baseApi << "/editMessageCaption?inline_message_id=" << inlineMessageId
      << "&caption=";
  encode(url, caption);

  reader.parse(http::get(inst, url.str()), value);
  curl_easy_cleanup(inst);

  if (!value.get("ok", "").asBool())
    throw TelegramException(value.get("description", "").asCString());

  return api_types::Message(value.get("result", ""));
}

api_types::Message tgbot::methods::Api::editMessageCaption(
    const std::string &inlineMessageId,
    const types::InlineKeyboardMarkup &replyMarkup,
    const std::string &caption) const {
  CURL *inst = http::curlEasyInit();
  Json::Value value;
  Json::Reader reader;

  std::stringstream url;
  url << baseApi << "/editMessageCaption?inline_message_id=" << inlineMessageId
      << "&caption=";
  encode(url, caption);
  url << "&reply_markup=";
  encode(url, replyMarkup.toString());

  reader.parse(http::get(inst, url.str()), value);
  curl_easy_cleanup(inst);

  if (!value.get("ok", "").asBool())
    throw TelegramException(value.get("description", "").asCString());

  return api_types::Message(value.get("result", ""));
}

// editMessageReplyMarkup
api_types::Message tgbot::methods::Api::editMessageReplyMarkup(
    const std::string &chatId, const std::string &messageId,
    const types::InlineKeyboardMarkup &replyMarkup) const {
  CURL *inst = http::curlEasyInit();
  Json::Value value;
  Json::Reader reader;

  std::stringstream url;
  url << baseApi << "/editMessageReplyMarkup?chat_id=" << chatId
      << "&message_id=" << messageId << "&reply_markup=";
  encode(url, replyMarkup.toString());

  reader.parse(http::get(inst, url.str()), value);
  curl_easy_cleanup(inst);

  if (!value.get("ok", "").asBool())
    throw TelegramException(value.get("description", "").asCString());

  return api_types::Message(value.get("result", ""));
}

api_types::Message tgbot::methods::Api::editMessageReplyMarkup(
    const std::string &inlineMessageId,
    const types::InlineKeyboardMarkup &replyMarkup) const {
  CURL *inst = http::curlEasyInit();
  Json::Value value;
  Json::Reader reader;

  std::stringstream url;
  url << baseApi
      << "/editMessageReplyMarkup?inline_message_id=" << inlineMessageId
      << "&reply_markup=";
  encode(url, replyMarkup.toString());

  reader.parse(http::get(inst, url.str()), value);
  curl_easy_cleanup(inst);

  if (!value.get("ok", "").asBool())
    throw TelegramException(value.get("description", "").asCString());

  return api_types::Message(value.get("result", ""));
}

// sendChatAction
bool tgbot::methods::Api::sendChatAction(
    const std::string &chatId, const types::ChatAction &action) const {
  CURL *inst = http::curlEasyInit();
  Json::Value value;
  Json::Reader reader;
  std::stringstream url;

  url << baseApi << "/sendChatAction?chat_id=" << chatId << "&action=";
  if (action == types::ChatAction::TYPING)
    url << "typing";
  else if (action == types::ChatAction::FIND_LOCATION)
    url << "find_location";
  else if (action == types::ChatAction::RECORD_AUDIO)
    url << "record_audio";
  else if (action == types::ChatAction::RECORD_VIDEO)
    url << "record_video";
  else if (action == types::ChatAction::RECORD_VIDEO_NOTE)
    url << "record_video_note";
  else if (action == types::ChatAction::UPLOAD_AUDIO)
    url << "upload_audio";
  else if (action == types::ChatAction::UPLOAD_DOCUMENT)
    url << "upload_document";
  else if (action == types::ChatAction::UPLOAD_PHOTO)
    url << "upload_photo";
  else if (action == types::ChatAction::UPLOAD_VIDEO)
    url << "upload_video";
  else if (action == types::ChatAction::UPLOAD_VIDEO_NOTE)
    url << "upload_video_note";

  reader.parse(http::get(inst, url.str()), value);
  curl_easy_cleanup(inst);

  if (!value.get("ok", "").asBool())
    throw TelegramException(value.get("description", "").asCString());

  return true;
}

// sendContact
api_types::Message tgbot::methods::Api::sendContact(
    const std::string &chatId, const std::string &phoneNumber,
    const std::string &firstName, const std::string &lastName,
    const bool &disableNotification, const int &replyToMessageId,
    const types::ReplyMarkup &replyMarkup) const {
  CURL *inst = http::curlEasyInit();
  Json::Value value;
  Json::Reader reader;

  std::stringstream url;
  url << baseApi << "/sendContact?chat_id=" << chatId << "&phone_number=";
  encode(url, phoneNumber);
  url << "&first_name=";
  encode(url, firstName);

  if (lastName != "") {
    url << "&last_name=";
    encode(url, lastName);
  }

  if (disableNotification)
    url << "&disable_notification=true";

  if (replyToMessageId != -1)
    url << "&reply_to_message_id=" << replyToMessageId;

  const std::string &&markup = replyMarkup.toString();
  if (markup != "") {
    url << "&reply_markup=";
    encode(url, markup);
  }

  reader.parse(http::get(inst, url.str()), value);
  curl_easy_cleanup(inst);

  if (!value.get("ok", "").asBool())
    throw TelegramException(value.get("description", "").asCString());

  return api_types::Message(value.get("result", ""));
}

// sendGame
api_types::Message tgbot::methods::Api::sendGame(
    const int &chatId, const std::string &gameShortName,
    const bool &disableNotification, const int &replyToMessageId,
    const types::ReplyMarkup &replyMarkup) const {
  CURL *inst = http::curlEasyInit();
  Json::Value value;
  Json::Reader reader;

  std::stringstream url;
  url << baseApi << "/sendGame?chat_id=" << chatId << "&game_short_name=";
  encode(url, gameShortName);

  if (disableNotification)
    url << "&disable_notification=true";

  if (replyToMessageId != -1)
    url << "&replyToMessageId=" << replyToMessageId;

  const std::string &&markup = replyMarkup.toString();
  if (markup != "") {
    url << "&reply_markup=";
    encode(url, markup);
  }

  reader.parse(http::get(inst, url.str()), value);
  curl_easy_cleanup(inst);

  if (!value.get("ok", "").asBool())
    throw TelegramException(value.get("description", "").asCString());

  return api_types::Message(value.get("result", ""));
}

// sendLocation
api_types::Message tgbot::methods::Api::sendLocation(
    const std::string &chatId, const double &latitude, const double &longitude,
    const bool &disableNotification, const int &replyToMessageId,
    const types::ReplyMarkup &replyMarkup) const {
  CURL *inst = http::curlEasyInit();
  Json::Value value;
  Json::Reader reader;

  std::stringstream url;
  url << baseApi << "/sendLocation?chat_id=" << chatId
      << "&latitude=" << latitude << "&longitude=" << longitude;

  if (disableNotification)
    url << "&disable_notification=true";

  if (replyToMessageId != -1)
    url << "&replyToMessageId=" << replyToMessageId;

  const std::string &&markup = replyMarkup.toString();
  if (markup != "") {
    url << "&reply_markup=";
    encode(url, markup);
  }

  reader.parse(http::get(inst, url.str()), value);
  curl_easy_cleanup(inst);

  if (!value.get("ok", "").asBool())
    throw TelegramException(value.get("description", "").asCString());

  return api_types::Message(value.get("result", ""));
}

// sendVenue
api_types::Message tgbot::methods::Api::sendVenue(
    const std::string &chatId, const double &latitude, const double &longitude,
    const std::string &title, const std::string &address,
    const std::string &foursquareId, const bool &disableNotification,
    const int &replyToMessageId, const types::ReplyMarkup &replyMarkup) const {
  CURL *inst = http::curlEasyInit();
  Json::Value value;
  Json::Reader reader;

  std::stringstream url;
  url << baseApi << "/sendVenue?chat_id=" << chatId << "&latitude=" << latitude
      << "&longitude=" << longitude << "&title=";
  encode(url, title);
  url << "&address=";
  encode(url, address);

  if (foursquareId != "")
    url << "&foursquare_id" << foursquareId;

  if (disableNotification)
    url << "&disable_notification=true";

  if (replyToMessageId != -1)
    url << "&replyToMessageId=" << replyToMessageId;

  const std::string &&markup = replyMarkup.toString();
  if (markup != "") {
    url << "&reply_markup=";
    encode(url, markup);
  }

  reader.parse(http::get(inst, url.str()), value);
  curl_easy_cleanup(inst);

  if (!value.get("ok", "").asBool())
    throw TelegramException(value.get("description", "").asCString());

  return api_types::Message(value.get("result", ""));
}

// sendInvoice
api_types::Message tgbot::methods::Api::sendInvoice(
    const int &chatId, const types::Invoice &invoice,
    const bool &disableNotification, const int &replyToMessageId) const {
  CURL *inst = http::curlEasyInit();
  Json::Value value;
  Json::Reader reader;

  std::stringstream url;
  url << baseApi << "/sendInvoice?chat_id=" << chatId;
  invoiceParams(url, invoice);

  if (disableNotification)
    url << "&disable_notification=true";

  if (replyToMessageId != -1)
    url << "&replyToMessageId=" << replyToMessageId;

  reader.parse(http::get(inst, url.str()), value);
  curl_easy_cleanup(inst);

  if (!value.get("ok", "").asBool())
    throw TelegramException(value.get("description", "").asCString());

  return api_types::Message(value.get("result", ""));
}

api_types::Message tgbot::methods::Api::sendInvoice(
    const int &chatId, const types::Invoice &invoice,
    const types::InlineKeyboardMarkup &replyMarkup,
    const bool &disableNotification, const int &replyToMessageId) const {
  CURL *inst = http::curlEasyInit();
  Json::Value value;
  Json::Reader reader;

  std::stringstream url;
  url << baseApi << "/sendInvoice?chat_id=" << chatId << "&reply_markup=";
  encode(url, replyMarkup.toString());
  invoiceParams(url, invoice);

  if (disableNotification)
    url << "&disable_notification=true";

  if (replyToMessageId != -1)
    url << "&replyToMessageId=" << replyToMessageId;

  reader.parse(http::get(inst, url.str()), value);
  curl_easy_cleanup(inst);

  if (!value.get("ok", "").asBool())
    throw TelegramException(value.get("description", "").asCString());

  return api_types::Message(value.get("result", ""));
}

// sendVideo
api_types::Message tgbot::methods::Api::sendVideo(
    const std::string &chatId, const std::string &video,
    const types::FileSource &source, const std::string &mimeType,
    const int &duration, const int &width, const int &height,
    const std::string &caption, const bool &disableNotification,
    const int &replyToMessageId, const types::ReplyMarkup &replyMarkup) const {
  CURL *inst = http::curlEasyInit();
  Json::Value value;
  Json::Reader reader;

  if (source == types::FileSource::EXTERNAL) {
    std::stringstream url;
    url << baseApi << "/sendVideo"
        << "?chat_id=" << chatId << "&video=";

    encode(url, video);

    if (duration != -1)
      url << "&duration=" << duration;

    if (width != -1)
      url << "&width=" << width;

    if (height != -1)
      url << "&height=" << height;

    if (caption != "") {
      url << "&caption=";
      encode(url, caption);
    }

    if (disableNotification)
      url << "&disable_notification=true";

    if (replyToMessageId != -1)
      url << "&reply_to_message_id=" << replyToMessageId;

    const std::string &&markup = replyMarkup.toString();
    if (markup != "") {
      url << "&reply_markup=";
      encode(url, markup);
    }

    reader.parse(http::get(inst, url.str()), value);
  } else
    reader.parse(http::multiPartUpload(
                     inst, baseApi + "/sendVideo", chatId, mimeType, video,
                     duration, width, height, caption, disableNotification,
                     replyToMessageId, replyMarkup.toString()),
                 value);

  curl_easy_cleanup(inst);

  if (!value.get("ok", "").asBool())
    throw TelegramException(value.get("description", "").asCString());

  return api_types::Message(value.get("result", ""));
}

// sendDocument
api_types::Message tgbot::methods::Api::sendDocument(
    const std::string &chatId, const std::string &document,
    const types::FileSource &source, const std::string &mimeType,
    const std::string &caption, const bool &disableNotification,
    const int &replyToMessageId, const types::ReplyMarkup &replyMarkup) const {
  CURL *inst = http::curlEasyInit();
  Json::Value value;
  Json::Reader reader;

  if (source == types::FileSource::EXTERNAL) {
    std::stringstream url;
    url << baseApi << "/sendDocument?chat_id=" << chatId << "&document=";

    encode(url, document);

    if (caption != "") {
      url << "&caption=";
      encode(url, caption);
    }

    if (disableNotification)
      url << "&disable_notification=true";

    if (replyToMessageId != -1)
      url << "&reply_to_message_id=" << replyToMessageId;

    const std::string &&markup = replyMarkup.toString();
    if (markup != "") {
      url << "&reply_markup=";
      encode(url, markup);
    }

    reader.parse(http::get(inst, url.str()), value);
  } else
    reader.parse(http::multiPartUpload(inst, baseApi + "/sendDocument", chatId,
                                       mimeType, "document", document, caption,
                                       disableNotification, replyToMessageId,
                                       replyMarkup.toString()),
                 value);

  curl_easy_cleanup(inst);

  if (!value.get("ok", "").asBool())
    throw TelegramException(value.get("description", "").asCString());

  return api_types::Message(value.get("result", ""));
}

// sendPhoto
api_types::Message tgbot::methods::Api::sendPhoto(
    const std::string &chatId, const std::string &photo,
    const types::FileSource &source, const std::string &mimeType,
    const std::string &caption, const bool &disableNotification,
    const int &replyToMessageId, const types::ReplyMarkup &replyMarkup) const {
  CURL *inst = http::curlEasyInit();
  Json::Value value;
  Json::Reader reader;

  if (source == types::FileSource::EXTERNAL) {
    std::stringstream url;
    url << baseApi << "/sendPhoto?chat_id=" << chatId << "&photo=";

    encode(url, photo);

    if (caption != "") {
      url << "&caption=";
      encode(url, caption);
    }

    if (disableNotification)
      url << "&disable_notification=true";

    if (replyToMessageId != -1)
      url << "&reply_to_message_id=" << replyToMessageId;

    const std::string &&markup = replyMarkup.toString();
    if (markup != "") {
      url << "&reply_markup=";
      encode(url, markup);
    }

    reader.parse(http::get(inst, url.str()), value);
  } else
    reader.parse(http::multiPartUpload(inst, baseApi + "/sendPhoto", chatId,
                                       mimeType, "photo", photo, caption,
                                       disableNotification, replyToMessageId,
                                       replyMarkup.toString()),
                 value);

  curl_easy_cleanup(inst);

  if (!value.get("ok", "").asBool())
    throw TelegramException(value.get("description", "").asCString());

  return api_types::Message(value.get("result", ""));
}

// sendAudio
api_types::Message tgbot::methods::Api::sendAudio(
    const std::string &chatId, const std::string &audio,
    const types::FileSource &source, const std::string &mimeType,
    const std::string &caption, const int &duration,
    const std::string &performer, const std::string &title,
    const bool &disableNotification, const int &replyToMessageId,
    const types::ReplyMarkup &replyMarkup) const {
  CURL *inst = http::curlEasyInit();
  Json::Value value;
  Json::Reader reader;

  if (source == types::FileSource::EXTERNAL) {
    std::stringstream url;
    url << baseApi << "/sendAudio?chat_id=" << chatId << "&audio=";

    encode(url, audio);

    if (caption != "") {
      url << "&caption=";
      encode(url, caption);
    }

    if (performer != "") {
      url << "&performer=";
      encode(url, performer);
    }

    if (title != "") {
      url << "&title=";
      encode(url, title);
    }

    if (disableNotification)
      url << "&disable_notification=true";

    if (replyToMessageId != -1)
      url << "&reply_to_message_id=" << replyToMessageId;

    if (duration != -1) {
      url << "&duration=" << duration;
    }

    const std::string &&markup = replyMarkup.toString();
    if (markup != "") {
      url << "&reply_markup=";
      encode(url, markup);
    }

    reader.parse(http::get(inst, url.str()), value);
  } else
    reader.parse(http::multiPartUpload(
                     inst, baseApi + "/sendAudio", chatId, mimeType, audio,
                     caption, duration, performer, title, disableNotification,
                     replyToMessageId, replyMarkup.toString()),
                 value);

  curl_easy_cleanup(inst);

  if (!value.get("ok", "").asBool())
    throw TelegramException(value.get("description", "").asCString());

  return api_types::Message(value.get("result", ""));
}

// sendVoice
api_types::Message tgbot::methods::Api::sendVoice(
    const std::string &chatId, const std::string &voice,
    const types::FileSource &source, const std::string &caption,
    const int &duration, const bool &disableNotification,
    const int &replyToMessageId, const types::ReplyMarkup &replyMarkup) const {
  CURL *inst = http::curlEasyInit();
  Json::Value value;
  Json::Reader reader;

  if (source == types::FileSource::EXTERNAL) {
    std::stringstream url;
    url << baseApi << "/sendVoice?chat_id=" << chatId << "&voice=";
    encode(url, voice);

    if (duration != -1)
      url << "&duration=" << duration;

    if (caption != "") {
      url << "&caption=";
      encode(url, caption);
    }

    if (disableNotification)
      url << "&disable_notification=true";

    if (replyToMessageId != -1)
      url << "&reply_to_message_id=" << replyToMessageId;

    const std::string &&markup = replyMarkup.toString();
    if (markup != "") {
      url << "&reply_markup=";
      encode(url, markup);
    }

    reader.parse(http::get(inst, url.str()), value);
  } else
    reader.parse(http::multiPartUpload(
                     inst, baseApi + "/sendVoice", chatId, "audio/ogg", "audio",
                     voice, caption, duration, disableNotification,
                     replyToMessageId, replyMarkup.toString()),
                 value);
  curl_easy_cleanup(inst);

  if (!value.get("ok", "").asBool())
    throw TelegramException(value.get("description", "").asCString());

  return api_types::Message(value.get("result", ""));
}

// sendSticker
api_types::Message tgbot::methods::Api::sendSticker(
    const std::string &chatId, const std::string &sticker,
    const types::FileSource &source, const bool &disableNotification,
    const int &replyToMessageId, const types::ReplyMarkup &replyMarkup) const {
  CURL *inst = http::curlEasyInit();
  Json::Value value;
  Json::Reader reader;

  if (source == types::FileSource::EXTERNAL) {
    std::stringstream url;
    url << baseApi << "/sendSticker?chat_id=" << chatId << "&sticker=";

    encode(url, sticker);

    if (disableNotification)
      url << "&disable_notification=true";

    if (replyToMessageId != -1)
      url << "&reply_to_message_id=" << replyToMessageId;

    const std::string &&markup = replyMarkup.toString();
    if (markup != "") {
      url << "&reply_markup=";
      encode(url, markup);
    }

    reader.parse(http::get(inst, url.str()), value);
  } else
    reader.parse(http::multiPartUpload(inst, baseApi + "/sendSticker", chatId,
                                       sticker, disableNotification,
                                       replyToMessageId,
                                       replyMarkup.toString()),
                 value);

  curl_easy_cleanup(inst);

  if (!value.get("ok", "").asBool())
    throw TelegramException(value.get("description", "").asCString());

  return api_types::Message(value.get("result", ""));
}

// sendVideoNote
api_types::Message tgbot::methods::Api::sendVideoNote(
    const std::string &chatId, const std::string &videoNote,
    const types::FileSource &source, const std::string &caption,
    const int &duration, const bool &disableNotification,
    const int &replyToMessageId, const types::ReplyMarkup &replyMarkup) const {
  CURL *inst = http::curlEasyInit();
  Json::Value value;
  Json::Reader reader;

  if (source == types::FileSource::EXTERNAL) {
    std::stringstream url;
    url << baseApi << "/sendVideoNote?chat_id=" << chatId << "&video_note=";

    encode(url, videoNote);

    if (duration != -1)
      url << "&duration=" << duration;

    if (caption != "") {
      url << "&caption=";
      encode(url, caption);
    }

    if (disableNotification)
      url << "&disable_notification=true";

    if (replyToMessageId != -1)
      url << "&reply_to_message_id=" << replyToMessageId;

    const std::string &&markup = replyMarkup.toString();
    if (markup != "") {
      url << "&reply_markup=";
      encode(url, markup);
    }

    reader.parse(http::get(inst, url.str()), value);
  } else
    reader.parse(http::multiPartUpload(
                     inst, baseApi + "/sendVideoNote", chatId, "video/mp4",
                     "video", videoNote, caption, duration, disableNotification,
                     replyToMessageId, replyMarkup.toString()),
                 value);

  curl_easy_cleanup(inst);

  if (!value.get("ok", "").asBool())
    throw TelegramException(value.get("description", "").asCString());

  return api_types::Message(value.get("result", ""));
}
