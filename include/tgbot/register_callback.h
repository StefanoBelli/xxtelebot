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
	 * @brief refer to callback function
	 */
	template <typename TypeUpdate>
		using UpdateCallback = std::function<void(const TypeUpdate, const Bot&)>;

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
			inline void callback(const void(*callback)(const types::Message,const Bot&)) {
				messageCallback = callback;
			}


			inline void callback(const void(*callback)(const types::InlineQuery, const Bot&)) {
				inlineQueryCallback = callback;
			}


			inline void callback(const void(*callback)(const types::ChoaenInlineResult, const Bot&)) {
				chosenInlineResultCallback = callback;
			}


			inline void callback(const void(*callback)(const types::CallbackQuery, const Bot&)) {
				callbackQueryCallback = callback;
			}


			inline void callback(const void(*callback)(const types::ShippingQuery, const Bot&)) {
				shippingQueryCallback = callback;
			}


			inline void callback(const void(*callback)(const types::PreCheckoutQuery, const Bot&)) {
				preCheckoutQueryCallback = callback;
			}

			inline void callback(const void(*callback)(const types::Message),
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
