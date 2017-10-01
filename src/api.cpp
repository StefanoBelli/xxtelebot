#include <sstream>
#include <tgbot/methods/api.h>
#include <tgbot/utils/https.h>
#include <jsoncpp/json/json.h>
#include <tgbot/bot.h>

using namespace tgbot::methods;

tgbot::methods::Api::Api(const std::string &token,
                         const std::string &useragent,
                         const std::vector<api_types::UpdateType> &allowedUpdates,
                         const int &timeout,
                         const int &limit) :

        baseApi("https://api.telegram.org/bot" + token),
        ua(useragent),
        currentOffset(0) {

    std::stringstream fullApiRequest;
    fullApiRequest << baseApi << "/getUpdates?limit=" << limit << "&timeout=" << timeout;

    if (allowedUpdates.size()) {
        fullApiRequest << "&allowed_updates=[";
        for (auto const &update : allowedUpdates) {
            switch (update) {
                case api_types::UpdateType::MESSAGE:
                    fullApiRequest << "\"message\",";
                    break;
                case api_types::UpdateType::CALLBACK_QUERY:
                    fullApiRequest << "\"callback_query\",";
                    break;
                case api_types::UpdateType::INLINE_QUERY :
                    fullApiRequest << "\"inline_query\",";
                    break;
                case api_types::UpdateType::CHOSEN_INLINE_RESULT:
                    fullApiRequest << "\"chosen_inline_result\",";
                    break;
                case api_types::UpdateType::PRE_CHECKOUT_QUERY:
                    fullApiRequest << "\"pre_checkout_query\",";
                    break;
                case api_types::UpdateType::SHIPPING_QUERY:
                    fullApiRequest << "\"shipping_query\",";
                    break;
                case api_types::UpdateType::EDITED_CHANNEL_POST:
                    fullApiRequest << "\"edited_channel_post\",";
                    break;
                case api_types::UpdateType::EDITED_MESSAGE:
                    fullApiRequest << "\"edited_message\",";
                    break;
                case api_types::UpdateType::CHANNEL_POST:
                    fullApiRequest << "\"channel_post\"";
                    break;
            }
        }
    }

    std::string req = fullApiRequest.str();
    char &endpos = req.at(req.size() - 1);
    if (endpos == ',')
        endpos = ']';

    updateApiRequest = req;
}

std::vector<api_types::Update> tgbot::methods::Api::getUpdates(void *c) {
    std::stringstream updatesRequest;
    updatesRequest << updateApiRequest << "&offset=" << currentOffset;

    Json::Value rootUpdate;
    Json::Reader parser;

    parser.parse(utils::http::get(c, updatesRequest.str()), rootUpdate);

    if (!rootUpdate.get("ok", "").asBool())
        throw TelegramException(rootUpdate.get("description", "").asCString());

    std::vector<api_types::Update> finalUpdates;

    Json::Value updates = rootUpdate.get("result", "");
    if (!updates.size())
        return {};

    for (auto const &singleUpdate : updates)
        finalUpdates.emplace_back(singleUpdate);

    currentOffset = updates[updates.size() - 1].get("update_id", "").asInt64();
    currentOffset++;

    return finalUpdates;
}
