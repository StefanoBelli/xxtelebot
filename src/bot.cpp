#include <sstream>
#include <thread>
#include <tgbot/bot.h>
#include <tgbot/utils/https.h>
#include <tgbot/logger.h>

using namespace tgbot;

tgbot::LongPollBot::LongPollBot(
    const std::string &token,
    const std::vector<types::UpdateType> &filterUpdates, const int &limit,
    const int &timeout)
    : Bot(token, filterUpdates, limit, timeout) {}

tgbot::WebhookBot::WebhookBot(const std::string &token) : Bot(token) {}

tgbot::WebhookBot::WebhookBot(
    const std::string &token, const std::string &url, const int &maxConnections,
    const std::vector<types::UpdateType> &filterUpdates)
    : Bot(token, url, maxConnections, filterUpdates) {}

tgbot::WebhookBot::WebhookBot(
    const std::string &token, const std::string &url,
    const std::string &certificate, const int &maxConnections,
    const std::vector<types::UpdateType> &filterUpdates)
    : Bot(token, url, certificate, maxConnections, filterUpdates) {}

void tgbot::LongPollBot::start() {
  getLogger().info("starting HTTP long poll...");
  
  CURL *fetchConnection = utils::http::curlEasyInit();

  curl_easy_setopt(fetchConnection, CURLOPT_TCP_KEEPALIVE, 1L);
  curl_easy_setopt(fetchConnection, CURLOPT_TCP_KEEPIDLE, 60);

  std::vector<types::Update> updates;
  while (true) {
    if (getUpdates(fetchConnection, updates)) {
      makeCallback(updates);
      updates.clear();
    }
  }
}

void tgbot::WebhookBot::start() {}

void tgbot::Bot::makeCallback(const std::vector<types::Update> &updates) const {
  std::thread tmpHolder;

  for (auto const &update : updates) {
  	if(__notifyEachUpdate)
  		getLogger().info("received update - " + std::to_string(update.updateId));
  	
    if (update.updateType == types::UpdateType::MESSAGE) {
      types::Message messageObject = std::move(*update.message);
      bool byCommandStart = false;

      if (commandCallback.size() && messageObject.text) {
        for (auto const &c : commandCallback) {
          if (std::get<1>(c)(*(messageObject.text), std::get<0>(c))) {
            std::vector<std::string> args;
            std::string arg;
            std::istringstream istr(*messageObject.text);

            while (getline(istr, arg, ' '))
              args.push_back(std::move(arg));

            tmpHolder = std::thread(std::get<3>(c), std::move(messageObject),
                                    *this, std::move(args));
            byCommandStart = true;
            break;
          }
        }
      }

      if (messageCallback && !byCommandStart)
        tmpHolder =
            std::thread(messageCallback, std::move(messageObject), *this);
      else if(!messageCallback)
      	getLogger().error("could not make any call to handler... Did you forgot Bot::callback() or something else?");
    }

    else if (update.updateType == types::UpdateType::EDITED_MESSAGE &&
             editedMessageCallback)
      tmpHolder = std::thread(editedMessageCallback,
                              std::move(*update.editedMessage), *this);

    else if (update.updateType == types::UpdateType::CALLBACK_QUERY &&
             callbackQueryCallback)
      tmpHolder = std::thread(callbackQueryCallback,
                              std::move(*update.callbackQuery), *this);

    else if (update.updateType == types::UpdateType::CHOSEN_INLINE_RESULT &&
             chosenInlineResultCallback)
      tmpHolder = std::thread(chosenInlineResultCallback,
                              std::move(*update.chosenInlineResult), *this);

    else if (update.updateType == types::UpdateType::EDITED_CHANNEL_POST &&
             editedChannelPostCallback)
      tmpHolder = std::thread(editedChannelPostCallback,
                              std::move(*update.editedChannelPost), *this);

    else if (update.updateType == types::UpdateType::INLINE_QUERY &&
             inlineQueryCallback)
      tmpHolder = std::thread(inlineQueryCallback,
                              std::move(*update.inlineQuery), *this);

    else if (update.updateType == types::UpdateType::PRE_CHECKOUT_QUERY &&
             preCheckoutQueryCallback)
      tmpHolder = std::thread(preCheckoutQueryCallback,
                              std::move(*update.preCheckoutQuery), *this);

    else if (update.updateType == types::UpdateType::SHIPPING_QUERY &&
             shippingQueryCallback)
      tmpHolder = std::thread(shippingQueryCallback,
                              std::move(*update.shippingQuery), *this);

    else if (update.updateType == types::UpdateType::CHANNEL_POST &&
             channelPostCallback)
      tmpHolder = std::thread(channelPostCallback,
                              std::move(*update.channelPost), *this);
    else
      getLogger().error("could not make any call to handler... Did you forgot Bot::callback() or something else?");
    
    if (tmpHolder.joinable())
      tmpHolder.detach();
  }
}

void tgbot::Bot::notifyEachUpdate(bool t) {
	__notifyEachUpdate = t;
}
