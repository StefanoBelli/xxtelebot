#include <tgbot/bot.h>
#include <tgbot/utils/https.h>

using namespace tgbot;

tgbot::Bot::Bot(const std::string &token,
		const std::string &useragent,
		const std::vector<types::UpdateType> &filterUpdates,
		const int &limit,
		const int &timeout) :
	Api(token,useragent,filterUpdates,timeout,limit),
	ua(useragent) {

	}

void tgbot::Bot::start() {
	std::vector<types::Update> updates;
	CURL* fetchConnection = utils::http::curlEasyInit(ua);

	curl_easy_setopt(fetchConnection,CURLOPT_TCP_KEEPALIVE,1L);
	curl_easy_setopt(fetchConnection,CURLOPT_TCP_KEEPIDLE,60);

	while(true) {
		updates = getUpdates(fetchConnection);
		if(updates.size())
			makeCallback(updates);
	}
}

void tgbot::Bot::makeCallback(const std::vector<types::Update>& updates) const {
	for(auto const& update : updates) {
		switch (update.updateType) {
			case types::UpdateType::MESSAGE:
				if (messageCallback) {
					types::Message *message{update.message.get()};
					if (message)
						return messageCallback(*message, *this);
				}

				break;
			case types::UpdateType::EDITED_MESSAGE:
				if (editedMessageCallback) {
					types::Message *editedMessage
					{update.editedMessage.get()};

					if (editedMessage)
						return editedMessageCallback(*editedMessage, *this);
				}

				break;
			case types::UpdateType::CALLBACK_QUERY:
				if (callbackQueryCallback) {
					types::CallbackQuery *callbackQuery
					{update.callbackQuery.get()};

					if (callbackQuery)
						return callbackQueryCallback(*callbackQuery, *this);
				}

				break;
			case types::UpdateType::CHOSEN_INLINE_RESULT:
				if (chosenInlineResultCallback) {
					types::ChosenInlineResult *chosenInlineResult
					{update.chosenInlineResult.get()};

					if (chosenInlineResult)
						return chosenInlineResultCallback(*chosenInlineResult, *this);
				}

				break;
			case types::UpdateType::EDITED_CHANNEL_POST:
				if (editedChannelPostCallback) {
					types::Message *editedChannelPost
					{update.editedChannelPost.get()};

					if (editedChannelPost)
						return editedChannelPostCallback(*editedChannelPost, *this);
				}

				break;
			case types::UpdateType::INLINE_QUERY:
				if (inlineQueryCallback) {
					types::InlineQuery *inlineQuery
					{update.inlineQuery.get()};

					if (inlineQuery)
						return inlineQueryCallback(*inlineQuery, *this);
				}

				break;
			case types::UpdateType::PRE_CHECKOUT_QUERY:
				if (preCheckoutQueryCallback) {
					types::PreCheckoutQuery *preCheckoutQuery
					{update.preCheckoutQuery.get()};

					if (preCheckoutQuery)
						return preCheckoutQueryCallback(*preCheckoutQuery, *this);
				}

				break;
			case types::UpdateType::SHIPPING_QUERY:
				if (shippingQueryCallback) {
					types::ShippingQuery *shippingQuery
					{update.shippingQuery.get()};

					if (shippingQuery)
						return shippingQueryCallback(*shippingQuery, *this);
				}

				break;
		}

		if (anyUpdateCallback)
			anyUpdateCallback(update, *this);
	}
}
