#include <thread>
#include <tgbot/bot.h>
#include <tgbot/utils/https.h>

using namespace tgbot;

tgbot::LongPollBot::LongPollBot(const std::string &token,
		const std::vector<types::UpdateType> &filterUpdates,
		const int &limit,
		const int &timeout) :
	Bot(token,filterUpdates,limit,timeout)
{}

tgbot::WebhookBot::WebhookBot(const std::string &token) :
    Bot(token)
{}

tgbot::WebhookBot::WebhookBot(const std::string& token,
		const std::string& url,
		const int& maxConnections,
		const std::vector<types::UpdateType>& filterUpdates) :
	Bot(token,url,maxConnections,filterUpdates)
{}

tgbot::WebhookBot::WebhookBot(const std::string& token,
		const std::string& url,
		const std::string& certificate,
		const int& maxConnections,
		const std::vector<types::UpdateType>& filterUpdates) :
	Bot(token,url,certificate,maxConnections,filterUpdates)
{}

void tgbot::LongPollBot::start() {
	CURL *fetchConnection = utils::http::curlEasyInit();

	curl_easy_setopt(fetchConnection, CURLOPT_TCP_KEEPALIVE, 1L);
	curl_easy_setopt(fetchConnection, CURLOPT_TCP_KEEPIDLE, 60);
	
	std::vector<types::Update> updates;
	while (true) {
		if(getUpdates(fetchConnection,updates)) {
			makeCallback(updates);
			updates.clear();
		}
	}
}

void tgbot::WebhookBot::start() {

}

void tgbot::Bot::makeCallback(const std::vector<types::Update> &updates) const {
	std::thread tmpHolder;
	for (auto const &update : updates) {
		switch (update.updateType) {
			case types::UpdateType::MESSAGE:
				if (messageCallback)
					tmpHolder = std::thread(messageCallback, std::move(*update.message), *this);

				break;
			case types::UpdateType::EDITED_MESSAGE:
				if (editedMessageCallback)
					tmpHolder = std::thread(editedMessageCallback, std::move(*update.editedMessage), *this);

				break;
			case types::UpdateType::CALLBACK_QUERY:
				if (callbackQueryCallback)
					tmpHolder = std::thread(callbackQueryCallback, std::move(*update.callbackQuery), *this);

				break;
			case types::UpdateType::CHOSEN_INLINE_RESULT:
				if (chosenInlineResultCallback)
					tmpHolder = std::thread(chosenInlineResultCallback, std::move(*update.chosenInlineResult), *this);

				break;
			case types::UpdateType::EDITED_CHANNEL_POST:
				if (editedChannelPostCallback)
					tmpHolder = std::thread(editedChannelPostCallback, std::move(*update.editedChannelPost), *this);

				break;
			case types::UpdateType::INLINE_QUERY:
				if (inlineQueryCallback) 
					tmpHolder = std::thread(inlineQueryCallback, std::move(*update.inlineQuery), *this);

				break;
			case types::UpdateType::PRE_CHECKOUT_QUERY:
				if (preCheckoutQueryCallback) 
					tmpHolder = std::thread(preCheckoutQueryCallback, std::move(*update.preCheckoutQuery), *this);

				break;
			case types::UpdateType::SHIPPING_QUERY:
				if (shippingQueryCallback)
					tmpHolder = std::thread(shippingQueryCallback, std::move(*update.shippingQuery), *this);

				break;
			case types::UpdateType::CHANNEL_POST:
				if (channelPostCallback)
					tmpHolder = std::thread(channelPostCallback, std::move(*update.channelPost), *this);

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
