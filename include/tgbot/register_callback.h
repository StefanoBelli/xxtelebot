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
	template <typename __TypeUpdate>
		using __T_UpdateCallback =
    	std::function<void(const __TypeUpdate, const methods::Api &)>;

	/*!
 	 * @brief registers and holds callbacks for each type of update
 	 */
	class RegisterCallback {
		public:
  			using MessageCallback = __T_UpdateCallback<types::Message>;
  			using InlineQueryCallback = __T_UpdateCallback<types::InlineQuery>;
  			using ChosenInlineResultCallback = __T_UpdateCallback<types::ChosenInlineResult>;
  			using CallbackQueryCallback = __T_UpdateCallback<types::CallbackQuery>;
  			using ShippingQueryCallback = __T_UpdateCallback<types::ShippingQuery>;
  			using PreCheckoutQueryCallback = __T_UpdateCallback<types::PreCheckoutQuery>;

		protected:
  			using __Command_Tuple = std::tuple<const char *,       											// string to be matched
  				  std::function<bool(const std::string&, const char*)>,    		// matcher function
                  const char,         											// separator
                  std::function<void(const types::Message, const methods::Api&, 
                          const std::vector<std::string>)>>; 						// user callback
  			RegisterCallback() = default;
  			MessageCallback messageCallback;
  			InlineQueryCallback inlineQueryCallback;
  			ChosenInlineResultCallback chosenInlineResultCallback;
  			CallbackQueryCallback callbackQueryCallback;
  			ShippingQueryCallback shippingQueryCallback;
  			PreCheckoutQueryCallback preCheckoutQueryCallback;
  			MessageCallback editedMessageCallback;
  			MessageCallback editedChannelPostCallback;
  			MessageCallback channelPostCallback;
  			std::vector<__Command_Tuple> commandCallback;

		public:

  			/*!
   			 * @brief C-style function pointer callback overload, associate with command
   			 * @param matcherCallback, the function responsible for giving result about the matching (see whenStarts() and whenContains())
   			 * @param callback, function that gets called when string matches with given instructions
   			 * @param matchWord, command string (e.g. /say hello : matchWord = "/say ")
   			 * @param sep, separator. (space character by default)
   			 */
  			inline void callback(bool (&matcherCallback)(const std::string&, const char*),
  		  			void (&callback)(const types::Message, const methods::Api &, const std::vector<std::string>),
                    const char *matchWord, const char sep = ' ') {

    			commandCallback.emplace_back(matchWord, matcherCallback, sep, callback);
  			}

  			/*!
   			 * @brief std::function wrapper callback overload, associate with command (ability to use lambdas
   			 * @param matcherCallback, the function responsible for giving result about the matching (see whenStarts() and whenContains())
   			 * @param callback, function that gets called when string matches with given instructions
   			 * @param matchWord, command string (e.g. /say hello : matchWord = "/say ")
   			 * @param sep, separator. (space character by default)
   			 */
  			inline void callback(std::function<bool(const std::string&, const char*)> matcherCallback,
  		  			std::function<void(const types::Message, const methods::Api &, const std::vector<std::string>)> callback,
                    const char *matchWord, const char sep = ' ') {

    			commandCallback.emplace_back(matchWord, matcherCallback, sep, callback);
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
   			 * @brief Message update callback
   			 * @param callback
   			 */
  			inline void callback(MessageCallback callback) {
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
   			 * @brief Inline query update callback
   			 * @param callback
   			 */
  			inline void callback(InlineQueryCallback callback) {
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

  			inline void callback(ChosenInlineResultCallback callback) {
  				/*!
   				 * @brief Chosen inline result update callback
   				 * @param callback
   				 */
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
   			 * @brief Callback query update callback
   			 * @param callback
   			 */
  			inline void callback(CallbackQueryCallback callback) {
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
   			 * @brief Shipping query update callback
   			 * @param callback
   			 */
  			inline void callback(ShippingQueryCallback callback) {
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
   			 * @brief Pre checkout query update callback
   			 * @param callback
   			 */
  			inline void callback(PreCheckoutQueryCallback callback) {
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

  			/*!
   			 * @brief Multiple-options update callback
   			 * @param callback
   			 * @param which : accepted values: EDITED_MESSAGE, EDITED_CHANNEL_POST,
   			 * CHANNEL_POST. Others ignored
   			 */
  			inline void callback(MessageCallback callback, 
		  			const types::UpdateType updateType) {
    			switch (updateType)
				{
					case types::UpdateType::EDITED_MESSAGE:
						editedMessageCallback = callback;
						break;
					case types::UpdateType::EDITED_CHANNEL_POST:
						editedChannelPostCallback = callback;
						break;
					case types::UpdateType::CHANNEL_POST:
						channelPostCallback = callback;
						break;
					default:
						break;
				}
  			}
	};

} // namespace tgbot

#endif
