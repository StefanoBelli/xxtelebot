#ifndef TGBOT_METHODS_API_H
#define TGBOT_METHODS_API_H

#include "types.h"

namespace tgbot {

	namespace methods {

		namespace api_types = ::tgbot::types;

		class Api {
		public:
			explicit Api(const std::string& token);
			api_types::Message sendMessage(const std::string& chatId, const std::string& text,
					const types::ParseMode& = types::ParseMode::DEFAULT,
					const bool& disableWebPagePreview = false,
					const bool& disableNotification = false,
					const int& replyToMessageId = -1,
					const std::string& replyMarkup = "");
			api_types::Message forwardMessage(const std::string& chatId, const std::string& fromChatId,
					const int& messageId, 
					const bool& disableNotification = false);
			api_types::Message sendPhoto(const std::string& chatId, const std::string& photo,
					const types::FileSource = types::FileSource::EXTERNAL,
					const std::string& caption = "", 
					const bool& disableNotification = false,
					const int& replyToMessageId = -1,
					const std::string& replyMarkup = "");
			api_types::Message sendAudio(const std::string& chatId, const std::string& audio,
					const types::FileSource = types::FileSource::EXTERNAL,
					const std::string& caption = "",
					const int& duration = -1,
					const std::string& performer = "",
					const std::string& title = "",
					const bool& disableNotification = false,
					const int& replyToMessageId = -1,
					const std::string& replyMarkup = "");
			api_types::Message sendDocument(const std::string& chatId, const std::string& document,
					const types::FileSource = types::FileSource::EXTERNAL,
					const std::string& caption = "", 
					const bool& disableNotification = false,
					const int& replyToMessageId = -1,
					const std::string& replyMarkup = "");
			api_types::Message sendVideo(const std::string& chatId, const std::string& video,
					const types::FileSource = types::FileSource::EXTERNAL,
					const int& duration = -1, 
					const int& width = -1,
					const int& height = -1,
					const std::string& caption = "",
					const bool& disableNotification = false,
					const int& replyToMessageId = -1,
					const std::string& replyMarkup = "");
			api_types::Message sendVoice(const std::string& chatId, const std::string& voice,
					const types::FileSource = types::FileSource::EXTERNAL,
					const std::string& caption = "", 
					const int& duration = -1,
					const bool& disableNotification = false,
					const int& replyToMessageId = -1,
					const std::string& replyMarkup = "");
			api_types::Message sendVideoNote(const std::string& chatId, const std::string& voice,
					const types::FileSource = types::FileSource::EXTERNAL,
					const std::string& caption = "", 
					const int& duration = -1,
					const bool& disableNotification = false,
					const int& replyToMessageId = -1,
					const std::string& replyMarkup = "");
			api_types::Message sendLocation(const std::string& chatId, const double& latitude,
					const double& longitude, 
					const bool& disableNotification = false,
					const int& replyToMessageId = -1,
					const std::string& replyMarkup = "");
			api_types::Message sendVenue(const std::string& chatId, const double& latitude,
					const double& longitude, 
					const std::string& title,
					const std::string& address,
					const std::string& foursquareId = "",
					const bool& disableNotification = false,
					const int& replyToMessageId = -1,
					const std::string& replyMarkup = "");
			api_types::Message sendContact(const std::string& chatId, const std::string& phoneNumber,
					const std::string& firstName,
					const std::string& lastName = "",
					const bool& disableNotification = false,
					const int& replyToMessageId = -1,
					const std::string& replyMarkup = "");
			bool sendChatAction(const std::string& chatId, const types::ChatAction& action);
			bool kickChatMember(const std::string& chatId, const int& userId, 
					const int& untilDate = -1);
			bool unbanChatMember(const std::string& chatId, const int& userId);
			bool restrictChatMember(const std::string& chatId, const int& userId,
					const types::ChatMemberRestrict& permissions,
					const int& untilDate = -1);
			bool promoteChatMember(const std::string& chatId, const int& userId,
					const types::ChatMemberPromote& permissions);
			std::string exportChatInviteLink(const std::string& chatId);
			bool setChatPhoto(const std::string& chatId,const std::string& filename);
			bool deleteChatPhoto(const std::string& chatId);
			bool setChatTitle(const std::string& chatId, const std::string& title);
			bool setChatDescription(const std::string& chatId, const std::string& description);
			bool pinChatMessage(const std::string& chatId, const std::string& messageId, 
					const bool& disableNotifiation = false);
			bool unpinChatMessage(const std::string& chatId);
			bool leaveChat(const std::string& chatId);
			bool answerCallbackQuery(const std::string& callbackQueryId, const std::string& text = "",
					const bool& showAlert = false, 
					const std::string& url = "",
					const int& cacheTime = 0);
			bool answerInlineQuery(const std::string& inlineQueryId, 
					const std::vector<types::InlineQueryResult>& result,
					const int& cacheTime = 0,
					const bool& isPersonal = true,
					const std::string& nextOffset = "",
					const std::string& switchPmText = "",
					const std::string& switchPmParameter = "");
			std::vector<api_types::Update> getUpdates(const long long& offset, const int limit = 100,
					const int timeout = 60);
			std::vector<api_types::Update> getUpdates(const long long& offset, 
					const std::vector<api_types::UpdateType> allowedUpdates,
					const int limit = 100,
					const int timeout = 60);
			api_types::User getMe();
			api_types::File getFile(const std::string& fileId);
			api_types::Chat getChat(const std::string& chatId);
			std::vector<api_types::ChatMember> getChatAdministrators(const std::string& chatId);
			unsigned getChatMembersCount(const std::string& chatId);
			api_types::ChatMember getChatMember(const std::string& chatId, const int& userId);
			api_types::UserProfilePhotos getUserProfilePhotos(const int& userId, const unsigned& offset = 0,
																		 const unsigned& limit = 100);

		private:
			const std::string token;
			long long currentOffset;
		};

	} //methods

} //tgbot

#endif 
