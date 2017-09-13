#ifndef TGBOT_TYPES_H
#define TGBOT_TYPES_H

#include <string>
#include <vector>
#include <memory>
#include "utils/matrix.h"

namespace tgbot {
	/*!
	 * @brief API-interacting types
	 */
	namespace types {

		/*!
		 * @typedef Ptr, a unique smart pointer alias
		 */
		template <typename _Ty>
			using Ptr = std::unique_ptr<_Ty>;

		struct Message; //forward declaration

		enum class UpdateType {
			MESSAGE,
			EDITED_MESSAGE,
			EDITED_CHANNEL_POST,
			INLINE_QUERY,
			CHOSEN_INLINE_RESULT,
			CALLBACK_QUERY,
			SHIPPING_QUERY,
			PRE_CHECKOUT_QUERY
		};

		struct User {
			public:
				explicit User(const std::string& encoded);
				std::string firstName;
				Ptr<std::string> lastName;
				Ptr<std::string> username;
				Ptr<std::string> languageCode;
				int id;
				bool isBot : 1;
		};

		struct ChatPhoto {
			public:
				explicit ChatPhoto(const std::string& encoded);
				std::string smallFileId;
				std::string bigFileId;
		};

		struct MessageEntity {
			public:
				explicit MessageEntity(const std::string& encoded);
				std::string type;
				Ptr<User> user;
				Ptr<std::string> url;
				int offset;
				int length;
		};

		struct Audio {
			public:
				explicit Audio(const std::string& encoded);
				std::string fileId;
				Ptr<std::string> performer;
				Ptr<std::string> title;
				Ptr<std::string> mimeType;
				int fileSize;
				int duration;
		};

		struct PhotoSize {
			public:
				explicit PhotoSize(const std::string& encoded);
				std::string fileId;
				int fileSize;
				int width;
				int height;
		};

		struct Document {
			public:
				explicit Document(const std::string& encoded);
				std::string fileId;
				Ptr<PhotoSize> thumb;
				Ptr<std::string> fileName;
				Ptr<std::string> mimeType;
				int fileSize;
		};

		struct Voice {
			public:
				explicit Voice(const std::string& encoded);
				std::string fileId;
				Ptr<std::string> mimeType;
				int fileSize;
				int duration;
		};

		struct Contact {
			public:
				explicit Contact(const std::string& encoded);
				std::string phoneNumber;
				std::string firstName;
				std::string lastName;
				int userId;
		};

		struct Location {
			public:
				explicit Location(const std::string& encoded);
				std::string longitude;
				std::string latitude;
		};

		struct Animation {
			public:
				explicit Animation(const std::string& encoded);
				PhotoSize thumb;
				std::string fileId;
				std::string fileName;
				std::string mimeType;
				int fileSize;
		};

		struct Venue {
			public:
				explicit Venue(const std::string& encoded);
				Ptr<std::string> fourSquareId;
				Location location;
				std::string title;
				std::string address;
		};

		struct VideoNote {
			public:
				explicit VideoNote(const std::string& encoded);
				std::string fileId;
				Ptr<PhotoSize> thumb;
				int fileSize;
				int length;
				int duration;
		};

		struct MaskPosition {
			public:
				explicit MaskPosition(const std::string& encoded);
				std::string point;
				double xShift;
				double yShift;
				double scale;
		};

		struct Sticker {
			public:
				explicit Sticker(const std::string& encoded);
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
			public:
				explicit Video(const std::string& encoded);
				std::string fileId;
				Ptr<PhotoSize> thumb;
				Ptr<std::string> mimeType;
				int fileSize;
				int width;
				int height;
				int duration;
		};

		struct Invoice {
			public:
				explicit Invoice(const std::string& encoded);
				std::string title;
				std::string description;
				std::string startParameter;
				std::string currency;
				int totalAmount;
		};

		struct ShippingAddress {
			public:
				explicit ShippingAddress(const std::string& encoded);
				std::string countryCode;
				std::string state;
				std::string city;
				std::string streetLineOne;
				std::string streetLineTwo;
				std::string postCode;
		};

		struct OrderInfo {
			public:
				explicit OrderInfo(const std::string& encoded);
				Ptr<ShippingAddress> shippingAddress;
				Ptr<std::string> name;
				Ptr<std::string> phoneNumber;
				Ptr<std::string> email;
		};

		struct SuccessfulPayment {
			public:
				explicit SuccessfulPayment(const std::string& encoded);
				std::string currency;
				std::string invoicePayload;
				std::string telegramPaymentChargeId;
				std::string providerPaymentChargeId;
				Ptr<std::string> shippingOptionId;
				Ptr<OrderInfo> orderInfo;
				int totalAmount;
		};

		struct Game {
			public:
				explicit Game(const std::string& encoded);
				std::string title;
				std::string description;
				std::vector<PhotoSize> photo;
				Ptr<Animation> animation;
				Ptr<std::vector<MessageEntity>> textEntities;
				Ptr<std::string> text;
		};

		struct Chat {
			public:
				explicit Chat(const std::string& encoded);
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
			public:
				explicit Message(const std::string& encoded);
				Chat chat;
				Ptr<User> from;
				Ptr<User> forwardFrom;
				Ptr<Chat> forwardFromChat;
				Ptr<std::string> forwardSignature;
				Ptr<Message> replyToMessage;
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
				Ptr<Message> pinnedMessage;
				Ptr<Invoice> invoice;
				Ptr<SuccessfulPayment> successfulPayment;
				int forwardFromMessageId;
				int forwardDate;
				int editDate;
				int messageId;
				int date;
				int migrateToChatId;
				int migrateFromChatId;
				bool deleteChatPhoto : 1;
				bool groupChatCreated : 1;
				bool supergroupChatCreated : 1;
				bool channelChatCreated : 1;
		};

		struct InlineQuery {
			public:
				explicit InlineQuery(const std::string& encoded);
				User user;
				std::string id;
				std::string query;
				std::string offset;
				Ptr<Location> location;
		};

		struct ChosenInlineResult {
			public:
				explicit ChosenInlineResult(const std::string& encoded);
				User from;
				std::string resultId;
				std::string query;
				Ptr<Location> location;
				Ptr<std::string> inlineMessageId;
		};

		struct CallbackQuery {
			public:
				explicit CallbackQuery(const std::string& encoded);
				User from;
				std::string id;
				std::string chatInstance;
				Ptr<Message> message;
				Ptr<std::string> inlineMessageId;
				Ptr<std::string> data;
				Ptr<std::string> gameShortName;
		};

		struct ShippingQuery {
			public:
				explicit ShippingQuery(const std::string& encoded);
				ShippingAddress shippingAddress;
				User from;
				std::string id;
				std::string invoicePayload;
		};

		struct PreCheckoutQuery {
			public:
				explicit PreCheckoutQuery(const std::string& encoded);
				User from;
				std::string currency;
				std::string invoicPayload;
				std::string id;
				Ptr<std::string> shippingOptionId;
				Ptr<OrderInfo> orderInfo;
				int totalAmount;
		};

		struct Update {
			public:
				explicit Update(const std::string& encoded);
				Ptr<Message> message;
				Ptr<Message> editedMessage;
				Ptr<Message> channelPost;
				Ptr<Message> editedChannelPost;
				Ptr<InlineQuery> inlineQuery;
				Ptr<ChosenInlineResult> chosenInlineResult;
				Ptr<CallbackQuery> callbackQuery;
				Ptr<ShippingQuery> shippingQuery;
				Ptr<PreCheckoutQuery> preCheckoutQuery;
				UpdateType updateType;
				int updateId;
		};

		struct ResponseParameters {
			public:
				explicit ResponseParameters(const std::string& encoded);
				int migrateToChatId;
				int retryAfter;
		};

		struct ForceReply {
			public:
				explicit ForceReply(const std::string& encoded);
				bool forceReply : 1;
				bool selective : 1;
		};

		struct File {
			public:
				explicit File(const std::string& encoded);
				std::string fileId;
				int fileSize;
				Ptr<std::string> filePath;
		};

		struct UserProfilePhotos {
			public:
				explicit UserProfilePhotos(const std::string& encoded);
				utils::Matrix<PhotoSize> photos;
				int totalCount;
		};

		struct KeyboardButton {
			public:
				explicit KeyboardButton(const std::string& encoded);
				std::string text;
				bool requestContact : 1;
				bool requestLocation : 1;
		};

		struct ReplyKeyboardMarkup {
			public:
				explicit ReplyKeyboardMarkup(const std::string& encoded);
				utils::Matrix<KeyboardButton> keyboard;
				bool resizeKeyboard : 1;
				bool oneTimeKeyboard : 1;
				bool selective : 1;
		};

		struct ReplyKeyboardRemove {
			public:
				explicit ReplyKeyboardRemove(const std::string& encoded);
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
			public:
				explicit InlineKeyboardButton(const std::string& encoded);
				std::string text;
				Ptr<std::string> url;
				Ptr<std::string> callbackData;
				Ptr<std::string> switchInlineQuery;
				Ptr<std::string> switchInlineQueryCurrentChat;
				CallbackGame callbackGame;
				bool pay : 1;
		};

		struct InlineKeyboardMarkup {
			public:
				explicit InlineKeyboardMarkup(const std::string& encoded);
				utils::Matrix<InlineKeyboardButton> inlineKeyboard;
		};

		struct ChatMember {
			public:
				explicit ChatMember(const std::string& encoded);
				User user;
				std::string status;
				int untilDate;
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
	} //types

} //tgbot

#endif 
