#ifndef TGBOT_BOT_H
#define TGBOT_BOT_H

#include <exception>
#include <utility>
#include <curl/curl.h>

#include "register_callback.h"

/*!
 * @brief Main tgbot namespace
 */
namespace tgbot {

/*!
 * @brief Exception raised when Bot API reports some kind of error
 */
class TelegramException : public std::exception {
public:
  explicit TelegramException(const std::string &_what) : __what(_what) {}
  const char *what() const noexcept override { return __what.c_str(); }
private:
  const std::string __what;
};

/*!
 * @brief Basic Bot interface
 */
class Bot : public methods::Api, public RegisterCallback {
public:
  Bot(const Bot&) = default;
  Bot(Bot&&) = default;
  Bot& operator=(const Bot&) = default;
  Bot& operator=(Bot&&) = default;
  ~Bot() = default;
  
  virtual void start() {}

  /*!
   * @brief log each update? (received update - ${UPDATE_ID}) (false by default)
   * @param t: true - yes / false - no
   */
  void notifyEachUpdate(bool t);
protected:
  template <typename... TyArgs>
  explicit Bot(TyArgs &&... many) : 
  	  Api(std::forward<TyArgs>(many)...) { curl_global_init(CURL_GLOBAL_SSL); }

  void makeCallback(const std::vector<types::Update> &updates) const;

private:
  bool __notifyEachUpdate { false };
};

/*!
 * @brief Long polling bot, (see LongPollBot::start() function)
 */
class LongPollBot : public Bot {
public:
  /*!
   * @brief Bot class constructor
   * @param token : Bot token
   * @param filterUpdates : accept only certain kinds of UpdateType (Default
   * everything)
   * @param limit : how many updates per-time? (Default 100)
   * @param timeout : long poll should stop after N seconds, if not receiving
   * updates (Default 60)
   */
  LongPollBot(const std::string &token,
              const std::vector<types::UpdateType> &filterUpdates = {},
              const int &limit = 100, const int &timeout = 60);

  ~LongPollBot() = default;
  LongPollBot(const LongPollBot&) = delete;
  LongPollBot(LongPollBot&&) = delete;
  LongPollBot& operator=(const LongPollBot&) = delete;
  LongPollBot& operator=(LongPollBot&&) = delete;

  /*!
   * @brief start long polling
   */
  void start() override;
};

/*!
 * @brief Webhook bot (see WebhookBot::start() function)
 */
class WebhookBot : public Bot {
public:
  /*!
   * @brief Construct and nothing more. Call setWebhook() before start() :)
   * @param token : Bot token
   */
  WebhookBot(const std::string &token);

  /*!
   * @brief Call setWebhook() after field initialization, if something wrong,
   * then throw TelegramException. No self-signed certificate upload
   * @param token : Bot token
   * @param url : Where would you like to get updates?
   * @param maxConnections : number of maximum connections
   * @param filterUpdates : allowed updates
   */
  WebhookBot(const std::string &token, const std::string &url,
             const int &maxConnections = 40,
             const std::vector<types::UpdateType> &filterUpdates = {});

  /*!
   * @brief Call setWebhook() after field initialization, if something wrong,
   * then throw TelegramException. *UPLOADS SELF-SIGNED CERTIFICATE*
   * @param certificate : local path to certificate
   * @param token : Bot token
   * @param url : Where would you like to get updates?
   * @param maxConnections : number of maximum connections
   * @param filterUpdates : allowed updates
   */
  WebhookBot(const std::string &token, const std::string &url,
             const std::string &certificate, const int &maxConnections = 40,
             const std::vector<types::UpdateType> &filterUpdates = {});
  
  ~WebhookBot() = default;
  WebhookBot(const WebhookBot&) = delete;
  WebhookBot(WebhookBot&&) = delete;
  WebhookBot& operator=(const WebhookBot&) = delete;
  WebhookBot& operator=(WebhookBot&&) = delete;

  /*!
   * @brief Start listening for events on target URL
   */
  void start() override;
};

} // namespace tgbot

#endif
