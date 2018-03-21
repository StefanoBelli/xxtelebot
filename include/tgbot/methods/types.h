#ifndef TGBOT_METHODS_TYPES_H
#define TGBOT_METHODS_TYPES_H

#include "../types.h"

namespace tgbot {

namespace methods {

/*!
 * @brief API Methods parameter types
 */
namespace types {

struct InputMessageContent;
struct InlineQueryResult;

constexpr char iqrTypeArticle[]   = "article";
constexpr char iqrTypeDocument[]  = "document";
constexpr char iqrTypeGif[]       = "gif";
constexpr char iqrTypeMpeg4Gif[]  = "mpeg4_gif";
constexpr char iqrTypePhoto[]     = "photo";
constexpr char iqrTypeVideo[]     = "video";
constexpr char iqrTypeAudio[]     = "audio";
constexpr char iqrTypeLocation[]  = "location";
constexpr char iqrTypeVenue[]     = "venue";
constexpr char iqrTypeContact[]   = "contact";
constexpr char iqrTypeGame[]      = "game";
constexpr char iqrTypeVoice[]     = "voice";

using InlineQueryResultsVector =
    std::vector<::tgbot::types::Ptr<InlineQueryResult>>;

using KeyboardButton = ::tgbot::types::KeyboardButton;
using CallbackGame = ::tgbot::types::CallbackGame;

/*!
 * @brief Parsing mode to be used
 */
enum class ParseMode { DEFAULT, MARKDOWN, HTML };

/*!
 * @brief What the bot is doing
 */
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

/*!
 * @brief Choose if filename should be treated as file_id
 * or uploaded via multipart
 */
enum class FileSource {
  /*!
   * @brief trait as file_id
   */
  EXTERNAL,

  /*!
   * @brief trait as local upload via multipart
   */
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

struct InlineKeyboardButton {
public:
  std::string text;
  ::tgbot::types::Ptr<std::string> url;
  ::tgbot::types::Ptr<std::string> callbackData;
  ::tgbot::types::Ptr<std::string> switchInlineQuery;
  ::tgbot::types::Ptr<std::string> switchInlineQueryCurrentChat;
  /*!
   * @brief check tgbot::types::CallbackGame for further infos
   */
  CallbackGame callbackGame;
  bool pay : 1;
};

//
// ReplyMarkup
//
struct ReplyMarkup {
public:
  // Not explicit constructor
  ReplyMarkup() = default;
  ReplyMarkup(const char *customMarkup);
  ReplyMarkup(const std::string &customMarkup);

  virtual std::string toString() const;

private:
  const std::string what;
};

struct InlineKeyboardMarkup : public ReplyMarkup {
public:
  std::string toString() const override;
  std::vector<std::vector<InlineKeyboardButton>> inlineKeyboard;
};

struct ReplyKeyboardMarkup : public ReplyMarkup {
public:
  std::string toString() const override;
  std::vector<std::vector<KeyboardButton>> keyboard;
  bool resizeKeyboard : 1;
  bool oneTimeKeyboard : 1;
  bool selective : 1;
};

struct ReplyKeyboardRemove : public ReplyMarkup {
public:
  std::string toString() const override;
  bool selective : 1;
};

struct ForceReply : public ReplyMarkup {
public:
  std::string toString() const override;
  bool selective : 1;
};

//
// InputMessageContent
//
struct InputMessageContent {
public:
  // Not explicit constructor
  InputMessageContent() = default;
  InputMessageContent(const char *customMarkup);
  InputMessageContent(const std::string &customMarkup);

  virtual std::string toString() const;

private:
  const std::string what;
};

struct InputTextMessageContent : public InputMessageContent {
public:
  std::string toString() const override;
  std::string messageText;
  ParseMode parseMode;
  bool disableWebPagePreview : 1;
};

struct InputLocationMessageContent : public InputMessageContent {
public:
  std::string toString() const override;
  double latitude;
  double longitude;
};

struct InputContactMessageContent : public InputMessageContent {
public:
  std::string toString() const override;
  std::string phoneNumber;
  std::string firstName;
  ::tgbot::types::Ptr<std::string> lastName;
};

struct InputVenueMessageContent : public InputMessageContent {
public:
  std::string toString() const override;
  std::string title;
  std::string address;
  ::tgbot::types::Ptr<std::string> foursquareId;
  double latitude;
  double longitude;
};

//
// InlineQueryResult
//
struct InlineQueryResult {
public:
  // Not explicit constructor
  InlineQueryResult() = default;
  InlineQueryResult(const char *customMarkup);
  InlineQueryResult(const std::string &customMarkup);

  virtual std::string toString() const;

private:
  const std::string what;
};

struct InlineQueryResultAudio : public InlineQueryResult {
public:
  std::string toString() const override;
  std::string type;
  std::string id;
  std::string audioUrl;
  std::string title;
  InputMessageContent inputMessageContent;
  ::tgbot::types::Ptr<std::string> caption;
  ::tgbot::types::Ptr<std::string> performer;
  ::tgbot::types::Ptr<InlineKeyboardMarkup> replyMarkup;
  int audioDuration;
};

struct InlineQueryResultArticle : public InlineQueryResult {
public:
  std::string toString() const override;
  std::string type;
  std::string id;
  std::string title;
  ::tgbot::types::Ptr<InputMessageContent> inputMessageContent;
  ::tgbot::types::Ptr<InlineKeyboardMarkup> replyMarkup;
  ::tgbot::types::Ptr<std::string> url;
  ::tgbot::types::Ptr<std::string> description;
  ::tgbot::types::Ptr<std::string> thumbUrl;
  int thumbWidth;
  int thumbHeight;
  bool hideUrl : 1;
};

struct InlineQueryResultContact : public InlineQueryResult {
public:
  std::string toString() const override;
  std::string type;
  std::string id;
  std::string phoneNumber;
  std::string firstName;
  ::tgbot::types::Ptr<std::string> lastName;
  ::tgbot::types::Ptr<std::string> thumbUrl;
  ::tgbot::types::Ptr<InlineKeyboardMarkup> replyMarkup;
  ::tgbot::types::Ptr<InputMessageContent> inputMessageContent;
  int thumbWidth;
  int thumbHeight;
};

struct InlineQueryResultGame : public InlineQueryResult {
public:
  std::string toString() const override;
  std::string type;
  std::string id;
  std::string gameShortName;
  ::tgbot::types::Ptr<InlineKeyboardMarkup> replyMarkup;
};

struct InlineQueryResultDocument : public InlineQueryResult {
public:
  std::string toString() const override;
  std::string type;
  std::string id;
  std::string title;
  std::string documentUrl;
  std::string mimeType;
  ::tgbot::types::Ptr<std::string> caption;
  ::tgbot::types::Ptr<std::string> description;
  ::tgbot::types::Ptr<InlineKeyboardMarkup> replyMarkup;
  ::tgbot::types::Ptr<InputMessageContent> inputMessageContent;
  ::tgbot::types::Ptr<std::string> thumbUrl;
  int thumbWidth;
  int thumbHeight;
};

struct InlineQueryResultGif : public InlineQueryResult {
public:
  std::string toString() const override;
  std::string type;
  std::string id;
  std::string gifUrl;
  std::string thumbUrl;
  ::tgbot::types::Ptr<std::string> title;
  ::tgbot::types::Ptr<std::string> caption;
  ::tgbot::types::Ptr<InlineKeyboardMarkup> replyMarkup;
  ::tgbot::types::Ptr<InputMessageContent> inputMessageContent;
  int gifWidth;
  int gifHeight;
  int gifDuration;
};

struct InlineQueryResultLocation : public InlineQueryResult {
public:
  std::string toString() const override;
  std::string type;
  std::string id;
  std::string title;
  ::tgbot::types::Ptr<InlineKeyboardMarkup> replyMarkup;
  ::tgbot::types::Ptr<InputMessageContent> inputMessageContent;
  ::tgbot::types::Ptr<std::string> thumbUrl;
  double latitude;
  double longitude;
  int thumbWidth;
  int thumbHeight;
};

struct InlineQueryResultMpeg4Gif : public InlineQueryResult {
public:
  std::string toString() const override;
  std::string type;
  std::string id;
  std::string mpeg4Url;
  std::string thumbUrl;
  ::tgbot::types::Ptr<std::string> title;
  ::tgbot::types::Ptr<std::string> caption;
  ::tgbot::types::Ptr<InlineKeyboardMarkup> replyMarkup;
  ::tgbot::types::Ptr<InputMessageContent> inputMessageContent;
  int mpeg4Width;
  int mpeg4Height;
  int mpeg4Duration;
};

struct InlineQueryResultPhoto : public InlineQueryResult {
public:
  std::string toString() const override;
  std::string type;
  std::string id;
  std::string photoUrl;
  std::string thumbUrl;
  ::tgbot::types::Ptr<std::string> title;
  ::tgbot::types::Ptr<std::string> description;
  ::tgbot::types::Ptr<std::string> caption;
  ::tgbot::types::Ptr<InputMessageContent> inputMessageContent;
  ::tgbot::types::Ptr<InlineKeyboardMarkup> replyMarkup;
  int photoWidth;
  int photoHeight;
};

struct InlineQueryResultVenue : public InlineQueryResult {
public:
  std::string toString() const override;
  std::string type;
  std::string id;
  std::string title;
  std::string address;
  ::tgbot::types::Ptr<std::string> foursquareId;
  ::tgbot::types::Ptr<std::string> thumbUrl;
  ::tgbot::types::Ptr<InputMessageContent> inputMessageContent;
  ::tgbot::types::Ptr<InlineKeyboardMarkup> replyMarkup;
  double latitude;
  double longitude;
  int thumbWidth;
  int thumbHeight;
};

struct InlineQueryResultVideo : public InlineQueryResult {
public:
  std::string toString() const override;
  std::string type;
  std::string id;
  std::string videoUrl;
  std::string mimeType;
  std::string thumbUrl;
  std::string title;
  ::tgbot::types::Ptr<std::string> caption;
  ::tgbot::types::Ptr<std::string> description;
  ::tgbot::types::Ptr<InlineKeyboardMarkup> replyMarkup;
  ::tgbot::types::Ptr<InputMessageContent> inputMessageContent;
  int videoWidth;
  int videoHeight;
  int videoDuration;
};

struct InlineQueryResultVoice : public InlineQueryResult {
public:
  std::string toString() const override;
  std::string type;
  std::string id;
  std::string title;
  std::string voiceUrl;
  ::tgbot::types::Ptr<std::string> caption;
  ::tgbot::types::Ptr<InputMessageContent> inputMessageContent;
  ::tgbot::types::Ptr<InlineKeyboardMarkup> replyMarkup;
  int voiceDuration;
};

struct InlineQueryResultCachedAudio : public InlineQueryResult {
public:
  std::string toString() const override;
  std::string type;
  std::string id;
  std::string audioFileId;
  ::tgbot::types::Ptr<std::string> caption;
  ::tgbot::types::Ptr<InputMessageContent> inputMessageContent;
  ::tgbot::types::Ptr<InlineKeyboardMarkup> replyMarkup;
};

struct InlineQueryResultCachedDocument : public InlineQueryResult {
public:
  std::string toString() const override;
  std::string type;
  std::string id;
  std::string documentFileId;
  std::string title;
  ::tgbot::types::Ptr<std::string> description;
  ::tgbot::types::Ptr<std::string> caption;
  ::tgbot::types::Ptr<InputMessageContent> inputMessageContent;
  ::tgbot::types::Ptr<InlineKeyboardMarkup> replyMarkup;
};

struct InlineQueryResultCachedGif : public InlineQueryResult {
public:
  std::string toString() const override;
  std::string type;
  std::string id;
  std::string gifFileId;
  ::tgbot::types::Ptr<std::string> title;
  ::tgbot::types::Ptr<std::string> caption;
  ::tgbot::types::Ptr<InputMessageContent> inputMessageContent;
  ::tgbot::types::Ptr<InlineKeyboardMarkup> replyMarkup;
};

struct InlineQueryResultCachedMpeg4Gif : public InlineQueryResult {
public:
  std::string toString() const override;
  std::string type;
  std::string id;
  std::string mpeg4FileId;
  ::tgbot::types::Ptr<std::string> title;
  ::tgbot::types::Ptr<std::string> caption;
  ::tgbot::types::Ptr<InputMessageContent> inputMessageContent;
  ::tgbot::types::Ptr<InlineKeyboardMarkup> replyMarkup;
};

struct InlineQueryResultCachedPhoto : public InlineQueryResult {
public:
  std::string toString() const override;
  std::string type;
  std::string id;
  std::string photoFileId;
  ::tgbot::types::Ptr<std::string> title;
  ::tgbot::types::Ptr<std::string> description;
  ::tgbot::types::Ptr<std::string> caption;
  ::tgbot::types::Ptr<InputMessageContent> inputMessageContent;
  ::tgbot::types::Ptr<InlineKeyboardMarkup> replyMarkup;
};

struct InlineQueryResultCachedSticker : public InlineQueryResult {
public:
  std::string toString() const override;
  std::string type;
  std::string id;
  std::string stickerFileId;
  ::tgbot::types::Ptr<InputMessageContent> inputMessageContent;
  ::tgbot::types::Ptr<InlineKeyboardMarkup> replyMarkup;
};

struct InlineQueryResultCachedVideo : public InlineQueryResult {
public:
  std::string toString() const override;
  std::string type;
  std::string id;
  std::string title;
  std::string videoFileId;
  ::tgbot::types::Ptr<std::string> description;
  ::tgbot::types::Ptr<std::string> caption;
  ::tgbot::types::Ptr<InputMessageContent> inputMessageContent;
  ::tgbot::types::Ptr<InlineKeyboardMarkup> replyMarkup;
};

struct InlineQueryResultCachedVoice : public InlineQueryResult {
public:
  std::string toString() const override;
  std::string type;
  std::string id;
  std::string title;
  std::string voiceFileId;
  ::tgbot::types::Ptr<std::string> caption;
  ::tgbot::types::Ptr<InputMessageContent> inputMessageContent;
  ::tgbot::types::Ptr<InlineKeyboardMarkup> replyMarkup;
};

struct LabeledPrice {
public:
  std::string label;
  int amount;
};

/*!
 * @brief This struct contains parameters for sendInvoice method
 */
struct Invoice {
public:
  std::vector<LabeledPrice> prices;
  std::string title;
  std::string description;
  std::string payload;
  std::string providerToken;
  std::string startParameter;
  std::string currency;
  ::tgbot::types::Ptr<std::string> photoUrl;
  int photoSize;
  int photoWidth;
  int photoHeight;
  bool needName : 1;
  bool needPhoneNumber : 1;
  bool needEmail : 1;
  bool needShippingAddress : 1;
  bool isFlexible : 1;
};

struct ShippingOption {
public:
  std::vector<LabeledPrice> prices;
  std::string id;
  std::string title;
};

} // namespace types

} // namespace methods

} // namespace tgbot

#endif
