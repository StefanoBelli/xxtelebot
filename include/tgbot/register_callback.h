#ifndef TGBOT_REGISTER_CB_H
#define TGBOT_REGISTER_CB_H

#include "methods/api.h"
#include "types.h"
#include "utils/str_match.h"

#include <functional>
#include <tuple>
#include <vector>

namespace tgbot {

/*!
 * @brief refer to RegisterCallback::callback() function (overloads)
 */
template <typename TypeUpdate>
using UpdateCallback =
    std::function<void(const TypeUpdate, const methods::Api &)>;

/*!
 * @brief refer to utils::whenStarts() and utils::whenContains()
 */
using MatcherCallback = bool (&)(const std::string &, const char *);

/*!
 * @brief refer to RegisterCallback::callback() function
 */
using OnCommandCallback = void (&)(const types::Message, const methods::Api &,
                                   const std::vector<std::string>);

/*!
 * @brief internal usage
 */
using __Command_Tuple = std::tuple<const char *,       // string to be matched
                                   MatcherCallback,    // matcher function
                                   const char,         // separator
                                   OnCommandCallback>; // user callback

/*!
 * @brief registers and holds callbacks for each type of update
 */
class RegisterCallback {
protected:
  RegisterCallback() = default;
  UpdateCallback<types::Message> messageCallback;
  UpdateCallback<types::InlineQuery> inlineQueryCallback;
  UpdateCallback<types::ChosenInlineResult> chosenInlineResultCallback;
  UpdateCallback<types::CallbackQuery> callbackQueryCallback;
  UpdateCallback<types::ShippingQuery> shippingQueryCallback;
  UpdateCallback<types::PreCheckoutQuery> preCheckoutQueryCallback;
  UpdateCallback<types::Message> editedMessageCallback;
  UpdateCallback<types::Message> editedChannelPostCallback;
  UpdateCallback<types::Message> channelPostCallback;
  std::vector<__Command_Tuple> commandCallback;

public:
  inline void callback(MatcherCallback matcher, OnCommandCallback callback,
                       const char *matchWord, const char sep = ' ') {
    commandCallback.emplace_back(matchWord, matcher, sep, callback);
  }

  /*!
   * @brief Message update callback
   * @param callback
   */
  inline void callback(void (&callback)(const types::Message,
                                        const methods::Api &)) {
    messageCallback = callback;
  }

  /*!
   * @brief Inline query update callback
   * @param callback
   */
  inline void callback(void (&callback)(const types::InlineQuery,
                                        const methods::Api &)) {
    inlineQueryCallback = callback;
  }

  /*!
   * @brief Chosen inline result update callback
   * @param callback
   */
  inline void callback(void (&callback)(const types::ChosenInlineResult,
                                        const methods::Api &)) {
    chosenInlineResultCallback = callback;
  }

  /*!
   * @brief Callback query update callback
   * @param callback
   */
  inline void callback(void (&callback)(const types::CallbackQuery,
                                        const methods::Api &)) {
    callbackQueryCallback = callback;
  }

  /*!
   * @brief Shipping query update callback
   * @param callback
   */
  inline void callback(void (&callback)(const types::ShippingQuery,
                                        const methods::Api &)) {
    shippingQueryCallback = callback;
  }

  /*!
   * @brief Pre checkout query update callback
   * @param callback
   */
  inline void callback(void (&callback)(const types::PreCheckoutQuery,
                                        const methods::Api &)) {
    preCheckoutQueryCallback = callback;
  }

  /*!
   * @brief Multiple-options update callback
   * @param callback
   * @param which : accepted values: EDITED_MESSAGE, EDITED_CHANNEL_POST,
   * CHANNEL_POST. Others ignored
   */
  inline void callback(void (&callback)(const types::Message,
                                        const methods::Api &),
                       const types::UpdateType &which) {
    if (which == types::UpdateType::EDITED_MESSAGE)
      editedMessageCallback = callback;
    else if (which == types::UpdateType::EDITED_CHANNEL_POST)
      editedChannelPostCallback = callback;
    else if (which == types::UpdateType::CHANNEL_POST)
      channelPostCallback = callback;
  }
};

} // namespace tgbot

#endif
