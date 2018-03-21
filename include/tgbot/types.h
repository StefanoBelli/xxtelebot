#ifndef TGBOT_TYPES_H
#define TGBOT_TYPES_H

#include <memory>
#include <string>
#include <vector>

namespace Json {
struct Value;
}

namespace tgbot {
/*!
 * @brief API-interacting types
 */
namespace types {

/*!
 * @typedef Ptr, a unique smart pointer alias
 */
template <typename _Ty> using Ptr = std::unique_ptr<_Ty>;

struct Message; // forward declaration

enum class UpdateType {
  MESSAGE,
  EDITED_MESSAGE,
  EDITED_CHANNEL_POST,
  INLINE_QUERY,
  CHOSEN_INLINE_RESULT,
  CALLBACK_QUERY,
  SHIPPING_QUERY,
  PRE_CHECKOUT_QUERY,
  CHANNEL_POST
};

enum class ChatType { PRIVATE, GROUP, SUPERGROUP, CHANNEL };

enum class MessageEntityType {
  MENTION,
  HASHTAG,
  BOT_COMMAND,
  URL,
  EMAIL,
  BOLD,
  ITALIC,
  CODE,
  PRE,
  TEXT_LINK,
  TEXT_MENTION
};

enum class ChatMemberStatus {
  CREATOR,
  ADMINISTRATOR,
  MEMBER,
  RESTRICTED,
  LEFT,
  KICKED
};

struct User {
public:
  explicit User(const Json::Value &object);
  std::string firstName;
  Ptr<std::string> lastName;
  Ptr<std::string> username;
  Ptr<std::string> languageCode;
  int id;
  bool isBot : 1;
};

struct ChatPhoto {
public:
  explicit ChatPhoto(const Json::Value &object);
  std::string smallFileId;
  std::string bigFileId;
};

struct MessageEntity {
public:
  explicit MessageEntity(const Json::Value &object);
  Ptr<User> user;
  Ptr<std::string> url;
  int offset;
  int length;
  MessageEntityType type;
};

struct Audio {
public:
  explicit Audio(const Json::Value &object);
  std::string fileId;
  Ptr<std::string> performer;
  Ptr<std::string> title;
  Ptr<std::string> mimeType;
  int fileSize;
  int duration;
};

struct PhotoSize {
public:
  PhotoSize() = default;
  explicit PhotoSize(const Json::Value &object);
  std::string fileId;
  int fileSize;
  int width;
  int height;
};

struct Document {
public:
  explicit Document(const Json::Value &object);
  std::string fileId;
  Ptr<PhotoSize> thumb;
  Ptr<std::string> fileName;
  Ptr<std::string> mimeType;
  int fileSize;
};

struct Voice {
public:
  explicit Voice(const Json::Value &object);
  std::string fileId;
  Ptr<std::string> mimeType;
  int fileSize;
  int duration;
};

struct Contact {
public:
  explicit Contact(const Json::Value &object);
  std::string phoneNumber;
  std::string firstName;
  Ptr<std::string> lastName;
  int userId;
};

struct Location {
public:
  explicit Location(const Json::Value &object);
  std::string longitude;
  std::string latitude;
};

struct Animation {
public:
  explicit Animation(const Json::Value &object);
  std::string fileId;
  Ptr<PhotoSize> thumb;
  Ptr<std::string> fileName;
  Ptr<std::string> mimeType;
  int fileSize;
};

struct Venue {
public:
  explicit Venue(const Json::Value &object);
  Location location;
  std::string title;
  std::string address;
  Ptr<std::string> fourSquareId;
};

struct VideoNote {
public:
  explicit VideoNote(const Json::Value &object);
  std::string fileId;
  Ptr<PhotoSize> thumb;
  int fileSize;
  int length;
  int duration;
};

struct MaskPosition {
public:
  explicit MaskPosition(const Json::Value &object);
  std::string point;
  double xShift;
  double yShift;
  double scale;
};

struct Sticker {
public:
  explicit Sticker(const Json::Value &object);
  std::string fileId;
  Ptr<MaskPosition> maskPosition;
  Ptr<PhotoSize> thumb;
  Ptr<std::string> emoji;
  Ptr<std::string> setName;
  int width;
  int height;
  int fileSize;
};

struct StickerSet {
public:
  explicit StickerSet(const Json::Value &object);
  std::string name;
  std::string title;
  std::vector<Sticker> stickers;
  bool containsMasks : 1;
};

struct Video {
public:
  explicit Video(const Json::Value &object);
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
  explicit Invoice(const Json::Value &object);
  std::string title;
  std::string description;
  std::string startParameter;
  std::string currency;
  int totalAmount;
};

struct ShippingAddress {
public:
  explicit ShippingAddress(const Json::Value &object);
  std::string countryCode;
  std::string state;
  std::string city;
  std::string streetLineOne;
  std::string streetLineTwo;
  std::string postCode;
};

struct OrderInfo {
public:
  explicit OrderInfo(const Json::Value &object);
  Ptr<ShippingAddress> shippingAddress;
  Ptr<std::string> name;
  Ptr<std::string> phoneNumber;
  Ptr<std::string> email;
};

struct SuccessfulPayment {
public:
  explicit SuccessfulPayment(const Json::Value &object);
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
  explicit Game(const Json::Value &object);
  std::string title;
  std::string description;
  std::vector<PhotoSize> photo;
  Ptr<Animation> animation;
  Ptr<std::vector<MessageEntity>> textEntities;
  Ptr<std::string> text;
};

struct GameHighScore {
public:
  explicit GameHighScore(const Json::Value &object);
  User user;
  int position;
  int score;
};

struct Chat {
public:
  explicit Chat(const Json::Value &object);
  ChatType type;
  Ptr<Message> pinnedMessage;
  Ptr<ChatPhoto> photo;
  Ptr<std::string> title;
  Ptr<std::string> username;
  Ptr<std::string> firstName;
  Ptr<std::string> lastName;
  Ptr<std::string> description;
  Ptr<std::string> inviteLink;
  std::int64_t id;
  bool allMembersAreAdministrators;
};

struct Message {
public:
  explicit Message(const Json::Value &object);
  Chat chat; // guranteed
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
  Ptr<User> leftChatMember;
  Ptr<std::string> newChatTitle;
  Ptr<std::vector<PhotoSize>> newChatPhoto;
  Ptr<Message> pinnedMessage;
  Ptr<Invoice> invoice;
  Ptr<SuccessfulPayment> successfulPayment;
  std::int64_t migrateToChatId;
  std::int64_t migrateFromChatId;
  int forwardFromMessageId;
  int forwardDate;
  int editDate;
  int messageId; // guranteed
  int date;      // guranteed
  bool deleteChatPhoto : 1;
  bool groupChatCreated : 1;
  bool supergroupChatCreated : 1;
  bool channelChatCreated : 1;
};

struct InlineQuery {
public:
  explicit InlineQuery(const Json::Value &object);
  User from;
  std::string id;
  std::string query;
  std::string offset;
  Ptr<Location> location;
};

struct ChosenInlineResult {
public:
  explicit ChosenInlineResult(const Json::Value &object);
  User from;
  std::string resultId;
  std::string query;
  Ptr<Location> location;
  Ptr<std::string> inlineMessageId;
};

struct CallbackQuery {
public:
  explicit CallbackQuery(const Json::Value &object);
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
  explicit ShippingQuery(const Json::Value &object);
  ShippingAddress shippingAddress;
  User from;
  std::string id;
  std::string invoicePayload;
};

struct PreCheckoutQuery {
public:
  explicit PreCheckoutQuery(const Json::Value &object);
  User from;
  std::string currency;
  std::string invoicePayload;
  std::string id;
  Ptr<std::string> shippingOptionId;
  Ptr<OrderInfo> orderInfo;
  int totalAmount;
};

struct Update {
public:
  explicit Update(const Json::Value &object);
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
  explicit ResponseParameters(const Json::Value &object);
  std::int64_t migrateToChatId;
  int retryAfter;
};

struct File {
public:
  explicit File(const Json::Value &object);
  std::string fileId;
  Ptr<std::string> filePath;
  int fileSize;
};

struct UserProfilePhotos {
public:
  explicit UserProfilePhotos(const Json::Value &object);
  std::vector<std::vector<PhotoSize>> photos;
  int totalCount;
};

struct KeyboardButton {
public:
  std::string text;
  bool requestContact : 1;
  bool requestLocation : 1;
};

struct WebhookInfo {
public:
  explicit WebhookInfo(const Json::Value &object);
  std::string url;
  Ptr<std::string> lastErrorMessage;
  Ptr<std::vector<std::string>> allowedUpdates;
  int pendingUpdateCount;
  int lastErrorDate;
  int maxConnections;
  bool hasCustomCertificate : 1;
};

/*!
 * @brief (note) according to telegram API documentation,
 * this is only a placeholder, currently using this has no effects
 * until specified
 */
enum class CallbackGame { GAME_CALLBACK };

struct ChatMember {
public:
  explicit ChatMember(const Json::Value &object);
  User user;
  ChatMemberStatus status;
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

} // namespace types

} // namespace tgbot

#endif
