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
	 * @brief refer to RegisterCallback::callback function
	 */
	template <typename TypeUpdate>
		using UpdateCallback = std::function<void(const TypeUpdate&, const Bot&)>;

	/*!
	 * @brief refer to RegisterCallback::callback function
	 */
	using AnyUpdateCallback = std::function<void(const types::Update&, const Bot&)>;

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

			AnyUpdateCallback anyUpdateCallback;

		public:
			/*!
			 * @brief register a callback, template specializations exist,
			 * this one will do nothing
			 * @tparam Ty : update type, see namespace tgbot::types
			 * @param unknownCallback
			 */
			template <typename Ty>
				inline void callback(const Ty& unknownCallback) {}

			/*!
			 * @brief register a callback, must be used
			 * for "edited message" or "edited channel post"
			 * @param message
			 * @param which : see types::UpdateType
			 */
			inline void callback(const UpdateCallback<types::Message>& message,
					const types::UpdateType& which);
	};

	template<>
		inline void RegisterCallback::callback<AnyUpdateCallback>(const AnyUpdateCallback& callback) {
			anyUpdateCallback = callback;
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

	inline void RegisterCallback::callback(const UpdateCallback<types::Message>& callback,
			const types::UpdateType& which) {
		if(which == types::UpdateType::EDITED_MESSAGE)
			editedMessageCallback = callback;
		else if(which == types::UpdateType::EDITED_CHANNEL_POST)
			editedChannelPostCallback = callback;
	}

}

#endif
