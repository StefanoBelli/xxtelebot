#ifndef TGBOT_BOT_H
#define TGBOT_BOT_H

#include <exception>
#include <utility>

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

  virtual const char *what() const noexcept { return __what.c_str(); }

private:
  const std::string __what;
};

/*!
 * @brief Basic Bot interface
 */
class Bot : public methods::Api, public RegisterCallback {
public:
  virtual void start() {}

protected:
  template <typename... TyArgs>
  Bot(TyArgs &&... many) : Api(std::forward<TyArgs>(many)...) {}

  void makeCallback(const std::vector<types::Update> &updates) const;
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

  /*!
   * @brief Start listening for events on target URL
   */
  void start() override;
};
} // namespace tgbot

#endif
