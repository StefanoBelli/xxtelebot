#ifndef TGBOT_METHODS_TYPES_H
#define TGBOT_METHODS_TYPES_H 

#include <string>
#include <memory>

namespace tgbot {
	
	namespace methods {

		namespace types {

			template <typename _Ty_Elem>
			using Ptr = std::unique_ptr<_Ty_Elem>;

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
				bool canSendMessages : 1;
				bool canSendMediaMessages : 1;
				bool canSendOtherMessages : 1;
				bool canAddWebPagePreviews : 1;
			};

			struct ChatMemberPromote {
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
			};

			struct InlineQueryResultArticle : public InlineQueryResult {
			public:
				std::string toString() override;
			};

			struct InlineQueryResultContact : public InlineQueryResult {
			public:
				std::string toString() override;
			};

			struct InlineQueryResultGame : public InlineQueryResult {
			public:
				std::string toString() override;
			};

			struct InlineQueryResultDocument : public InlineQueryResult {
			public:
				std::string toString() override;
			};

			struct InlineQueryResultGif : public InlineQueryResult {
			public:
				std::string toString() override;
			};

			struct InlineQueryResultLocation : public InlineQueryResult {
			public:
				std::string toString() override;
			};
			
			struct InlineQueryResultMpeg4Gif : public InlineQueryResult {
			public:
				std::string toString() override;
			};
			
			struct InlineQueryResultPhoto : public InlineQueryResult {
			public:
				std::string toString() override;
			};
			
			struct InlineQueryResultVenue : public InlineQueryResult {
			public:
				std::string toString() override;
			};

			struct InlineQueryResultVideo : public InlineQueryResult {
			public:
				std::string toString() override;
			};
			
			struct InlineQueryResultVoice : public InlineQueryResult {
			public:
				std::string toString() override;
			};

			struct InlineQueryResultCachedAudio : public InlineQueryResult {
			public:
				std::string toString() override;
			};

			struct InlineQueryResultCachedDocument : public InlineQueryResult {
			public:
				std::string toString() override;
			};

			struct InlineQueryResultCachedGif : public InlineQueryResult {
			public:
				std::string toString() override;
			};
			
			struct InlineQueryResultCachedMpeg4Gif : public InlineQueryResult {
			public:
				std::string toString() override;
			};
			
			struct InlineQueryResultCachedPhoto : public InlineQueryResult {
			public:
				std::string toString() override;
			};
			
			struct InlineQueryResultCachedSticker : public InlineQueryResult {
			public:
				std::string toString() override;
			};

			struct InlineQueryResultCachedVideo : public InlineQueryResult {
			public:
				std::string toString() override;
			};
			
			struct InlineQueryResultCachedVoice : public InlineQueryResult {
			public:
				std::string toString() override;
			};

			struct InputMessageContent {
			public:
				virtual std::string toString() = 0;
			};

			struct InputTextMessageContent : public InputMessageContent {
			public:
				std::string toString() override;
				std::string messageText;
				Ptr<ParseMode> parseMode;
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
