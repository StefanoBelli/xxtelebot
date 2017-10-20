#include <sstream>
#include <tgbot/methods/api.h>
#include <tgbot/utils/https.h>
#include <jsoncpp/json/json.h>
#include <tgbot/bot.h>

using namespace tgbot::methods;
using namespace tgbot::utils;

static inline void allowedUpdatesToString(const std::vector<api_types::UpdateType>& updates,
                                    std::stringstream& stream) {
    stream << "[";
    for (auto const &update : updates) {
        switch (update) {
            case api_types::UpdateType::MESSAGE:
                stream << "\"message\",";
                break;
            case api_types::UpdateType::CALLBACK_QUERY:
                stream << "\"callback_query\",";
                break;
            case api_types::UpdateType::INLINE_QUERY :
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

static inline void removeComma(const std::stringstream& stream, std::string& target) {
    std::string &&req = stream.str();
    char &endpos = req.at(req.size() - 1);
    if (endpos == ',')
        endpos = ']';
    target = req;
}

//Api constructors

//Webhook, no further action
tgbot::methods::Api::Api(const std::string& token) :
    baseApi("https://api.telegram.org/bot" + token)
{}

//Webhook
tgbot::methods::Api::Api(const std::string& token,
		const std::string& url,
		const int& maxConnections,
		const std::vector<api_types::UpdateType>& allowedUpdates) :
            baseApi("https://api.telegram.org/bot" + token) {

        if(!setWebhook(url,maxConnections,allowedUpdates))
            throw TelegramException("Unable to set webhook");
}

//Webhook with cert
tgbot::methods::Api::Api(const std::string& token,
		const std::string& url,
		const std::string& certificate,
		const int& maxConnections,
		const std::vector<api_types::UpdateType>& allowedUpdates) :
            baseApi("https://api.telegram.org/bot" + token) {

        if(!setWebhook(url,certificate,maxConnections,allowedUpdates))
            throw TelegramException("Unable to set webhook");
}

//HTTP Long polling
tgbot::methods::Api::Api(const std::string &token,
		const std::vector<api_types::UpdateType> &allowedUpdates,
		const int &timeout,
		const int &limit) :
	        baseApi("https://api.telegram.org/bot" + token),
	        currentOffset(0) {

		std::stringstream fullApiRequest;
		fullApiRequest << baseApi << "/getUpdates?limit=" << limit << "&timeout=" << timeout;

		if (allowedUpdates.size()) {
            fullApiRequest << "&allowed_updates=";
			allowedUpdatesToString(allowedUpdates,fullApiRequest);
			removeComma(fullApiRequest,updateApiRequest);
		} else 
			updateApiRequest = fullApiRequest.str();
}

//
//API implementations
//

//getUpdates (internal usage)
int tgbot::methods::Api::getUpdates(void *c, std::vector<api_types::Update>& updates) {
	std::stringstream updatesRequest;
	updatesRequest << updateApiRequest << "&offset=" << currentOffset;

	Json::Value rootUpdate;
	Json::Reader parser;

	parser.parse(utils::http::get(c, updatesRequest.str()), rootUpdate);

	if (!rootUpdate.get("ok", "").asBool())
		throw TelegramException(rootUpdate.get("description", "").asCString());

	Json::Value valueUpdates = rootUpdate.get("result", "");
	const int& updatesCount = valueUpdates.size();
	if (!updatesCount)
		return 0;

	for (auto const &singleUpdate : valueUpdates)
		updates.emplace_back(singleUpdate);

	currentOffset = 1 + valueUpdates[updatesCount - 1].get("update_id", "").asInt64();

	return updatesCount;
}

//
// Availible API Methods
//

//setWebhook
bool tgbot::methods::Api::setWebhook(const std::string &url, const int &maxConnections,
                                     const std::vector<api_types::UpdateType> &allowedUpdates) {
    std::stringstream request;
    request << baseApi << "/setWebhook?url=" << url << "&max_connections=" << maxConnections;

    std::string setWebhookRequest;
    if (allowedUpdates.size()) {
        request << "&allowed_updates=";
        allowedUpdatesToString(allowedUpdates,request);
        removeComma(request,setWebhookRequest);
    } else
        setWebhookRequest = request.str();

    CURL* inst = http::curlEasyInit();
    Json::Value value;
    Json::Reader reader;

    reader.parse(http::get(inst,setWebhookRequest),value);
    curl_easy_cleanup(inst);

    bool isOk = value.get("ok","").asBool();
    if(isOk)
        urlWebhook = url;

    return isOk;
}

bool tgbot::methods::Api::setWebhook(const std::string &url, const std::string &certificate,
                                     const int &maxConnections,
                                     const std::vector<api_types::UpdateType> &allowedUpdates) {
    CURL* inst = http::curlEasyInit();
    Json::Value value;
    Json::Reader reader;

    if(!allowedUpdates.size())
        reader.parse(http::multiPartUpload(inst, baseApi + "/setWebhook", certificate, url, maxConnections),
                     value);
    else {
        std::stringstream request;
        std::string final;

        allowedUpdatesToString(allowedUpdates, request);
        removeComma(request, final);

        reader.parse(http::multiPartUpload(inst, baseApi + "/setWebhook", certificate, url, maxConnections, final),
                     value);
    }

    curl_easy_cleanup(inst);

    bool isOk = value.get("ok","").asBool();
    if(isOk)
        urlWebhook = url;

    return isOk;
}

//deleteWebhook
bool tgbot::methods::Api::deleteWebhook() const {
    CURL* inst = http::curlEasyInit();
    bool isOk = (http::get(inst,baseApi + "/deleteWebhook").find("\"ok\":true") != std::string::npos);
    curl_easy_cleanup(inst);
    return isOk;
}

//getWebhookInfo
api_types::WebhookInfo tgbot::methods::Api::getWebhookInfo() const {
    CURL* inst = http::curlEasyInit();
    Json::Value value;
    Json::Reader reader;

    reader.parse(http::get(inst,baseApi + "/getWebhookInfo"), value);
    curl_easy_cleanup(inst);

    if(!value.get("ok","").asBool())
        throw TelegramException(value.get("description","").asCString());

    return api_types::WebhookInfo(value.get("result",""));
}

//getMe
api_types::User tgbot::methods::Api::getMe() const {
    CURL* inst = http::curlEasyInit();
    Json::Value value;
    Json::Reader reader;

    reader.parse(http::get(inst,baseApi + "/getMe"), value);
    curl_easy_cleanup(inst);

    if(!value.get("ok","").asBool())
        throw TelegramException(value.get("description","").asCString());

    return api_types::User(value.get("result",""));
}

//getChat
api_types::Chat tgbot::methods::Api::getChat(const std::string &chatId) const {
    CURL* inst = http::curlEasyInit();
    Json::Value value;
    Json::Reader reader;

    reader.parse(http::get(inst,baseApi + "/getChat?chat_id=\"" + chatId + "\""), value);
    curl_easy_cleanup(inst);

    if(!value.get("ok","").asBool())
        throw TelegramException(value.get("description","").asCString());

    return api_types::Chat(value.get("result",""));
}

//getChatMembersCount
unsigned tgbot::methods::Api::getChatMembersCount(const std::string &chatId) const {
    CURL* inst = http::curlEasyInit();
    Json::Value value;
    Json::Reader reader;

    reader.parse(http::get(inst,baseApi + "/getChatMembersCount?chat_id=\"" + chatId + "\""), value);
    curl_easy_cleanup(inst);

    if(!value.get("ok","").asBool())
        throw TelegramException(value.get("description","").asCString());

    return value.get("result","").asUInt();
}

//getFile
api_types::File tgbot::methods::Api::getFile(const std::string &fileId) const {
    CURL* inst = http::curlEasyInit();
    Json::Value value;
    Json::Reader reader;

    reader.parse(http::get(inst,baseApi + "/getFile?file_id=\"" + fileId + "\""), value);
    curl_easy_cleanup(inst);

    if(!value.get("ok","").asBool())
        throw TelegramException(value.get("description","").asCString());

    return api_types::File(value.get("result",""));
}

//getChatMember
api_types::ChatMember tgbot::methods::Api::getChatMember(const std::string &chatId, const int &userId) const {
    CURL* inst = http::curlEasyInit();
    Json::Value value;
    Json::Reader reader;

    std::stringstream url;
    url << baseApi << "/getChatMember?chat_id=\"" << chatId << "\"&user_id=" << userId;

    reader.parse(http::get(inst,url.str()), value);
    curl_easy_cleanup(inst);

    if(!value.get("ok","").asBool())
        throw TelegramException(value.get("description","").asCString());

    return api_types::ChatMember(value.get("result",""));
}

//getStickerSet
api_types::StickerSet tgbot::methods::Api::getStickerSet(const std::string &name) const {
    CURL* inst = http::curlEasyInit();
    Json::Value value;
    Json::Reader reader;

    reader.parse(http::get(inst,baseApi + "/getStickerSet?name=\"" + name + "\""), value);
    curl_easy_cleanup(inst);

    if(!value.get("ok","").asBool())
        throw TelegramException(value.get("description","").asCString());

    return api_types::StickerSet(value.get("result",""));
}

//getUserProfilePhotos
api_types::UserProfilePhotos tgbot::methods::Api::getUserProfilePhotos(const int &userId, const unsigned int &offset,
                                                                       const unsigned int &limit) const {
    CURL* inst = http::curlEasyInit();
    Json::Value value;
    Json::Reader reader;

    std::stringstream url;
    url << baseApi << "/getUserProfilePhotos?user_id=" << userId << "&offset=" << offset
            << "&limit=" << limit;

    reader.parse(http::get(inst,url.str()), value);
    curl_easy_cleanup(inst);

    if(!value.get("ok","").asBool())
        throw TelegramException(value.get("description","").asCString());

    return api_types::UserProfilePhotos(value.get("result",""));
}

//getChatAdministrators
std::vector<api_types::ChatMember> tgbot::methods::Api::getChatAdministrators(const std::string &chatId) const {
    CURL* inst = http::curlEasyInit();
    Json::Value value;
    Json::Reader reader;

    reader.parse(http::get(inst,baseApi + "/getChatAdministrators?chat_id=\"" + chatId + "\""), value);
    curl_easy_cleanup(inst);

    if(!value.get("ok","").asBool())
        throw TelegramException(value.get("description","").asCString());

    std::vector<api_types::ChatMember> members;
    for(auto const member : value.get("result",""))
        members.emplace_back(member);

    return members;
}

//getGameHighScores
std::vector<api_types::GameHighScore> tgbot::methods::Api::getGameHighScores(const int &userId, const int &chatId,
                                                                             const int &messageId) const {
    CURL* inst = http::curlEasyInit();
    Json::Value value;
    Json::Reader reader;

    std::stringstream url;
    url << baseApi << "/getGameHighScores?user_id=" << userId << "&chat_id=" << chatId
            << "&message_id=" << messageId;

    reader.parse(http::get(inst,url.str()), value);
    curl_easy_cleanup(inst);

    if(!value.get("ok","").asBool())
        throw TelegramException(value.get("description","").asCString());

    std::vector<api_types::GameHighScore> members;
    for(auto const member : value.get("result",""))
        members.emplace_back(member);

    return members;
}

std::vector<api_types::GameHighScore> tgbot::methods::Api::getGameHighScores(const int &userId,
                                                                             const std::string &inlineMessageId) const {
    CURL* inst = http::curlEasyInit();
    Json::Value value;
    Json::Reader reader;

    std::stringstream url;
    url << baseApi << "/getGameHighScores?user_id=" << userId << "&inline_message_id=\""
            << inlineMessageId << "\"";

    reader.parse(http::get(inst,url.str()), value);
    curl_easy_cleanup(inst);

    if(!value.get("ok","").asBool())
        throw TelegramException(value.get("description","").asCString());

    std::vector<api_types::GameHighScore> members;
    for(auto const member : value.get("result",""))
        members.emplace_back(member);

    return members;
}