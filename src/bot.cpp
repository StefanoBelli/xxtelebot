#include <thread>
#include <tgbot/bot.h>
#include <tgbot/utils/https.h>

using namespace tgbot;

tgbot::Bot::Bot(const std::string &token,
		const std::string &useragent,
		const std::vector<types::UpdateType> &filterUpdates,
		const int &limit,
		const int &timeout) :
	Api(token, useragent, filterUpdates, timeout, limit),
	ua(useragent) {

	}

void tgbot::Bot::start() {
	std::vector<types::Update> updates;
	CURL *fetchConnection = utils::http::curlEasyInit(ua);

	curl_easy_setopt(fetchConnection, CURLOPT_TCP_KEEPALIVE, 1L);
	curl_easy_setopt(fetchConnection, CURLOPT_TCP_KEEPIDLE, 60);

	while (true) {
		updates = getUpdates(fetchConnection);
		if (updates.size())
			makeCallback(updates);
	}
}


void tgbot::Bot::makeCallback(const std::vector<types::Update> &updates) const {
	std::thread tmpHolder;
	for (auto const &update : updates) {
		switch (update.updateType) {
			case types::UpdateType::MESSAGE:
				if (messageCallback)
					tmpHolder = std::thread(messageCallback, std::move(*update.message.get()), *this);

				break;
			case types::UpdateType::EDITED_MESSAGE:
				if (editedMessageCallback)
					tmpHolder = std::thread(editedMessageCallback, std::move(*update.editedMessage.get()), *this);

				break;
			case types::UpdateType::CALLBACK_QUERY:
				if (callbackQueryCallback)
					tmpHolder = std::thread(callbackQueryCallback, std::move(*update.callbackQuery.get()), *this);

				break;
			case types::UpdateType::CHOSEN_INLINE_RESULT:
				if (chosenInlineResultCallback)
					tmpHolder = std::thread(chosenInlineResultCallback, std::move(*update.chosenInlineResult.get()), *this);

				break;
			case types::UpdateType::EDITED_CHANNEL_POST:
				if (editedChannelPostCallback)
					tmpHolder = std::thread(editedChannelPostCallback, std::move(*update.editedChannelPost.get()), *this);

				break;
			case types::UpdateType::INLINE_QUERY:
				if (inlineQueryCallback) 
					tmpHolder = std::thread(inlineQueryCallback, std::move(*update.inlineQuery.get()), *this);

				break;
			case types::UpdateType::PRE_CHECKOUT_QUERY:
				if (preCheckoutQueryCallback) 
					tmpHolder = std::thread(preCheckoutQueryCallback, std::move(*update.preCheckoutQuery.get()), *this);

				break;
			case types::UpdateType::SHIPPING_QUERY:
				if (shippingQueryCallback)
					tmpHolder = std::thread(shippingQueryCallback, std::move(*update.shippingQuery.get()), *this);

				break;
			case types::UpdateType::CHANNEL_POST:
				if (channelPostCallback)
					tmpHolder = std::thread(channelPostCallback, std::move(*update.channelPost.get()), *this);

				break;
		}

		if (tmpHolder.joinable())
			tmpHolder.detach();
	}
}

tgbot::TelegramException::TelegramException(const char *_what) :
	_what(_what) {}
	
const char *tgbot::TelegramException::what() const noexcept {
	return _what;
}
