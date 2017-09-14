#ifndef TGBOT_BOT_H
#define TGBOT_BOT_H

#include "methods/api.h"
#include "register_callback.h"

namespace tgbot {
	class Bot : public methods::Api, public RegisterCallback {
		public:
			/*!
			 * @brief Bot class constructor
			 * @param token : Bot token
			 * @param filterUpdates : accept only certain kinds of UpdateType (Default everything)
			 * @param limit : how many updates per-time? (Default 100)
			 * @param timeout : long poll should stop after N seconds, if not receiving updates (Default 60)
			 */
			Bot(const std::string& token, 
				const std::vector<types::UpdateType>& filterUpdates = {},
				const int& limit = 100,
				const int& timeout = 60);

			/*!
			 * @brief Set a new update (getUpdates) filter
			 * @param newFilter : new filter to be set
			 */
			void setUpdatesFilter(const std::vector<types::UpdateType>& newFilter);

			/*!
			 * @brief Start long polling
			 */
			void start() const;

		private:
			std::vector<types::UpdateType> updatesFilter;
	};
}

#endif
