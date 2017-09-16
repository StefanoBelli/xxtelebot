#ifndef TGBOT_BOT_H
#define TGBOT_BOT_H

#include "types.h"
#include "methods/api.h"
#include "register_callback.h"

/*!
 * @brief Main tgbot namespace
 */
namespace tgbot {

	class Bot : public methods::Api, public RegisterCallback {
		public:
			/*!
			 * @brief Bot class constructor
			 * @param token : Bot token
			 * @param useragent : User-Agent HTTP header field
			 * @param filterUpdates : accept only certain kinds of UpdateType (Default everything)
			 * @param limit : how many updates per-time? (Default 100)
			 * @param timeout : long poll should stop after N seconds, if not receiving updates (Default 60)
			 */
			Bot(const std::string& token,
                const std::string& useragent,
				const std::vector<types::UpdateType>& filterUpdates = {},
				const int& limit = 100,
				const int& timeout = 60);

			/*!
			 * @brief Start long polling
			 */
			void start();
		
		private:
			void makeCallback(const std::vector<types::Update>& updates) const;
            const std::string ua;
	};

} //tgbot

#endif
