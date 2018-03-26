#ifndef TGBOT_METHODS_API_H
#define TGBOT_METHODS_API_H

#include "../logger.h"
#include "types.h"

namespace tgbot {

/*!
 * @brief TG API methods and relative (parameter) types
 */
namespace methods {

namespace api_types = ::tgbot::types;

/*!
 * @brief Contains Telegram bot API methods
 */
class Api {
public:
  api_types::Message
  sendMessage(const std::string &chatId, const std::string &text,
              const types::ParseMode & = types::ParseMode::DEFAULT,
              const bool &disableWebPagePreview = false,
              const bool &disableNotification = false,
              const types::ReplyMarkup &replyMarkup = "") const;

  api_types::Message
  sendMessage(const std::string &chatId, const std::string &text,
              const int replyToMessageId,
              const types::ParseMode & = types::ParseMode::DEFAULT,
              const bool &disableWebPagePreview = false,
              const bool &disableNotification = false,
              const types::ReplyMarkup &replyMarkup = "") const;

  api_types::Message
  forwardMessage(const std::string &chatId, const std::string &fromChatId,
                 const int &messageId,
                 const bool &disableNotification = false) const;

  api_types::Message
  sendPhoto(const std::string &chatId, const std::string &photo,
            const types::FileSource &source = types::FileSource::EXTERNAL,
            const std::string &mimeType = "", const std::string &caption = "",
            const bool &disableNotification = false,
            const int &replyToMessageId = -1,
            const types::ReplyMarkup &replyMarkup = "") const;

  api_types::Message
  sendAudio(const std::string &chatId, const std::string &audio,
            const types::FileSource &source = types::FileSource::EXTERNAL,
            const std::string &mimeType = "", const std::string &caption = "",
            const int &duration = -1, const std::string &performer = "",
            const std::string &title = "",
            const bool &disableNotification = false,
            const int &replyToMessageId = -1,
            const types::ReplyMarkup &replyMarkup = "") const;

  api_types::Message sendDocument(
      const std::string &chatId, const std::string &document,
      const types::FileSource &source = types::FileSource::EXTERNAL,
      const std::string &mimeType = "", const std::string &caption = "",
      const bool &disableNotification = false, const int &replyToMessageId = -1,
      const types::ReplyMarkup &replyMarkup = "") const;

  api_types::Message
  sendVideo(const std::string &chatId, const std::string &video,
            const types::FileSource &source = types::FileSource::EXTERNAL,
            const std::string &mimeType = "", const int &duration = -1,
            const int &width = -1, const int &height = -1,
            const std::string &caption = "",
            const bool &disableNotification = false,
            const int &replyToMessageId = -1,
            const types::ReplyMarkup &replyMarkup = "") const;

  api_types::Message
  sendVoice(const std::string &chatId, const std::string &voice,
            const types::FileSource &source = types::FileSource::EXTERNAL,
            const std::string &caption = "", const int &duration = -1,
            const bool &disableNotification = false,
            const int &replyToMessageId = -1,
            const types::ReplyMarkup &replyMarkup = "") const;

  api_types::Message
  sendVideoNote(const std::string &chatId, const std::string &videoNote,
                const types::FileSource &source = types::FileSource::EXTERNAL,
                const std::string &caption = "", const int &duration = -1,
                const bool &disableNotification = false,
                const int &replyToMessageId = -1,
                const types::ReplyMarkup &replyMarkup = "") const;

  api_types::Message
  sendLocation(const std::string &chatId, const double &latitude,
               const double &longitude, const bool &disableNotification = false,
               const int &replyToMessageId = -1,
               const types::ReplyMarkup &replyMarkup = "") const;

  api_types::Message
  sendVenue(const std::string &chatId, const double &latitude,
            const double &longitude, const std::string &title,
            const std::string &address, const std::string &foursquareId = "",
            const bool &disableNotification = false,
            const int &replyToMessageId = -1,
            const types::ReplyMarkup &replyMarkup = "") const;

  api_types::Message
  sendContact(const std::string &chatId, const std::string &phoneNumber,
              const std::string &firstName, const std::string &lastName = "",
              const bool &disableNotification = false,
              const int &replyToMessageId = -1,
              const types::ReplyMarkup &replyMarkup = "") const;

  api_types::Message
  sendSticker(const std::string &chatId, const std::string &sticker,
              const types::FileSource &source = types::FileSource::EXTERNAL,
              const bool &disableNotification = false,
              const int &replyToMessageId = -1,
              const types::ReplyMarkup &replyMarkup = "") const;

  /*!
   * @brief Please refer to tgbot::methods::types::Invoice struct
   */
  api_types::Message sendInvoice(const int &chatId,
                                 const types::Invoice &invoice,
                                 const bool &disableNotification = false,
                                 const int &replyToMessageId = -1) const;

  /*!
   * @brief Please refer to tgbot::methods::types::Invoice struct
   */
  api_types::Message sendInvoice(const int &chatId,
                                 const types::Invoice &invoice,
                                 const types::InlineKeyboardMarkup &replyMarkup,
                                 const bool &disableNotification = false,
                                 const int &replyToMessageId = -1) const;

  api_types::Message sendGame(const int &chatId,
                              const std::string &gameShortName,
                              const bool &disableNotification = false,
                              const int &replyToMessageId = -1,
                              const types::ReplyMarkup &replyMarkup = "") const;

  api_types::Message setGameScore(const std::string &userId, const int &score,
                                  const std::string &inlineMessageId,
                                  const bool &force = false,
                                  const bool &disableEditMessage = false) const;

  api_types::Message setGameScore(const std::string &userId, const int &score,
                                  const int &chatId, const int &messageId,
                                  const bool &force = false,
                                  const bool &disableEditMessage = false) const;

  std::vector<api_types::GameHighScore>
  getGameHighScores(const int &userId,
                    const std::string &inlineMessageId) const;

  std::vector<api_types::GameHighScore>
  getGameHighScores(const int &userId, const int &chatId,
                    const int &messageId) const;

  /*!
   * @brief Use this overload if the shipping query cannot proceed
   */
  bool answerShippingQuery(const std::string &shippingQueryId,
                           const std::string &errorMessage) const;

  /*!
   * @brief Use this overload if the shipping query CAN proceed
   */
  bool answerShippingQuery(
      const std::string &shippingQueryId,
      const std::vector<types::ShippingOption> &shippingOptions) const;

  /*!
   * @brief Use this overload if the checkout phase can take place
   */
  bool answerPreCheckoutQuery(const std::string &preCheckoutQueryId,
                              const std::string &errorMessage) const;

  /*!
   * @brief Use this overload if the checkout phase CANNOT take place
   */
  bool answerPreCheckoutQuery(const std::string &preCheckoutQueryId) const;

  api_types::StickerSet getStickerSet(const std::string &name) const;

  api_types::File uploadStickerFile(
      const int &userId, const std::string &pngSticker,
      const types::FileSource &source = types::FileSource::EXTERNAL) const;

  bool createNewStickerSet(
      const int &userId, const std::string &name, const std::string &title,
      const std::string &emoji, const std::string &pngSticker,
      const types::FileSource &source = types::FileSource::EXTERNAL) const;

  bool createNewStickerSet(
      const int &userId, const std::string &name, const std::string &title,
      const std::string &emoji, const std::string &pngSticker,
      const api_types::MaskPosition &maskPosition,
      const types::FileSource &source = types::FileSource::EXTERNAL) const;

  bool addStickerToSet(
      const int &userId, const std::string &name, const std::string &emoji,
      const std::string &pngSticker,
      const types::FileSource &source = types::FileSource::EXTERNAL) const;

  bool addStickerToSet(
      const int &userId, const std::string &name, const std::string &emoji,
      const std::string &pngSticker,
      const api_types::MaskPosition &maskPosition,
      const types::FileSource &source = types::FileSource::EXTERNAL) const;

  bool setStickerPositionInSet(const std::string &sticker,
                               const int position) const;

  bool deleteStickerFromSet(const std::string &sticker) const;

  bool sendChatAction(const std::string &chatId,
                      const types::ChatAction &action) const;

  bool kickChatMember(const std::string &chatId, const int &userId,
                      const int &untilDate = -1) const;

  bool unbanChatMember(const std::string &chatId, const int &userId) const;

  bool restrictChatMember(const std::string &chatId, const int &userId,
                          const types::ChatMemberRestrict &permissions,
                          const int &untilDate = -1) const;

  bool promoteChatMember(const std::string &chatId, const int &userId,
                         const types::ChatMemberPromote &permissions) const;

  std::string exportChatInviteLink(const std::string &chatId) const;

  bool setChatPhoto(const std::string &chatId, const std::string &filename,
                    const std::string &mimeType) const;

  bool deleteChatPhoto(const std::string &chatId) const;

  bool setChatTitle(const std::string &chatId, const std::string &title) const;

  bool setChatDescription(const std::string &chatId,
                          const std::string &description) const;

  bool pinChatMessage(const std::string &chatId, const std::string &messageId,
                      const bool &disableNotification = false) const;

  bool unpinChatMessage(const std::string &chatId) const;

  bool leaveChat(const std::string &chatId) const;

  bool answerCallbackQuery(const std::string &callbackQueryId,
                           const std::string &text = "",
                           const bool &showAlert = false,
                           const std::string &url = "",
                           const int &cacheTime = 0) const;

  bool answerInlineQuery(
      const std::string &inlineQueryId,
      const std::vector<::tgbot::types::Ptr<types::InlineQueryResult>> &results,
      const int &cacheTime = 0, const bool &isPersonal = true,
      const std::string &nextOffset = "", const std::string &switchPmText = "",
      const std::string &switchPmParameter = "") const;

  api_types::Message
  editMessageText(const std::string &inlineMessageId, const std::string &text,
                  const types::ParseMode &parseMode = types::ParseMode::DEFAULT,
                  const bool &disableWebPagePreview = false) const;

  api_types::Message
  editMessageText(const std::string &inlineMessageId,
                  const types::InlineKeyboardMarkup &replyMarkup,
                  const std::string &text,
                  const types::ParseMode &parseMode = types::ParseMode::DEFAULT,
                  const bool &disableWebPagePreview = false) const;

  api_types::Message
  editMessageText(const std::string &chatId, const std::string &messageId,
                  const std::string &text,
                  const types::ParseMode &parseMode = types::ParseMode::DEFAULT,
                  const bool &disableWebPagePreview = false) const;

  api_types::Message
  editMessageText(const std::string &chatId, const std::string& messageId,
                  const types::InlineKeyboardMarkup &replyMarkup,
                  const std::string &text,
                  const types::ParseMode &parseMode = types::ParseMode::DEFAULT,
                  const bool &disableWebPagePreview = false) const;

  api_types::Message
  editMessageReplyMarkup(const std::string &inlineMessageId,
                         const types::InlineKeyboardMarkup &replyMarkup) const;

  api_types::Message
  editMessageReplyMarkup(const std::string &chatId,
                         const std::string &messageId,
                         const types::InlineKeyboardMarkup &replyMarkup) const;

  api_types::Message editMessageCaption(const std::string &chatId,
                                        const std::string &messageId,
                                        const std::string &caption) const;

  api_types::Message editMessageCaption(const std::string &inlineMessageId,
                                        const std::string &caption) const;

  api_types::Message
  editMessageCaption(const std::string &chatId, const std::string &messageId,
                     const types::InlineKeyboardMarkup &replyMarkup,
                     const std::string &caption) const;

  api_types::Message
  editMessageCaption(const std::string &inlineMessageId,
                     const types::InlineKeyboardMarkup &replyMarkup,
                     const std::string &caption) const;

  bool deleteMessage(const std::string &chatId,
                     const std::string &messageId) const;

  api_types::User getMe() const;

  api_types::File getFile(const std::string &fileId) const;

  api_types::Chat getChat(const std::string &chatId) const;

  std::vector<api_types::ChatMember>
  getChatAdministrators(const std::string &chatId) const;

  unsigned getChatMembersCount(const std::string &chatId) const;

  api_types::ChatMember getChatMember(const std::string &chatId,
                                      const int &userId) const;

  api_types::UserProfilePhotos
  getUserProfilePhotos(const int &userId, const unsigned &offset = 0,
                       const unsigned &limit = 100) const;

  bool deleteWebhook() const;

  api_types::WebhookInfo getWebhookInfo() const;

  bool
  setWebhook(const std::string &url, const int &maxConnections = 40,
             const std::vector<api_types::UpdateType> &allowedUpdates = {});

  bool
  setWebhook(const std::string &url, const std::string &certificate,
             const int &maxConnections = 40,
             const std::vector<api_types::UpdateType> &allowedUpdates = {});

  inline Logger const& getLogger() const {
  	  return logger;
  }

  inline Logger& getLogger() {
  	  return logger;
  }

protected:
  Api() = delete;
  ~Api() = default;
  Api(const Api&) = default;
  Api(Api&&) = default;
  Api& operator=(const Api&) = default;
  Api& operator=(Api&&) = default;

  explicit Api(const std::string &token);

  Api(const std::string &token,
      const std::vector<api_types::UpdateType> &allowedUpdates,
      const int &timeout, const int &limit);

  Api(const std::string &token, const std::string &url,
      const int &maxConnections,
      const std::vector<api_types::UpdateType> &allowedUpdates);

  Api(const std::string &token, const std::string &url,
      const std::string &certificate, const int &maxConnections,
      const std::vector<api_types::UpdateType> &allowedUpdates);

  int getUpdates(void *c, std::vector<api_types::Update> &updates);

  std::string urlWebhook;

private:
  const std::string baseApi;
  std::string updateApiRequest;
  int currentOffset;
  tgbot::Logger logger;
};

} // namespace methods

} // namespace tgbot

#endif
