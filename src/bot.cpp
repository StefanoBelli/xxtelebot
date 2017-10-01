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
				if (messageCallback) {
					types::Message *message{update.message.get()};
					if (message)
						tmpHolder = std::thread(messageCallback, std::move(*message), *this);
				}

				break;
			case types::UpdateType::EDITED_MESSAGE:
				if (editedMessageCallback) {
					types::Message *editedMessage
					{update.editedMessage.get()};

					if (editedMessage)
						tmpHolder = std::thread(editedMessageCallback, std::move(*editedMessage), *this);
				}

				break;
			case types::UpdateType::CALLBACK_QUERY:
				if (callbackQueryCallback) {
					types::CallbackQuery *callbackQuery
					{update.callbackQuery.get()};

					if (callbackQuery)
						tmpHolder = std::thread(callbackQueryCallback, std::move(*callbackQuery), *this);
				}

				break;
			case types::UpdateType::CHOSEN_INLINE_RESULT:
				if (chosenInlineResultCallback) {
					types::ChosenInlineResult *chosenInlineResult
					{update.chosenInlineResult.get()};

					if (chosenInlineResult)
						tmpHolder = std::thread(chosenInlineResultCallback, std::move(*chosenInlineResult), *this);
				}

				break;
			case types::UpdateType::EDITED_CHANNEL_POST:
				if (editedChannelPostCallback) {
					types::Message *editedChannelPost
					{update.editedChannelPost.get()};

					if (editedChannelPost)
						tmpHolder = std::thread(editedChannelPostCallback, std::move(*editedChannelPost), *this);
				}

				break;
			case types::UpdateType::INLINE_QUERY:
				if (inlineQueryCallback) {
					types::InlineQuery *inlineQuery
					{update.inlineQuery.get()};

					if (inlineQuery)
						tmpHolder = std::thread(inlineQueryCallback, std::move(*inlineQuery), *this);
				}

				break;
			case types::UpdateType::PRE_CHECKOUT_QUERY:
				if (preCheckoutQueryCallback) {
					types::PreCheckoutQuery *preCheckoutQuery
					{update.preCheckoutQuery.get()};

					if (preCheckoutQuery)
						tmpHolder = std::thread(preCheckoutQueryCallback, std::move(*preCheckoutQuery), *this);
				}

				break;
			case types::UpdateType::SHIPPING_QUERY:
				if (shippingQueryCallback) {
					types::ShippingQuery *shippingQuery
					{update.shippingQuery.get()};

					if (shippingQuery)
						tmpHolder = std::thread(shippingQueryCallback, std::move(*shippingQuery), *this);
				}

				break;
			case types::UpdateType::CHANNEL_POST:
				if (channelPostCallback) {
					types::Message *message
					{update.channelPost.get()};

					if (message)
						tmpHolder = std::thread(channelPostCallback, std::move(*message), *this);
				}

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
