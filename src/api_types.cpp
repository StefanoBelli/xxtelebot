#include <sstream>
#include <tgbot/methods/types.h>

#define BOOL_TOSTR(xvalue) ((xvalue) ? "true" : "false")

#define SEPARATE(k)                                                            \
  if (k)                                                                       \
  jsonify << ','

std::string tgbot::methods::types::InputMessageContent::toString() const {
  return what;
}

std::string tgbot::methods::types::ReplyMarkup::toString() const {
  return what;
}

std::string tgbot::methods::types::InlineQueryResult::toString() const {
  return what;
}

tgbot::methods::types::ReplyMarkup::ReplyMarkup(const char *customMarkup)
    : what(customMarkup) {}

tgbot::methods::types::ReplyMarkup::ReplyMarkup(const std::string &customMarkup)
    : what(customMarkup) {}

tgbot::methods::types::InputMessageContent::InputMessageContent(
    const char *customMarkup)
    : what(customMarkup) {}

tgbot::methods::types::InputMessageContent::InputMessageContent(
    const std::string &customMarkup)
    : what(customMarkup) {}

tgbot::methods::types::InlineQueryResult::InlineQueryResult(
    const char *customMarkup)
    : what(customMarkup) {}

tgbot::methods::types::InlineQueryResult::InlineQueryResult(
    const std::string &customMarkup)
    : what(customMarkup) {}

std::string tgbot::methods::types::InlineKeyboardMarkup::toString() const {
  const std::size_t &r = inlineKeyboard.size();

  if (!r)
    return "";

  std::stringstream jsonify;
  jsonify << "{ \"inline_keyboard\": [";

  for (std::size_t i = 0; i < r; ++i) {
    SEPARATE(i);
    jsonify << "[";

    const std::vector<InlineKeyboardButton> &ikb = inlineKeyboard.at(i);
    for (size_t j = 0; j < ikb.size(); ++j) {
      SEPARATE(j);

      const InlineKeyboardButton &currentButton = ikb.at(j);
      jsonify << "{ \"text\": \"" << currentButton.text
              << "\", \"pay\": " << BOOL_TOSTR(currentButton.pay);

      if (currentButton.url)
        jsonify << ", \"url\": \"" << *(currentButton.url) << "\"";

      if (currentButton.callbackData)
        jsonify << ", \"callback_data\": \"" << *(currentButton.callbackData)
                << "\"";

      if (currentButton.switchInlineQuery)
        jsonify << ", \"switch_inline_query\": \""
                << *(currentButton.switchInlineQuery) << "\"";

      if (currentButton.switchInlineQueryCurrentChat)
        jsonify << ", \"switch_inline_query_current_chat\": \""
                << *(currentButton.switchInlineQueryCurrentChat) << "\"";

      jsonify << "}";
    }

    jsonify << "]";
  }

  jsonify << "]}";

  return jsonify.str();
}

std::string tgbot::methods::types::ReplyKeyboardMarkup::toString() const {
  const std::size_t &r = keyboard.size();

  if (!r)
    return "";

  std::stringstream jsonify;
  jsonify << "{ \"resize_keyboard\": " << BOOL_TOSTR(resizeKeyboard)
          << ", \"one_time_keyboard\": " << BOOL_TOSTR(oneTimeKeyboard)
          << ", \"selective\": " << BOOL_TOSTR(selective) << ", \"keyboard\":[";

  for (std::size_t i = 0; i < r; ++i) {
    SEPARATE(i);
    jsonify << "[";

    const std::vector<KeyboardButton> &kb = keyboard.at(i);
    for (size_t j = 0; j < kb.size(); ++j) {
      SEPARATE(j);

      const KeyboardButton &currentButton = kb.at(j);
      jsonify << "{ \"text\": \"" << currentButton.text << "\","
              << "\"request_contact\": "
              << BOOL_TOSTR(currentButton.requestContact)
              << ",\"request_location\": "
              << BOOL_TOSTR(currentButton.requestLocation) << "}";
    }
    jsonify << "]";
  }

  jsonify << "]}";

  return jsonify.str();
}

std::string tgbot::methods::types::ReplyKeyboardRemove::toString() const {
  std::stringstream jsonify;
  jsonify << "{\"remove_keyboard\": true, \"selective\": "
          << BOOL_TOSTR(selective) << "}";

  return jsonify.str();
}

std::string tgbot::methods::types::ForceReply::toString() const {
  std::stringstream jsonify;
  jsonify << "{\"force_reply\": true, \"selective\": " << BOOL_TOSTR(selective)
          << "}";

  return jsonify.str();
}

std::string tgbot::methods::types::InputTextMessageContent::toString() const {
  std::stringstream jsonify;
  jsonify << "{ \"message_text\": \"" << messageText
          << "\",\"disable_web_page_preview\": "
          << BOOL_TOSTR(disableWebPagePreview);

  if (parseMode == ParseMode::HTML)
    jsonify << ",\"parse_mode\": \"HTML\"";
  else if (parseMode == ParseMode::MARKDOWN)
    jsonify << ",\"parse_mode\": \"Markdown\"";

  jsonify << "}";

  return jsonify.str();
}

std::string
tgbot::methods::types::InputLocationMessageContent::toString() const {
  std::stringstream jsonify;
  jsonify << "{ \"latitude\": " << latitude << ",\"longitude\": " << longitude
          << "}";

  return jsonify.str();
}

std::string
tgbot::methods::types::InputContactMessageContent::toString() const {
  std::stringstream jsonify;
  jsonify << "{ \"phone_number\": \"" << phoneNumber << "\", \"first_name\": \""
          << firstName << "\"";

  if (lastName)
    jsonify << ",\"last_name\": \"" << *(lastName) << "\"";

  jsonify << "}";

  return jsonify.str();
}

std::string tgbot::methods::types::InputVenueMessageContent::toString() const {
  std::stringstream jsonify;
  jsonify << "{ \"title\": \"" << title << "\", \"address\":\"" << address
          << "\", \"latitude\": " << latitude
          << ", \"longitude\": " << longitude;

  if (foursquareId)
    jsonify << ",\"foursquare_id\":\"" << *(foursquareId) << "\"";

  jsonify << "}";

  return jsonify.str();
}

std::string tgbot::methods::types::InlineQueryResultAudio::toString() const {
  std::stringstream jsonify;
  jsonify << "{ \"type\": \"" << type << "\", \"id\": \"" << id << "\","
          << "\"audio_url\": \"" << audioUrl << "\", \"title\": \"" << title
          << "\""
          << ",\"input_message_content\": " << inputMessageContent.toString();

  if (caption)
    jsonify << ",\"caption\": \"" << *(caption) << "\"";

  if (performer)
    jsonify << ",\"performer\": \"" << *(performer) << "\"";

  if (replyMarkup)
    jsonify << ",\"reply_markup\": " << replyMarkup->toString();

  if (audioDuration)
    jsonify << ",\"audio_duration\": " << audioDuration;

  jsonify << "}";

  return jsonify.str();
}

std::string tgbot::methods::types::InlineQueryResultGame::toString() const {
  std::stringstream jsonify;
  jsonify << "{ \"type\": \"" << type << "\", \"id\": \"" << id << "\""
          << ",\"game_short_name\": \"" << gameShortName << "\"";

  if (replyMarkup)
    jsonify << ",\"reply_markup\": " << replyMarkup->toString();

  jsonify << "}";

  return jsonify.str();
}

std::string tgbot::methods::types::InlineQueryResultArticle::toString() const {
  std::stringstream jsonify;
  jsonify << "{ \"type\": \"" << type << "\", \"id\": \"" << id << "\""
          << ",\"title\": \"" << title << "\","
          << "\"input_message_content\": " << inputMessageContent->toString()
          << ",\"hide_url\": " << hideUrl;

  if (replyMarkup)
    jsonify << ",\"reply_markup\": " << replyMarkup->toString();

  if (url)
    jsonify << ",\"url\": \"" << *(url) << "\"";

  if (description)
    jsonify << ",\"description\": \"" << *(description) << "\"";

  if (thumbUrl)
    jsonify << ",\"thumb_url\": \"" << *(thumbUrl) << "\"";

  if (thumbWidth)
    jsonify << ",\"thumb_width\": " << thumbWidth;

  if (thumbHeight)
    jsonify << ",\"thumb_height\": " << thumbHeight;

  jsonify << "}";

  return jsonify.str();
}

std::string tgbot::methods::types::InlineQueryResultContact::toString() const {
  std::stringstream jsonify;
  jsonify << "{ \"type\": \"" << type << "\", \"id\": \"" << id << "\""
          << ",\"phone_number\": \"" << phoneNumber << "\", \"first_name\": \""
          << firstName << "\"";

  if (lastName)
    jsonify << ",\"last_name\": \"" << *(lastName) << "\"";

  if (thumbUrl)
    jsonify << ",\"thumb_url\": \"" << *(thumbUrl) << "\"";

  if (thumbWidth)
    jsonify << ",\"thumb_width\": " << thumbWidth;

  if (thumbHeight)
    jsonify << ",\"thumb_height\": " << thumbHeight;

  if (replyMarkup)
    jsonify << ",\"reply_markup\": " << replyMarkup->toString();

  if (inputMessageContent)
    jsonify << ",\"input_message_content\": "
            << inputMessageContent->toString();

  jsonify << "}";

  return jsonify.str();
}

std::string tgbot::methods::types::InlineQueryResultDocument::toString() const {
  std::stringstream jsonify;
  jsonify << "{ \"type\": \"" << type << "\", \"id\": \"" << id << "\""
          << ", \"title\": \"" << title << "\", \"document_url\": \""
          << documentUrl << "\", \"mime_type\": \"" << mimeType << "\"";

  if (thumbHeight)
    jsonify << ",\"thumb_height\": " << thumbHeight;

  if (thumbWidth)
    jsonify << ",\"thumb_width\": " << thumbWidth;

  if (caption)
    jsonify << ",\"caption\": \"" << *(caption) << "\"";

  if (description)
    jsonify << ",\"description\": \"" << *(description) << "\"";

  if (thumbUrl)
    jsonify << ",\"thumb_url\": \"" << *(thumbUrl) << "\"";

  if (replyMarkup)
    jsonify << ",\"reply_markup\": " << replyMarkup->toString();

  if (inputMessageContent)
    jsonify << ",\"input_message_content\": "
            << inputMessageContent->toString();

  jsonify << "}";

  return jsonify.str();
}

std::string tgbot::methods::types::InlineQueryResultGif::toString() const {
  std::stringstream jsonify;
  jsonify << "{ \"type\": \"" << type << "\", \"id\": \"" << id
          << "\", \"gif_url\": \"" << gifUrl << "\", \"thumb_url\": \""
          << thumbUrl << "\"";

  if (gifWidth)
    jsonify << ",\"gif_width\": " << gifWidth;

  if (gifHeight)
    jsonify << ",\"gif_height\": " << gifHeight;

  if (gifDuration)
    jsonify << ",\"gif_duration\": " << gifDuration;

  if (title)
    jsonify << ",\"title\": \"" << *(title) << "\"";

  if (caption)
    jsonify << ",\"title\": \"" << *(caption) << "\"";

  if (replyMarkup)
    jsonify << ",\"reply_markup\": " << replyMarkup->toString();

  if (inputMessageContent)
    jsonify << ",\"input_message_content\": "
            << inputMessageContent->toString();

  jsonify << "}";

  return jsonify.str();
}

std::string tgbot::methods::types::InlineQueryResultLocation::toString() const {
  std::stringstream jsonify;
  jsonify << "{ \"type\": \"" << type << "\", \"id\": \"" << id
          << "\", \"title\": \"" << title << "\", \"latitude\": " << latitude
          << ", \"longitude\": " << longitude;

  if (thumbWidth)
    jsonify << ",\"thumb_width\": " << thumbWidth;

  if (thumbHeight)
    jsonify << ",\"thumb_height\": " << thumbHeight;

  if (thumbUrl)
    jsonify << ",\"thumb_url\": \"" << *(thumbUrl) << "\"";

  if (replyMarkup)
    jsonify << ",\"reply_markup\": " << replyMarkup->toString();

  if (inputMessageContent)
    jsonify << ",\"input_message_content\": "
            << inputMessageContent->toString();

  jsonify << "}";

  return jsonify.str();
}

std::string tgbot::methods::types::InlineQueryResultMpeg4Gif::toString() const {
  std::stringstream jsonify;
  jsonify << "{ \"type\": \"" << type << "\", \"id\": \"" << id
          << "\", \"mpeg4_url\": \"" << mpeg4Url << "\", \"thumb_url\": \""
          << thumbUrl << "\"";

  if (title)
    jsonify << ",\"title\": \"" << *(title) << "\"";

  if (caption)
    jsonify << ",\"caption\": \"" << *(caption) << "\"";

  if (replyMarkup)
    jsonify << ",\"reply_markup\": " << replyMarkup->toString();

  if (inputMessageContent)
    jsonify << ",\"input_message_content\": "
            << inputMessageContent->toString();

  if (mpeg4Width)
    jsonify << ",\"mpeg4_width\": " << mpeg4Width;

  if (mpeg4Height)
    jsonify << ",\"mpeg4_height\": " << mpeg4Height;

  if (mpeg4Duration)
    jsonify << ",\"mpeg4_duration\": " << mpeg4Duration;

  jsonify << "}";

  return jsonify.str();
}

std::string tgbot::methods::types::InlineQueryResultPhoto::toString() const {
  std::stringstream jsonify;
  jsonify << "{ \"type\": \"" << type << "\", \"id\": \"" << id
          << "\", \"photo_url\": \"" << photoUrl << "\", \"thumb_url\": \""
          << thumbUrl << "\"";

  if (title)
    jsonify << ",\"title\": \"" << *(title) << "\"";

  if (description)
    jsonify << ",\"description\": \"" << *(description) << "\"";

  if (caption)
    jsonify << ",\"caption\": \"" << *(caption) << "\"";

  if (replyMarkup)
    jsonify << ",\"reply_markup\": " << replyMarkup->toString();

  if (inputMessageContent)
    jsonify << ",\"input_message_content\": "
            << inputMessageContent->toString();

  if (photoWidth)
    jsonify << ",\"photo_width\": " << photoWidth;

  if (photoHeight)
    jsonify << ",\"photo_height\": " << photoHeight;

  jsonify << "}";

  return jsonify.str();
}

std::string tgbot::methods::types::InlineQueryResultVenue::toString() const {
  std::stringstream jsonify;
  jsonify << "{ \"type\": \"" << type << "\", \"id\": \"" << id
          << "\", \"title\": \"" << title << "\", \"latitude\": " << latitude
          << ", \"longitude\": " << longitude << ", \"address\": \"" << address
          << "\"";

  if (thumbWidth)
    jsonify << ",\"thumb_width\": " << thumbWidth;

  if (thumbHeight)
    jsonify << ",\"thumb_height\": " << thumbHeight;

  if (thumbUrl)
    jsonify << ",\"thumb_url\": \"" << *(thumbUrl) << "\"";

  if (foursquareId)
    jsonify << ",\"foursquare_id\": \"" << *(foursquareId) << "\"";

  if (replyMarkup)
    jsonify << ",\"reply_markup\": " << replyMarkup->toString();

  if (inputMessageContent)
    jsonify << ",\"input_message_content\": "
            << inputMessageContent->toString();

  jsonify << "}";

  return jsonify.str();
}

std::string tgbot::methods::types::InlineQueryResultVideo::toString() const {
  std::stringstream jsonify;
  jsonify << "{ \"type\": \"" << type << "\", \"id\": \"" << id
          << "\", \"video_url\": \"" << videoUrl << "\", \"thumb_url\": \""
          << thumbUrl << "\", \"title\": \"" << title << "\", \"mime_type\": \""
          << mimeType << "\"";

  if (caption)
    jsonify << ",\"caption\": \"" << *(caption) << "\"";

  if (description)
    jsonify << ",\"description\": \"" << *(description) << "\"";

  if (replyMarkup)
    jsonify << ",\"reply_markup\": " << replyMarkup->toString();

  if (inputMessageContent)
    jsonify << ",\"input_message_content\": "
            << inputMessageContent->toString();

  if (videoWidth)
    jsonify << ",\"video_width\": " << videoWidth;

  if (videoHeight)
    jsonify << ",\"video_height\": " << videoHeight;

  if (videoDuration)
    jsonify << ",\"video_duration\": " << videoDuration;

  jsonify << "}";

  return jsonify.str();
}

std::string tgbot::methods::types::InlineQueryResultVoice::toString() const {
  std::stringstream jsonify;
  jsonify << "{ \"type\": \"" << type << "\", \"id\": \"" << id
          << "\", \"title\": \"" << title << "\", \"voice_url\": \"" << voiceUrl
          << "\"";

  if (caption)
    jsonify << ",\"caption\": \"" << *(caption) << "\"";

  if (voiceDuration)
    jsonify << ",\"voice_duration\": " << voiceDuration;

  if (replyMarkup)
    jsonify << ",\"reply_markup\": " << replyMarkup->toString();

  if (inputMessageContent)
    jsonify << ",\"input_message_content\": "
            << inputMessageContent->toString();

  jsonify << "}";

  return jsonify.str();
}

std::string
tgbot::methods::types::InlineQueryResultCachedAudio::toString() const {
  std::stringstream jsonify;
  jsonify << "{ \"type\": \"" << type << "\", \"id\": \"" << id
          << "\", \"audio_file_id\": \"" << audioFileId << "\"";

  if (caption)
    jsonify << ",\"caption\": \"" << *(caption) << "\"";

  if (inputMessageContent)
    jsonify << ",\"input_message_content\": "
            << inputMessageContent->toString();

  if (replyMarkup)
    jsonify << ",\"reply_markup\": " << replyMarkup->toString();

  jsonify << "}";

  return jsonify.str();
}

std::string
tgbot::methods::types::InlineQueryResultCachedDocument::toString() const {
  std::stringstream jsonify;

  jsonify << "{ \"type\": \"" << type << "\", \"id\": \"" << id
          << "\", \"title\": \"" << title << "\", \"document_file_id\": \""
          << documentFileId << "\"";

  if (caption)
    jsonify << ",\"caption\": \"" << *(caption) << "\"";

  if (description)
    jsonify << ",\"description\": \"" << *(description) << "\"";

  if (inputMessageContent)
    jsonify << ",\"input_message_content\": "
            << inputMessageContent->toString();

  if (replyMarkup)
    jsonify << ",\"reply_markup\": " << replyMarkup->toString();

  jsonify << "}";

  return jsonify.str();
}

std::string
tgbot::methods::types::InlineQueryResultCachedGif::toString() const {
  std::stringstream jsonify;
  jsonify << "{ \"type\": \"" << type << "\", \"id\": \"" << id
          << "\", \"gif_file_id\": \"" << gifFileId << "\"";

  if (caption)
    jsonify << ",\"caption\": \"" << *(caption) << "\"";

  if (title)
    jsonify << ",\"title\": \"" << *(title) << "\"";

  if (inputMessageContent)
    jsonify << ",\"input_message_content\": "
            << inputMessageContent->toString();

  if (replyMarkup)
    jsonify << ",\"reply_markup\": " << replyMarkup->toString();

  jsonify << "}";

  return jsonify.str();
}

std::string
tgbot::methods::types::InlineQueryResultCachedMpeg4Gif::toString() const {
  std::stringstream jsonify;
  jsonify << "{ \"type\": \"" << type << "\", \"id\": \"" << id
          << "\", \"mpeg4_file_id\": \"" << mpeg4FileId << "\"";

  if (caption)
    jsonify << ",\"caption\": \"" << *(caption) << "\"";

  if (title)
    jsonify << ",\"title\": \"" << *(title) << "\"";

  if (inputMessageContent)
    jsonify << ",\"input_message_content\": "
            << inputMessageContent->toString();

  if (replyMarkup)
    jsonify << ",\"reply_markup\": " << replyMarkup->toString();

  jsonify << "}";

  return jsonify.str();
}

std::string
tgbot::methods::types::InlineQueryResultCachedPhoto::toString() const {
  std::stringstream jsonify;
  jsonify << "{ \"type\": \"" << type << "\", \"id\": \"" << id
          << "\", \"photo_file_id\": \"" << photoFileId << "\"";

  if (title)
    jsonify << ",\"title\": \"" << *(title) << "\"";

  if (description)
    jsonify << ",\"description\": \"" << *(description) << "\"";

  if (caption)
    jsonify << ",\"caption\": \"" << *(caption) << "\"";

  if (inputMessageContent)
    jsonify << ",\"input_message_content\": "
            << inputMessageContent->toString();

  if (replyMarkup)
    jsonify << ",\"reply_markup\": " << replyMarkup->toString();

  jsonify << "}";

  return jsonify.str();
}

std::string
tgbot::methods::types::InlineQueryResultCachedSticker::toString() const {
  std::stringstream jsonify;
  jsonify << "{ \"type\": \"" << type << "\", \"id\": \"" << id
          << "\", \"sticker_file_id\": \"" << stickerFileId << "\"";

  if (inputMessageContent)
    jsonify << ",\"input_message_content\": "
            << inputMessageContent->toString();

  if (replyMarkup)
    jsonify << ",\"reply_markup\": " << replyMarkup->toString();

  jsonify << "}";

  return jsonify.str();
}

std::string
tgbot::methods::types::InlineQueryResultCachedVideo::toString() const {
  std::stringstream jsonify;
  jsonify << "{ \"type\": \"" << type << "\", \"id\": \"" << id
          << "\", \"video_file_id\": \"" << videoFileId << "\","
          << "\"title\": \"" << title << "\"";

  if (description)
    jsonify << ",\"description\": \"" << *(description) << "\"";

  if (caption)
    jsonify << ",\"caption\": \"" << *(caption) << "\"";

  if (inputMessageContent)
    jsonify << ",\"input_message_content\": "
            << inputMessageContent->toString();

  if (replyMarkup)
    jsonify << ",\"reply_markup\": " << replyMarkup->toString();

  jsonify << "}";

  return jsonify.str();
}

std::string
tgbot::methods::types::InlineQueryResultCachedVoice::toString() const {
  std::stringstream jsonify;
  jsonify << "{ \"type\": \"" << type << "\", \"id\": \"" << id
          << "\", \"voice_file_id\": \"" << voiceFileId << "\","
          << "\"title\": \"" << title << "\"";

  if (caption)
    jsonify << ",\"caption\": \"" << *(caption) << "\"";

  if (inputMessageContent)
    jsonify << ",\"input_message_content\": "
            << inputMessageContent->toString();

  if (replyMarkup)
    jsonify << ",\"reply_markup\": " << replyMarkup->toString();

  jsonify << "}";

  return jsonify.str();
}
