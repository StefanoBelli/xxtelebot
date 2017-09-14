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
		struct EditedMessage;
		struct EditedChannelPost;
		struct Update;
	}

	template <typename TypeUpdate>
		using UpdateCallback = std::function<void(const TypeUpdate&, const Bot&)>;
	using AnyUpdateCallback = std::function<void(const types::Update&, const Bot&)>;

	class RegisterCallback {
		protected:
			RegisterCallback() = default;
			inline void makeCallback(const types::Update& update) const {

			}

		private:
			UpdateCallback<types::Message> messageCallback;
			UpdateCallback<types::InlineQuery> inlineQueryCallback;
			UpdateCallback<types::ChosenInlineResult> chosenInlineResultCallback;
			UpdateCallback<types::CallbackQuery> callbackQueryCallback;
			UpdateCallback<types::ShippingQuery> shippingQueryCallback;
			UpdateCallback<types::PreCheckoutQuery> preCheckoutQueryCallback;
			UpdateCallback<types::EditedMessage> editedMessageCallback;
			UpdateCallback<types::EditedChannelPost> editedChannelPostCallback;

			AnyUpdateCallback anyUpdate;

		public:
			template <typename Ty>
				inline void callback(const Ty& unknownCallback) {}

	};

	template<>
		inline void RegisterCallback::callback<AnyUpdateCallback>(const AnyUpdateCallback& callback) {
			anyUpdate = callback;
		}

	template<>
		inline void RegisterCallback::callback<UpdateCallback<types::Message>>(const UpdateCallback<types::Message>& callback) {
			messageCallback = callback;
		}

	template<>
		inline void RegisterCallback::callback<UpdateCallback<types::InlineQuery>>(const UpdateCallback<types::InlineQuery>& callback) {
			inlineQueryCallback = callback;
		}

	template<>
		inline void RegisterCallback::callback<UpdateCallback<types::ChosenInlineResult>>(const UpdateCallback<types::ChosenInlineResult>& callback) {
			chosenInlineResultCallback = callback;
		}

	template<>
		inline void RegisterCallback::callback<UpdateCallback<types::CallbackQuery>>(const UpdateCallback<types::CallbackQuery>& callback) {
			callbackQueryCallback = callback;
		}

	template<>
		inline void RegisterCallback::callback<UpdateCallback<types::ShippingQuery>>(const UpdateCallback<types::ShippingQuery>& callback) {
			shippingQueryCallback = callback;
		}

	template<>
		inline void RegisterCallback::callback<UpdateCallback<types::PreCheckoutQuery>>(const UpdateCallback<types::PreCheckoutQuery>& callback) {
			preCheckoutQueryCallback = callback;
		}

	template<>
		inline void RegisterCallback::callback<UpdateCallback<types::EditedMessage>>(const UpdateCallback<types::EditedMessage>& callback) {
			editedMessageCallback = callback;
		}

	template<>
		inline void RegisterCallback::callback<UpdateCallback<types::EditedChannelPost>>(const UpdateCallback<types::EditedChannelPost>& callback) {
			editedChannelPostCallback = callback;
		}
}

#endif
