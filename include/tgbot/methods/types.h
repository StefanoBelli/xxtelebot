#ifndef TGBOT_METHODS_TYPES_H
#define TGBOT_METHODS_TYPES_H 

#include "../types.h"

namespace tgbot {

	namespace methods {

		namespace types {

			template <typename _Ty_Elem>
				using Ptr = std::unique_ptr<_Ty_Elem>;
			using InlineKeyboardMarkup = ::tgbot::types::InlineKeyboardMarkup;

			struct InputMessageContent;

			enum class ParseMode {
				DEFAULT,
				MARKDOWN,
				HTML
			};

			enum class ChatAction {
				TYPING,
				UPLOAD_PHOTO,
				RECORD_VIDEO,
				UPLOAD_VIDEO,
				RECORD_AUDIO,
				UPLOAD_AUDIO,
				UPLOAD_DOCUMENT,
				FIND_LOCATION,
				RECORD_VIDEO_NOTE,
				UPLOAD_VIDEO_NOTE
			};

			enum class FileSource {
				EXTERNAL,
				LOCAL_UPLOAD
			};

			struct ChatMemberRestrict {
				public:
					bool canSendMessages : 1;
					bool canSendMediaMessages : 1;
					bool canSendOtherMessages : 1;
					bool canAddWebPagePreviews : 1;
			};

			struct ChatMemberPromote {
				public:
					bool canPostMessages : 1;
					bool canChangeInfo : 1;
					bool canEditMessages : 1;
					bool canDeleteMessages : 1;
					bool canInviteUsers : 1;
					bool canRestrictMembers : 1;
					bool canPinMessages : 1;
					bool canPromoteMembers : 1;
			};

			struct InlineQueryResult {
				public:
					virtual std::string toString() = 0;
			};

			struct InlineQueryResultAudio : public InlineQueryResult {
				public:
					std::string toString() override;
					std::string type;
					std::string id;
					std::string audioUrl;
					std::string title;
					Ptr<std::string> caption;
					Ptr<std::string> performer;
					Ptr<InlineKeyboardMarkup> replyMarkup;
					Ptr<InputMessageContent> inputMessageContent;
					int audioDuration;
			};

			struct InlineQueryResultArticle : public InlineQueryResult {
				public:
					std::string toString() override;
					std::string type;
					std::string id;
					std::string title;
					Ptr<InputMessageContent> inputMessageContent;
					Ptr<InlineKeyboardMarkup> replyMarkup;
					Ptr<std::string> url;
					Ptr<std::string> description;
					Ptr<std::string> thumbUrl;
					int thumbWidth;
					int thumbHeight;
					bool hideUrl : 1;
			};

			struct InlineQueryResultContact : public InlineQueryResult {
				public:
					std::string toString() override;
					std::string type;
					std::string id;
					std::string phoneNumber;
					std::string firstName;
					Ptr<std::string> lastName;
					Ptr<std::string> thumbUrl;
					Ptr<InlineKeyboardMarkup> replyMarkup;
					Ptr<InputMessageContent> inputMessageContent;
					int thumbWidth;
					int thumbHeight;
			};

			struct InlineQueryResultGame : public InlineQueryResult {
				public:
					std::string toString() override;
					std::string type;
					std::string id;
					std::string gameShortName;
					Ptr<InlineKeyboardMarkup> replyMarkup;
			};

			struct InlineQueryResultDocument : public InlineQueryResult {
				public:
					std::string toString() override;
					std::string type;
					std::string id;
					std::string title;
					std::string documentUrl;
					std::string mimeType;
					Ptr<std::string> caption;
					Ptr<std::string> description;
					Ptr<InlineKeyboardMarkup> replyMarkup;
					Ptr<InputMessageContent> inputMessageContent;
					Ptr<std::string> thumbUrl;
					int thumbWidth;
					int thumbHeight;
			};

			struct InlineQueryResultGif : public InlineQueryResult {
				public:
					std::string toString() override;
					std::string type;
					std::string id;
					std::string gifUrl;
					std::string thumbUrl;
					Ptr<std::string> title;
					Ptr<std::string> caption;
					Ptr<InlineKeyboardMarkup> replyMarkup;
					Ptr<InputMessageContent> inputMessageContent;
					int gifWidth;
					int gifHeight;
					int gifDuration;
			};

			struct InlineQueryResultLocation : public InlineQueryResult {
				public:
					std::string toString() override;
					std::string type;
					std::string id;
					std::string title;
					Ptr<InlineKeyboardMarkup> replyMarkup;
					Ptr<InputMessageContent> inputMessageContent;
					Ptr<std::string> thumbUrl;
					double latitude;
					double longitude;
					int thumbWidth;
					int thumbHeight;
			};

			struct InlineQueryResultMpeg4Gif : public InlineQueryResult {
				public:
					std::string toString() override;
					std::string type;
					std::string id;
					std::string mpeg4Url;
					std::string thumbUrl;
					Ptr<std::string> title;
					Ptr<std::string> caption;
					Ptr<InlineKeyboardMarkup> replyMarkup;
					Ptr<InputMessageContent> inputMessageContent;
					int mpeg4Width;
					int mpeg4Height;
					int mpeg4Duration;
			};

			struct InlineQueryResultPhoto : public InlineQueryResult {
				public:
					std::string toString() override;
					std::string type;
					std::string id;
					std::string photoUrl;
					std::string thumbUrl;
					Ptr<std::string> title;
					Ptr<std::string> description;
					Ptr<std::string> caption;
					Ptr<InputMessageContent> inputMessageContent;
					Ptr<InlineKeyboardMarkup> replyMarkup;
					int photoWidth;
					int photoHeight;
			};

			struct InlineQueryResultVenue : public InlineQueryResult {
				public:
					std::string toString() override;
					std::string type;
					std::string id;
					std::string title;
					std::string address;
					Ptr<std::string> foursquareId;
					Ptr<std::string> thumbUrl;
					Ptr<InputMessageContent> inputMessageContent;
					Ptr<InlineKeyboardMarkup> replyMarkup;
					double latitude;
					double longitude;
					int thumbWidth;
					int thumbHeight;
			};

			struct InlineQueryResultVideo : public InlineQueryResult {
				public:
					std::string toString() override;
					std::string type;
					std::string id;
					std::string videoUrl;
					std::string mimeType;
					std::string thumbUrl;
					std::string title;
					Ptr<std::string> caption;
					Ptr<std::string> description;
					Ptr<InlineKeyboardMarkup> replyMarkup;
					Ptr<InputMessageContent> inputMessageContent;
					int videoWidth;
					int videoHeight;
					int videoDuration;
			};

			struct InlineQueryResultVoice : public InlineQueryResult {
				public:
					std::string toString() override;
					std::string type;
					std::string id;
					std::string title;
					std::string voiceUrl;
					Ptr<std::string> caption;
					Ptr<InputMessageContent> inputMessageContent;
					Ptr<InlineKeyboardMarkup> replyMarkup;
					int voiceDuration;
			};

			struct InlineQueryResultCachedAudio : public InlineQueryResult {
				public:
					std::string toString() override;
					std::string type;
					std::string id;
					std::string audioFileId;
					Ptr<std::string> caption;
					Ptr<InputMessageContent> inputMessageContent;
					Ptr<InlineKeyboardMarkup> replyMarkup;
			};

			struct InlineQueryResultCachedDocument : public InlineQueryResult {
				public:
					std::string toString() override;
					std::string type;
					std::string id;
					std::string documentFileId;
					std::string title;
					Ptr<std::string> description;
					Ptr<std::string> caption;
					Ptr<InputMessageContent> inputMessageContent;
					Ptr<InlineKeyboardMarkup> replyMarkup;
			};

			struct InlineQueryResultCachedGif : public InlineQueryResult {
				public:
					std::string toString() override;
					std::string type;
					std::string id;
					std::string gifFileId;
					Ptr<std::string> title;
					Ptr<std::string> caption;
					Ptr<InputMessageContent> inputMessageContent;
					Ptr<InlineKeyboardMarkup> replyMarkup;
			};

			struct InlineQueryResultCachedMpeg4Gif : public InlineQueryResult {
				public:
					std::string toString() override;
					std::string type;
					std::string id;
					std::string mpeg4FileId;
					Ptr<std::string> title;
					Ptr<std::string> caption;
					Ptr<InputMessageContent> inputMessageContent;
					Ptr<InlineKeyboardMarkup> replyMarkup;
			};

			struct InlineQueryResultCachedPhoto : public InlineQueryResult {
				public:
					std::string toString() override;
					std::string type;
					std::string id;
					std::string photoFileId;
					Ptr<std::string> title;
					Ptr<std::string> description;
					Ptr<std::string> caption;
					Ptr<InputMessageContent> inputMessageContent;
					Ptr<InlineKeyboardMarkup> replyMarkup;
			};

			struct InlineQueryResultCachedSticker : public InlineQueryResult {
				public:
					std::string toString() override;
					std::string type;
					std::string id;
					std::string stickerFileId;
					Ptr<InputMessageContent> inputMessageContent;
					Ptr<InlineKeyboardMarkup> replyMarkup;
			};

			struct InlineQueryResultCachedVideo : public InlineQueryResult {
				public:
					std::string toString() override;
					std::string type;
					std::string id;
					std::string title;
					std::string videoFileId;
					Ptr<std::string> description;
					Ptr<std::string> caption;
					Ptr<InputMessageContent> inputMessageContent;
					Ptr<InlineKeyboardMarkup> replyMarkup;
			};

			struct InlineQueryResultCachedVoice : public InlineQueryResult {
				public:
					std::string toString() override;
					std::string type;
					std::string id;
					std::string title;
					std::string voiceFileId;
					Ptr<std::string> caption;
					Ptr<InputMessageContent> inputMessageContent;
					Ptr<InlineKeyboardMarkup> replyMarkup;
			};

			//
			//InputMessageContent
			//
			struct InputMessageContent {
				public:
					virtual std::string toString() = 0;
			};

			struct InputTextMessageContent : public InputMessageContent {
				public:
					std::string toString() override;
					std::string messageText;
					ParseMode parseMode;
					bool disableWebPagePreview : 1;
			};

			struct InputLocationMessageContent : public InputMessageContent {
				public:
					std::string toString() override;
					double latitude;
					double longitude;
			};

			struct InputContactMessageContent : public InputMessageContent {
				public:
					std::string toString() override;
					std::string phoneNumber;
					std::string firstName;
					Ptr<std::string> lastName;
			};

			struct InputVenueMessageContent : public InputMessageContent {
				public:
					std::string toString() override;
					std::string title;
					std::string address;
					Ptr<std::string> foursquareId;
					double latitude;
					double longitude;
			};

		} //types

	} //methods

} //tgbot

#endif
