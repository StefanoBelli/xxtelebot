#ifndef TGBOT_BOT_H
#define TGBOT_BOT_H

#include <utility>
#include <exception>
#include <iostream>

#include "types.h"
#include "methods/api.h"
#include "register_callback.h"

/*!
 * @brief Main tgbot namespace
 */
namespace tgbot {

	class TelegramException : public std::exception {
		public:
			explicit TelegramException(const char* _what);
			virtual const char* what() const noexcept;
		private:
			const char* _what;
	};

	class Bot : public methods::Api, public RegisterCallback {
		public:
			virtual void start() {}
		protected:
			template<typename ... TyArgs>
				Bot(TyArgs&& ... many) : Api(std::forward<TyArgs>(many)...) {}

			void makeCallback(const std::vector<types::Update>& updates) const;
	};

	class LongPollBot : public Bot {
		public:
			/*!
			 * @brief Bot class constructor
			 * @param token : Bot token
			 * @param filterUpdates : accept only certain kinds of UpdateType (Default everything)
			 * @param limit : how many updates per-time? (Default 100)
			 * @param timeout : long poll should stop after N seconds, if not receiving updates (Default 60)
			 */
			LongPollBot(const std::string& token,
				const std::vector<types::UpdateType>& filterUpdates = {},
				const int& limit = 100,
				const int& timeout = 60);

			void start() override;
	};

	class WebhookBot : public Bot {
		public:
			WebhookBot(const std::string& token,
					const std::string& url,
					const int& maxConnections = 40,
					const std::vector<types::UpdateType>& filterUpdates = {});
			
			WebhookBot(const std::string& token,
					const std::string& url,
					const std::string& certificate,
					const int& maxConnections = 40,
					const std::vector<types::UpdateType>& filterUpdates = {});
			
			void start() override;
	};
} //tgbot

#endif
