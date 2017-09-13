#ifndef TGBOT_TYPES_H
#define TGBOT_TYPES_H

#include <string>
#include <vector>
#include <memory>
#include "matrix.h"

namespace tgbot {
	/*!
	 * @brief API-interacting types
	 */
	namespace types {

		/* !
		 * @typedef Ptr, a unique smart pointer alias
		 */
		template <typename _Ty>
		using Ptr = std::unique_ptr<_Ty>;
		
		struct Message; //forward declaration


		struct User {
			std::string firstName;
			Ptr<std::string> lastName;
			Ptr<std::string> username;
			Ptr<std::string> languageCode;
			int id;
			bool isBot : 1;
		};

		struct ChatPhoto {
			std::string smallFileId;
			std::string bigFileId;
		};

		struct MessageEntity {
			std::string type;
			Ptr<User> user;
			Ptr<std::string> url;
			int offset;
			int length;
		};

		struct Audio {
			std::string fileId;
			Ptr<std::string> performer;
			Ptr<std::string> title;
			Ptr<std::string> mimeType;
			Ptr<int> fileSize;
			int duration;
		};

		struct PhotoSize {
			std::string fileId;
			Ptr<int> fileSize;
			int width;
			int height;
		};

		struct Document {
			std::string fileId;
			Ptr<PhotoSize> thumb;
			Ptr<std::string> fileName;
			Ptr<std::string> mimeType;
			Ptr<int> fileSize;
		};

		struct Voice {
			std::string fileId;
			Ptr<std::string> mimeType;
			Ptr<int> fileSize;
			int duration;
		};

		struct Contact {
			std::string phoneNumber;
			std::string firstName;
			std::string lastName;
			int userId;
		};

		struct Location {
			std::string longitude;
			std::string latitude;
		};

		struct Animation {
			PhotoSize thumb;
			std::string fileId;
			std::string fileName;
			std::string mimeType;
			int fileSize;
		};

		struct Venue {
			Ptr<std::string> fourSquareId;
			Location location;
			std::string title;
			std::string address;
		};

		struct VideoNote {
			std::string fileId;
			Ptr<PhotoSize> thumb;
			Ptr<int> fileSize;
			int length;
			int duration;
		};

		struct MaskPosition {
			std::string point;
			double xShift;
			double yShift;
			double scale;
		};

		struct Sticker {
			MaskPosition maskPosition;
			PhotoSize thumb;
			std::string fileId;
			std::string emoji;
			std::string setName;
			int width;
			int height;
			int fileSize;
		};

		struct Video {
			std::string fileId;
			Ptr<PhotoSize> thumb;
			Ptr<std::string> mimeType;
			Ptr<int> fileSize;
			int width;
			int height;
			int duration;
		};

		struct Invoice {
			std::string title;
			std::string description;
			std::string startParameter;
			std::string currency;
			int totalAmount;
		};
		
		struct ShippingAddress {
			std::string countryCode;
			std::string state;
			std::string city;
			std::string streetLineOne;
			std::string streetLineTwo;
			std::string postCode;
		};

		struct OrderInfo {
			Ptr<ShippingAddress> shippingAddress;
			Ptr<std::string> name;
			Ptr<std::string> phoneNumber;
			Ptr<std::string> email;
		};

		struct SuccessfulPayment {
			std::string currency;
			std::string invoicePayload;
			std::string telegramPaymentChargeId;
			std::string providerPaymentChargeId;
			Ptr<std::string> shippingOptionId;
			Ptr<OrderInfo> orderInfo;
			int totalAmount;
		};

		struct Game {
			std::string title;
			std::string description;
			std::vector<PhotoSize> photo;
			Ptr<Animation> animation;
			Ptr<std::vector<MessageEntity>> textEntities;
			Ptr<std::string> text;
		};

		struct Chat {
			std::string type;
			Ptr<Message> pinnedMessage;
			Ptr<ChatPhoto> photo;
			Ptr<std::string> title;
			Ptr<std::string> username;
			Ptr<std::string> firstName;
			Ptr<std::string> lastName;
			Ptr<std::string> description;
			Ptr<std::string> inviteLink;
			int id;
			bool allMembersAreAdministrators;
		};

		struct Message {
			Chat chat;
			Ptr<User> from;
			Ptr<User> forwardFrom;
			Ptr<Chat> forwardFromChat;
			Ptr<int> forwardFromMessageId;
			Ptr<std::string> forwardSignature;
			Ptr<int> forwardDate;
			Ptr<Message> replyToMessage;
			Ptr<int> editDate;
			Ptr<std::string> authorSignature;
			Ptr<std::string> text;
			Ptr<std::vector<MessageEntity>> entities;
			Ptr<Audio> audio;
			Ptr<Document> document;
			Ptr<Game> game;
			Ptr<std::vector<PhotoSize>> photo;
			Ptr<Sticker> sticker;
			Ptr<Video> video;
			Ptr<Voice> voice;
			Ptr<VideoNote> videoNote;
			Ptr<std::string> caption;
			Ptr<Contact> contact;
			Ptr<Location> location;
			Ptr<Venue> venue;
			Ptr<std::vector<User>> newChatMembers;
			Ptr<std::vector<User>> leftChatMembers;
			Ptr<std::string> newChatTitle;
			Ptr<std::vector<PhotoSize>> newChatPhoto;
			Ptr<int> migrateToChatId;
			Ptr<int> migrateFromChatId;
			Ptr<Message> pinnedMessage;
			Ptr<Invoice> invoice;
			Ptr<SuccessfulPayment> successfulPayment;
			int messageId;
			int date;
			bool deleteChatPhoto : 1;
			bool groupChatCreated : 1;
			bool supergroupChatCreated : 1;
			bool channelChatCreated : 1;
		};

		struct InlineQuery {
			User user;
			std::string id;
			std::string query;
			std::string offset;
			Ptr<Location> location;
		};

		struct ChosenInlineResult {
			User from;
			std::string resultId;
			std::string query;
			Ptr<Location> location;
			Ptr<std::string> inlineMessageId;
		};

		struct CallbackQuery {
			User from;
			std::string id;
			std::string chatInstance;
			Ptr<Message> message;
			Ptr<std::string> inlineMessageId;
			Ptr<std::string> data;
			Ptr<std::string> gameShortName;
		};

		struct ShippingQuery {
			ShippingAddress shippingAddress;
			User from;
			std::string id;
			std::string invoicePayload;
		};

		struct PreCheckoutQuery {
			User from;
			std::string currency;
			std::string invoicPayload;
			std::string id;
			Ptr<std::string> shippingOptionId;
			Ptr<OrderInfo> orderInfo;
			int totalAmount;
		};

		struct Update {
			Ptr<Message> message;
			Ptr<Message> editedMessage;
			Ptr<Message> channelPost;
			Ptr<Message> editedChannelPost;
			Ptr<InlineQuery> inlineQuery;
			Ptr<ChosenInlineResult> chosenInlineResult;
			Ptr<CallbackQuery> callbackQuery;
			Ptr<ShippingQuery> shippingQuery;
			Ptr<PreCheckoutQuery> preCheckoutQuery;
			int updateId;
		};
		
		struct ResponseParameters {
			Ptr<int> migrateToChatId;
			Ptr<int> retryAfter;
		};

		struct ForceReply {
			bool forceReply : 1;
			bool selective : 1;
		};

		struct File {
			std::string fileId;
			Ptr<int> fileSize;
			Ptr<std::string> filePath;
		};

		struct UserProfilePhotos {
			Matrix<PhotoSize> photos;
			int totalCount;
		};

		struct KeyboardButton {
			std::string text;
			bool requestContact : 1;
			bool requestLocation : 1;
		};

		struct ReplyKeyboardMarkup {
			Matrix<KeyboardButton> keyboard;
			bool resizeKeyboard : 1;
			bool oneTimeKeyboard : 1;
			bool selective : 1;
		};

		struct ReplyKeyboardRemove {
			bool removeKeyboard : 1;
			bool selective : 1;
		};

		/*!
		 * @brief (note) according to telegram API documentation, 
		 * this is only a placeholder
		 */
		enum class CallbackGame {
			GAME_CALLBACK
		};

		struct InlineKeyboardButton {
			std::string text;
			Ptr<std::string> url;
			Ptr<std::string> callbackData;
			Ptr<std::string> switchInlineQuery;
			Ptr<std::string> switchInlineQueryCurrentChat;
			Ptr<CallbackGame> callbackGame; 
			bool pay : 1;
		};

		struct InlineKeyboardMarkup {
			Matrix<InlineKeyboardButton> inlineKeyboard;
		};

		struct ChatMember {
			User user;
			std::string status;
			Ptr<int> untilDate;
			bool canBeEdited : 1;
			bool canChangeInfo : 1;
			bool canPostMessages : 1;
			bool canEditMessages : 1;
			bool canDeleteMessages : 1;
			bool canInviteUsers : 1;
			bool canRestrictMembers : 1;
			bool canPinMessages : 1;
			bool canPromoteMembers : 1;
			bool canSendMessages : 1;
			bool canSendMediaMessages : 1;
			bool canSendOtherMessages : 1;
			bool canAddWebPagePreviews : 1;
		};
	}
}

#endif 
