#ifndef TGBOT_REGISTER_CB_H
#define TGBOT_REGISTER_CB_H

#include <functional>

namespace tgbot {
	class Bot;
	namespace types {
		struct Message;
		struct InlineQuery;
		struct ChosenInlineResult;
		struct CallbackQuery;
		struct ShippingQuery;
		struct PreCheckoutQuery;
		struct Update;
		enum class UpdateType;
	}

	/*!
	 * @brief refer to RegisterCallback::callback() function (overloads)
	 */
	template <typename TypeUpdate>
		using UpdateCallback = std::function<void(const TypeUpdate, const Bot&)>;

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

		public:
            /*!
             * @brief Message update callback
             * @param callback
             */
			inline void callback(void(&callback)(const types::Message,const Bot&)) {
				messageCallback = callback;
			}

            /*!
             * @brief Inline query update callback
             * @param callback
             */
			inline void callback(void(&callback)(const types::InlineQuery, const Bot&)) {
				inlineQueryCallback = callback;
			}

            /*!
             * @brief Chosen inline result update callback
             * @param callback
             */
			inline void callback(void(&callback)(const types::ChosenInlineResult, const Bot&)) {
				chosenInlineResultCallback = callback;
			}

            /*!
             * @brief Callback query update callback
             * @param callback
             */
			inline void callback(void(&callback)(const types::CallbackQuery, const Bot&)) {
				callbackQueryCallback = callback;
			}

            /*!
             * @brief Shipping query update callback
             * @param callback
             */
			inline void callback(void(&callback)(const types::ShippingQuery, const Bot&)) {
				shippingQueryCallback = callback;
			}

            /*!
             * @brief Pre checkout query update callback
             * @param callback
             */
			inline void callback(void(&callback)(const types::PreCheckoutQuery, const Bot&)) {
				preCheckoutQueryCallback = callback;
			}

            /*!
            * @brief Multiple-options update callback
            * @param callback
            * @param which : accepted values: EDITED_MESSAGE, EDITED_CHANNEL_POST, CHANNEL_POST.
            * Others ignored
            */
			inline void callback(void(&callback)(const types::Message, const Bot&),
					const types::UpdateType& which) {
				if(which == types::UpdateType::EDITED_MESSAGE)
					editedMessageCallback = callback;
				else if(which == types::UpdateType::EDITED_CHANNEL_POST)
					editedChannelPostCallback = callback;
				else if(which == types::UpdateType::CHANNEL_POST)
					channelPostCallback = callback;
			}
	};
}

#endif
