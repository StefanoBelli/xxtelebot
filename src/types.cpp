#include <string>
#include <jsoncpp/json/json.h>
#include <tgbot/types.h>

using namespace tgbot::types;

tgbot::types::Update::Update(const Json::Value &object) {
	if(object.isMember("message")) {
		message = std::unique_ptr<Message>(new Message(object.get("message","")));
		updateType = UpdateType::MESSAGE;
	} else if(object.isMember("edited_message")) {
		editedMessage = std::unique_ptr<Message>(new Message(object.get("edited_message","")));
		updateType = UpdateType::EDITED_MESSAGE;
	} else if(object.isMember("callback_query")) {
		callbackQuery = std::unique_ptr<CallbackQuery>(new CallbackQuery(object.get("callback_query","")));
		updateType = UpdateType::CALLBACK_QUERY;
	} else if(object.isMember("chosen_inline_result")) {
		chosenInlineResult = std::unique_ptr<ChosenInlineResult>(new ChosenInlineResult(object.get("chosen_inline_result","")));
		updateType = UpdateType::CHOSEN_INLINE_RESULT;
	} else if(object.isMember("inline_query")) {
		inlineQuery = std::unique_ptr<InlineQuery>(new InlineQuery(object.get("inline_query","")));
		updateType = UpdateType::INLINE_QUERY;
	} else if(object.isMember("shipping_query")) {
		shippingQuery = std::unique_ptr<ShippingQuery>(new ShippingQuery(object.get("shipping_query","")));
		updateType = UpdateType::SHIPPING_QUERY;
	} else if(object.isMember("pre_checkout_query")) {
		preCheckoutQuery = std::unique_ptr<PreCheckoutQuery>(new PreCheckoutQuery(object.get("pre_checkout_query","")));
		updateType = UpdateType::PRE_CHECKOUT_QUERY;
	} else if(object.isMember("edited_channel_post")) {
		editedChannelPost = std::unique_ptr<Message>(new Message(object.get("edited_channel_post","")));
		updateType = UpdateType::EDITED_CHANNEL_POST;
	} else if(object.isMember("channel_post")) {
        channelPost = std::unique_ptr<Message>(new Message(object.get("edited_channel_post","")));
        updateType = UpdateType::CHANNEL_POST;
    }
}

tgbot::types::Message::Message(const Json::Value &object) :
    chat(object.get("chat","")) {

}

tgbot::types::CallbackQuery::CallbackQuery(const Json::Value &object) :
    from(object.get("from","")) {

}

tgbot::types::ChosenInlineResult::ChosenInlineResult(const Json::Value &object) :
    from(object.get("from","")) {

}

tgbot::types::InlineQuery::InlineQuery(const Json::Value &object) :
    user(object.get("from","")) {

}

tgbot::types::ShippingQuery::ShippingQuery(const Json::Value &object) :
    shippingAddress(object.get("shipping_address","")), from(object.get("from","")) {

}

tgbot::types::PreCheckoutQuery::PreCheckoutQuery(const Json::Value &object) :
    from(object.get("from","")) {


}

tgbot::types::Chat::Chat(const Json::Value &object) {
    const std::string& type = object.get("type","").asString();
    if(type == "private")
        this->type = ChatType::PRIVATE;
    else if(type == "supergroup")
        this->type = ChatType::SUPERGROUP;
    else if(type == "group")
        this->type = ChatType::GROUP;
    else if(type == "channel")
        this->type = ChatType::CHANNEL;

    id = object.get("id","").asInt();

    if(this->type != ChatType::PRIVATE)
        allMembersAreAdministrators = object.get("all_members_are_administrators","").asBool();
}

tgbot::types::User::User(const Json::Value &object) :
    firstName(object.get("first_name","").asString()),
    id(object.get("id","").asInt()),
    isBot(object.get("is_bot","").asBool()) {

}

tgbot::types::ShippingAddress::ShippingAddress(const Json::Value &object) {
}
