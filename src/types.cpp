#include <json/json.h>
#include <sstream>
#include <string>
#include <tgbot/types.h>

#define BOOL_TOSTR(xvalue) ((xvalue) ? "true" : "false")

using ArrayIndex = Json::Value::ArrayIndex;
using namespace tgbot::types;

tgbot::types::Update::Update(const Json::Value &object)
    : updateId(object.get("update_id", "").asInt()) {

  if (object.isMember("message")) {
    this->message = Ptr<Message>(new Message(object.get("message", "")));
    this->updateType = UpdateType::MESSAGE;
  } else if (object.isMember("edited_message")) {
    this->editedMessage =
        Ptr<Message>(new Message(object.get("edited_message", "")));
    this->updateType = UpdateType::EDITED_MESSAGE;
  } else if (object.isMember("callback_query")) {
    this->callbackQuery =
        Ptr<CallbackQuery>(new CallbackQuery(object.get("callback_query", "")));
    this->updateType = UpdateType::CALLBACK_QUERY;
  } else if (object.isMember("chosen_inline_result")) {
    this->chosenInlineResult = Ptr<ChosenInlineResult>(
        new ChosenInlineResult(object.get("chosen_inline_result", "")));
    this->updateType = UpdateType::CHOSEN_INLINE_RESULT;
  } else if (object.isMember("inline_query")) {
    this->inlineQuery =
        Ptr<InlineQuery>(new InlineQuery(object.get("inline_query", "")));
    this->updateType = UpdateType::INLINE_QUERY;
  } else if (object.isMember("shipping_query")) {
    this->shippingQuery =
        Ptr<ShippingQuery>(new ShippingQuery(object.get("shipping_query", "")));
    this->updateType = UpdateType::SHIPPING_QUERY;
  } else if (object.isMember("pre_checkout_query")) {
    this->preCheckoutQuery = Ptr<PreCheckoutQuery>(
        new PreCheckoutQuery(object.get("pre_checkout_query", "")));
    this->updateType = UpdateType::PRE_CHECKOUT_QUERY;
  } else if (object.isMember("edited_channel_post")) {
    this->editedChannelPost =
        Ptr<Message>(new Message(object.get("edited_channel_post", "")));
    this->updateType = UpdateType::EDITED_CHANNEL_POST;
  } else if (object.isMember("channel_post")) {
    this->channelPost =
        Ptr<Message>(new Message(object.get("channel_post", "")));
    this->updateType = UpdateType::CHANNEL_POST;
  }
}

tgbot::types::Message::Message(const Json::Value &object)
    : chat(object.get("chat", "")),
      messageId(object.get("message_id", "").asInt()),
      date(object.get("date", "").asInt()) {

  if (object.isMember("migrate_to_chat_id"))
    this->migrateToChatId = object.get("migrate_to_chat_id", "").asInt64();

  if (object.isMember("migrate_from_chat_id"))
    this->migrateFromChatId = object.get("migrate_from_chat_id", "").asInt64();

  if (object.isMember("entities")) {
    this->entities =
        Ptr<std::vector<MessageEntity>>(new std::vector<MessageEntity>{});

    for (auto const &singleEntity : object.get("entities", ""))
      this->entities->emplace_back(singleEntity);
  }

  if (object.isMember("caption"))
    this->caption = Ptr<std::string>(
        new std::string(object.get("caption", "").asCString()));

  // we may have just entered a new chat

  if (object.isMember("reply_to_message")) {
    this->replyToMessage =
        Ptr<Message>(new Message(object.get("reply_to_message", "")));
    if (object.isMember("supergroup_chat_created"))
      this->supergroupChatCreated = true;

    if (object.isMember("channel_chat_created"))
      this->channelChatCreated = true;
  }

  // end

  // is the message sent from user or channel?

  if (object.isMember("from"))
    this->from = Ptr<User>(new User(object.get("from", "")));
  else {
    if (object.isMember("author_signature"))
      this->authorSignature = Ptr<std::string>(
          new std::string(object.get("author_signature", "").asCString()));
  }

  // end

  // forwarded messages

  if (object.isMember("forward_date")) {
    this->forwardDate = object.get("forward_date", "").asInt();
    if (object.isMember("forward_from"))
      this->forwardFrom = Ptr<User>(new User(object.get("forward_from", "")));
    else if (object.isMember("forward_from_chat")) {
      this->forwardFromChat =
          Ptr<Chat>(new Chat(object.get("forward_from_chat", "")));

      this->forwardFromMessageId =
          object.get("forward_from_message_id", "").asInt();

      if (object.isMember("forward_signature"))
        this->forwardSignature = Ptr<std::string>(
            new std::string(object.get("forward_signature", "").asCString()));
    }
  } else if (object.isMember("edit_date"))
    this->editDate = object.get("edit_date", "").asInt();

  // end

  // single message type

  if (object.isMember("text"))
    this->text =
        Ptr<std::string>(new std::string(object.get("text", "").asCString()));

  else if (object.isMember("audio"))
    this->audio = Ptr<Audio>(new Audio(object.get("audio", "")));

  else if (object.isMember("document"))
    this->document = Ptr<Document>(new Document(object.get("document", "")));

  else if (object.isMember("game"))
    this->game = Ptr<Game>(new Game(object.get("game", "")));

  else if (object.isMember("sticker"))
    this->sticker = Ptr<Sticker>(new Sticker(object.get("sticker", "")));

  else if (object.isMember("video"))
    this->video = Ptr<Video>(new Video(object.get("video", "")));

  else if (object.isMember("video_note"))
    this->videoNote =
        Ptr<VideoNote>(new VideoNote(object.get("video_note", "")));

  else if (object.isMember("invoice"))
    this->invoice = Ptr<Invoice>(new Invoice(object.get("invoice", "")));

  else if (object.isMember("successful_payment"))
    this->successfulPayment = Ptr<SuccessfulPayment>(
        new SuccessfulPayment(object.get("successful_payment", "")));

  else if (object.isMember("contact"))
    this->contact = Ptr<Contact>(new Contact(object.get("contact", "")));

  else if (object.isMember("location"))
    this->location = Ptr<Location>(new Location(object.get("location", "")));

  else if (object.isMember("venue"))
    this->venue = Ptr<Venue>(new Venue(object.get("venue", "")));

  else if (object.isMember("photo")) {
    this->photo = Ptr<std::vector<PhotoSize>>(new std::vector<PhotoSize>{});

    for (auto const &singlePhoto : object.get("photo", ""))
      this->photo->emplace_back(singlePhoto);
  } else {
    if (object.isMember("delete_chat_photo"))
      this->deleteChatPhoto = true;

    else if (object.isMember("group_chat_created"))
      this->groupChatCreated = true;

    else if (object.isMember("left_chat_member"))
      this->leftChatMember =
          Ptr<User>(new User(object.get("left_chat_member", "")));

    else if (object.isMember("new_chat_title"))
      this->newChatTitle = Ptr<std::string>(
          new std::string(object.get("new_chat_title", "").asCString()));

    else if (object.isMember("pinned_message"))
      this->pinnedMessage =
          Ptr<Message>(new Message(object.get("pinned_message", "")));

    else if (object.isMember("new_chat_photo")) {
      this->newChatPhoto =
          Ptr<std::vector<PhotoSize>>(new std::vector<PhotoSize>{});

      for (auto const &singlePhoto : object.get("new_chat_photo", ""))
        this->newChatPhoto->emplace_back(singlePhoto);
    }

    else if (object.isMember("new_chat_members")) {
      this->newChatMembers = Ptr<std::vector<User>>(new std::vector<User>{});

      for (auto const &singleUser : object.get("new_chat_members", ""))
        this->newChatMembers->emplace_back(singleUser);
    }
  }

  // end
}

tgbot::types::CallbackQuery::CallbackQuery(const Json::Value &object)
    : from(object.get("from", "")), id(object.get("id", "").asCString()),
      chatInstance(object.get("chat_instance", "").asCString()) {

  if (object.isMember("message"))
    this->message = Ptr<Message>(new Message(object.get("message", "")));

  if (object.isMember("inline_message_id"))
    this->inlineMessageId = Ptr<std::string>(
        new std::string(object.get("inline_message_id", "").asCString()));

  if (object.isMember("data"))
    this->data =
        Ptr<std::string>(new std::string(object.get("data", "").asCString()));

  if (object.isMember("game_short_name"))
    this->gameShortName = Ptr<std::string>(
        new std::string(object.get("game_short_name", "").asCString()));
}

tgbot::types::ChosenInlineResult::ChosenInlineResult(const Json::Value &object)
    : from(object.get("from", "")),
      resultId(object.get("result_id", "").asCString()),
      query(object.get("query", "").asCString()) {

  if (object.isMember("location"))
    this->location = Ptr<Location>(new Location(object.get("location", "")));

  if (object.isMember("inline_message_id"))
    this->inlineMessageId = Ptr<std::string>(
        new std::string(object.get("inline_message_id", "").asCString()));
}

tgbot::types::InlineQuery::InlineQuery(const Json::Value &object)
    : from(object.get("from", "")), id(object.get("id", "").asCString()),
      query(object.get("query", "").asCString()),
      offset(object.get("offset", "").asCString()) {

  if (object.isMember("location"))
    this->location = Ptr<Location>(new Location(object.get("location", "")));
}

tgbot::types::ShippingQuery::ShippingQuery(const Json::Value &object)
    : shippingAddress(object.get("shipping_address", "")),
      from(object.get("from", "")), id(object.get("id", "").asCString()),
      invoicePayload(object.get("invoice_payload", "").asCString()) {}

tgbot::types::PreCheckoutQuery::PreCheckoutQuery(const Json::Value &object)
    : from(object.get("from", "")),
      currency(object.get("currency", "").asCString()),
      invoicePayload(object.get("invoice_payload", "").asCString()),
      id(object.get("id", "").asCString()),
      totalAmount(object.get("total_amount", "").asInt()) {

  if (object.isMember("shipping_option_id"))
    this->shippingOptionId = Ptr<std::string>(
        new std::string(object.get("shipping_option_id", "").asCString()));

  if (object.isMember("order_info"))
    this->orderInfo =
        Ptr<OrderInfo>(new OrderInfo(object.get("order_info", "")));
}

tgbot::types::Chat::Chat(const Json::Value &object) {
  const std::string &chatType = object.get("type", "").asCString();
  if (chatType == "private")
    this->type = ChatType::PRIVATE;
  else if(chatType == "supergroup")
    this->type = ChatType::SUPERGROUP;
  else if (chatType == "group")
    this->type = ChatType::GROUP;
  else if (chatType == "channel")
    this->type = ChatType::CHANNEL;

  id = object.get("id", "").asInt64();

  if (this->type != ChatType::PRIVATE &&
      object.isMember("all_members_are_administrators"))
    this->allMembersAreAdministrators = true;

  if (object.isMember("title"))
    this->title =
        Ptr<std::string>(new std::string(object.get("title", "").asCString()));

  if (object.isMember("username"))
    this->username = Ptr<std::string>(
        new std::string(object.get("username", "").asCString()));

  if (object.isMember("first_name"))
    this->firstName = Ptr<std::string>(
        new std::string(object.get("first_name", "").asCString()));

  if (object.isMember("last_name"))
    this->lastName = Ptr<std::string>(
        new std::string(object.get("last_name", "").asCString()));

  if (object.isMember("description"))
    this->description = Ptr<std::string>(
        new std::string(object.get("description", "").asCString()));

  if (object.isMember("invite_link"))
    this->inviteLink = Ptr<std::string>(
        new std::string(object.get("invite_link", "").asCString()));

  if (object.isMember("pinned_message"))
    this->pinnedMessage =
        Ptr<Message>(new Message(object.get("pinned_message", "")));

  if (object.isMember("photo"))
    this->photo = Ptr<ChatPhoto>(new ChatPhoto(object.get("photo", "")));
}

tgbot::types::User::User(const Json::Value &object)
    : firstName(object.get("first_name", "").asCString()),
      id(object.get("id", "").asInt()),
      isBot(object.get("is_bot", "").asBool()) {

  if (object.isMember("last_name"))
    this->lastName = Ptr<std::string>(
        new std::string(object.get("last_name", "").asCString()));

  if (object.isMember("username"))
    this->username = Ptr<std::string>(
        new std::string(object.get("username", "").asCString()));

  if (object.isMember("language_code"))
    this->languageCode = Ptr<std::string>(
        new std::string(object.get("language_code", "").asCString()));
}

tgbot::types::ShippingAddress::ShippingAddress(const Json::Value &object)
    : countryCode(object.get("country_code", "").asCString()),
      state(object.get("state", "").asCString()),
      city(object.get("city", "").asCString()),
      streetLineOne(object.get("street_line_one", "").asCString()),
      streetLineTwo(object.get("street_line_two", "").asCString()),
      postCode(object.get("post_code", "").asCString()) {}

tgbot::types::ChatPhoto::ChatPhoto(const Json::Value &object)
    : smallFileId(object.get("small_file_id", "").asCString()),
      bigFileId(object.get("big_file_id", "").asCString()) {}

tgbot::types::Audio::Audio(const Json::Value &object)
    : fileId(object.get("file_id", "").asCString()),
      duration(object.get("duration", "").asInt()) {

  if (object.isMember("file_size"))
    this->fileSize = object.get("file_size", "").asInt();

  if (object.isMember("performer"))
    this->performer = Ptr<std::string>(
        new std::string(object.get("performer", "").asCString()));

  if (object.isMember("title"))
    this->title =
        Ptr<std::string>(new std::string(object.get("title", "").asCString()));

  if (object.isMember("mime_type"))
    this->mimeType = Ptr<std::string>(
        new std::string(object.get("mime_type", "").asCString()));
}

tgbot::types::Document::Document(const Json::Value &object)
    : fileId(object.get("file_id", "").asCString()) {

  if (object.isMember("thumb"))
    this->thumb = Ptr<PhotoSize>(new PhotoSize(object.get("thumb", "")));

  if (object.isMember("file_name"))
    this->fileName = Ptr<std::string>(
        new std::string(object.get("file_name", "").asCString()));

  if (object.isMember("mime_type"))
    this->mimeType = Ptr<std::string>(
        new std::string(object.get("mime_type", "").asCString()));

  if (object.isMember("file_size"))
    this->fileSize = object.get("file_size", "").asInt();
}

tgbot::types::PhotoSize::PhotoSize(const Json::Value &object)
    : fileId(object.get("file_id", "").asCString()),
      width(object.get("width", "").asInt()),
      height(object.get("height", "").asInt()) {

  if (object.isMember("file_size"))
    this->fileSize = object.get("file_size", "").asInt();
}

tgbot::types::Game::Game(const Json::Value &object)
    : title(object.get("title", "").asCString()),
      description(object.get("description", "").asCString()), photo({}) {

  for (auto const &singlePhoto : object.get("photo", ""))
    this->photo.emplace_back(singlePhoto);

  if (object.isMember("animation"))
    this->animation =
        Ptr<Animation>(new Animation(object.get("animation", "")));

  if (object.isMember("text_entities")) {
    this->textEntities =
        Ptr<std::vector<MessageEntity>>(new std::vector<MessageEntity>{});

    for (auto const &singleEntity : object.get("text_entities", ""))
      this->textEntities->emplace_back(singleEntity);
  }

  if (object.isMember("text"))
    this->text =
        Ptr<std::string>(new std::string(object.get("text", "").asCString()));
}

tgbot::types::MaskPosition::MaskPosition(const Json::Value &object)
    : point(object.get("point", "").asCString()),
      xShift(object.get("x_shift", "").asDouble()),
      yShift(object.get("y_shift", "").asDouble()),
      scale(object.get("scale", "").asDouble()) {}

tgbot::types::Sticker::Sticker(const Json::Value &object)
    : fileId(object.get("file_id", "").asCString()),
      width(object.get("width", "").asInt()),
      height(object.get("height", "").asInt()),
      fileSize(object.get("file_size", "").asInt()) {

  if (object.isMember("thumb"))
    this->thumb = Ptr<PhotoSize>(new PhotoSize(object.get("thumb", "")));

  if (object.isMember("emoji"))
    this->emoji =
        Ptr<std::string>(new std::string(object.get("emoji", "").asCString()));

  if (object.isMember("set_name"))
    this->setName = Ptr<std::string>(
        new std::string(object.get("set_name", "").asCString()));

  if (object.isMember("mask_position"))
    this->maskPosition =
        Ptr<MaskPosition>(new MaskPosition(object.get("mask_position", "")));

  if (object.isMember("file_size"))
    this->fileSize = object.get("file_size", "").asInt();
}

tgbot::types::Video::Video(const Json::Value &object)
    : fileId(object.get("file_id", "").asCString()),
      width(object.get("width", "").asInt()),
      height(object.get("height", "").asInt()),
      duration(object.get("duration", "").asInt()) {

  if (object.isMember("file_size"))
    this->fileSize = object.get("file_size", "").asInt();

  if (object.isMember("thumb"))
    this->thumb = Ptr<PhotoSize>(new PhotoSize(object.get("thumb", "")));

  if (object.isMember("mime_type"))
    this->mimeType = Ptr<std::string>(
        new std::string(object.get("mime_type", "").asCString()));
}

tgbot::types::Voice::Voice(const Json::Value &object)
    : fileId(object.get("file_id", "").asCString()),
      duration(object.get("duration", "").asInt()) {

  if (object.isMember("file_size"))
    this->fileSize = object.get("file_size", "").asInt();

  if (object.isMember("mime_type"))
    this->mimeType = Ptr<std::string>(
        new std::string(object.get("mime_type", "").asCString()));
}

tgbot::types::VideoNote::VideoNote(const Json::Value &object)
    : fileId(object.get("file_id", "").asCString()),
      length(object.get("length", "").asInt()),
      duration(object.get("duration", "").asInt()) {

  if (object.isMember("file_size"))
    this->fileSize = object.get("file_size", "").asInt();

  if (object.isMember("thumb"))
    this->thumb = Ptr<PhotoSize>(new PhotoSize(object.get("thumb", "")));
}

tgbot::types::Contact::Contact(const Json::Value &object)
    : phoneNumber(object.get("phone_number", "").asCString()),
      firstName(object.get("first_name", "").asCString()) {

  if (object.isMember("last_name"))
    this->lastName = Ptr<std::string>(
        new std::string(object.get("last_name", "").asCString()));

  if (object.isMember("user_id"))
    this->userId = object.get("user_id", "").asInt();
}

tgbot::types::Location::Location(const Json::Value &object)
    : longitude(object.get("longitude", "").asCString()),
      latitude(object.get("latitude", "").asCString()) {}

tgbot::types::Venue::Venue(const Json::Value &object)
    : location(object.get("location", "")),
      title(object.get("title", "").asCString()),
      address(object.get("address", "").asCString()) {

  if (object.isMember("foursquare_id"))
    this->fourSquareId = Ptr<std::string>(
        new std::string(object.get("foursquare_id", "").asCString()));
}

tgbot::types::Invoice::Invoice(const Json::Value &object)
    : title(object.get("title", "").asCString()),
      description(object.get("description", "").asCString()),
      startParameter(object.get("start_parameter", "").asCString()),
      currency(object.get("currency", "").asCString()),
      totalAmount(object.get("total_amount", "").asInt()) {}

tgbot::types::SuccessfulPayment::SuccessfulPayment(const Json::Value &object)
    : currency(object.get("currency", "").asCString()),
      invoicePayload(object.get("invoice_payload", "").asCString()),
      telegramPaymentChargeId(
          object.get("telegram_payment_charge_id", "").asCString()),
      providerPaymentChargeId(
          object.get("provider_payment_charge_id", "").asCString()),
      totalAmount(object.get("total_amount", "").asInt()) {

  if (object.isMember("shipping_option_id"))
    this->shippingOptionId = Ptr<std::string>(
        new std::string(object.get("shipping_option_id", "").asCString()));

  if (object.isMember("order_info"))
    this->orderInfo =
        Ptr<OrderInfo>(new OrderInfo(object.get("order_info", "")));
}

tgbot::types::MessageEntity::MessageEntity(const Json::Value &object)
    : offset(object.get("offset", "").asInt()),
      length(object.get("length", "").asInt()) {

  const std::string &entityTypeStr = object.get("type", "").asString();
  if (entityTypeStr == "mention")
    type = MessageEntityType::MENTION;
  else if (entityTypeStr == "hashtag")
    type = MessageEntityType::HASHTAG;
  else if (entityTypeStr == "bot_command")
    type = MessageEntityType::BOT_COMMAND;
  else if (entityTypeStr == "url")
    type = MessageEntityType::URL;
  else if (entityTypeStr == "email")
    type = MessageEntityType::EMAIL;
  else if (entityTypeStr == "bold")
    type = MessageEntityType::BOLD;
  else if (entityTypeStr == "italic")
    type = MessageEntityType::ITALIC;
  else if (entityTypeStr == "code")
    type = MessageEntityType::CODE;
  else if (entityTypeStr == "pre")
    type = MessageEntityType::PRE;
  else if (entityTypeStr == "text_link")
    type = MessageEntityType::TEXT_LINK;
  else if (entityTypeStr == "text_mention")
    type = MessageEntityType::TEXT_MENTION;

  if (object.isMember("user"))
    this->user = Ptr<User>(new User(object.get("user", "")));

  if (object.isMember("url"))
    this->url =
        Ptr<std::string>(new std::string(object.get("url", "").asCString()));
}

tgbot::types::OrderInfo::OrderInfo(const Json::Value &object) {
  if (object.isMember("shipping_address"))
    this->shippingAddress = Ptr<ShippingAddress>(
        new ShippingAddress(object.get("shipping_address", "")));

  if (object.isMember("name"))
    this->name =
        Ptr<std::string>(new std::string(object.get("name", "").asCString()));

  if (object.isMember("phone_number"))
    this->phoneNumber = Ptr<std::string>(
        new std::string(object.get("phone_number", "").asCString()));

  if (object.isMember("email"))
    this->email =
        Ptr<std::string>(new std::string(object.get("email", "").asCString()));
}

tgbot::types::StickerSet::StickerSet(const Json::Value &object)
    : name(object.get("name", "").asCString()),
      title(object.get("title", "").asCString()),
      stickers(std::vector<Sticker>{}),
      containsMasks(object.get("contains_masks", "").asBool()) {

  for (auto const &singleSticker : object.get("stickers", ""))
    stickers.emplace_back(singleSticker);
}

tgbot::types::ResponseParameters::ResponseParameters(
    const Json::Value &object) {
  if (object.isMember("migrate_to_chat_id"))
    this->migrateToChatId = object.get("migrate_to_chat_id", "").asInt64();

  if (object.isMember("retry_after"))
    this->retryAfter = object.get("retry_after", "").asInt();
}

tgbot::types::File::File(const Json::Value &object)
    : fileId(object.get("file_id", "").asCString()) {

  if (object.isMember("file_size"))
    this->fileSize = object.get("file_size", "").asInt();

  if (object.isMember("file_path"))
    this->filePath = Ptr<std::string>(
        new std::string(object.get("file_path", "").asCString()));
}

tgbot::types::UserProfilePhotos::UserProfilePhotos(const Json::Value &object)
    : totalCount(object.get("total_count", "").asInt()) {
  const Json::Value &matArr{object.get("photos", "")};
  for (ArrayIndex i = 0; i < matArr.size(); ++i) {
    this->photos.emplace_back();
    for (ArrayIndex j = 0; j < matArr[i].size(); ++j)
      this->photos.at(i).emplace_back(matArr[i][j]);
  }
}

tgbot::types::ChatMember::ChatMember(const Json::Value &object)
    : user(object.get("user", "")),
      untilDate(object.get("until_date", "").asInt()) {

  const std::string &statusStr{object.get("status", "").asString()};
  if (statusStr == "creator")
    status = ChatMemberStatus::CREATOR;
  else if (statusStr == "administrator")
    status = ChatMemberStatus::ADMINISTRATOR;
  else if (statusStr == "member")
    status = ChatMemberStatus::MEMBER;
  else if (statusStr == "restricted")
    status = ChatMemberStatus::RESTRICTED;
  else if (statusStr == "left")
    status = ChatMemberStatus::LEFT;
  else if (statusStr == "kicked")
    status = ChatMemberStatus::KICKED;

  if (object.isMember("can_be_edited"))
    this->canBeEdited = object.get("can_be_edited", "").asBool();

  if (object.isMember("can_change_info"))
    this->canChangeInfo = object.get("can_change_info", "").asBool();

  if (object.isMember("can_post_messages"))
    this->canPostMessages = object.get("can_post_messages", "").asBool();

  if (object.isMember("can_edit_messages"))
    this->canEditMessages = object.get("can_edit_messages", "").asBool();

  if (object.isMember("can_delete_messages"))
    this->canDeleteMessages = object.get("can_delete_messages", "").asBool();

  if (object.isMember("can_invite_users"))
    this->canInviteUsers = object.get("can_invite_users", "").asBool();

  if (object.isMember("can_restrict_members"))
    this->canRestrictMembers = object.get("can_restrict_members", "").asBool();

  if (object.isMember("can_pin_messages"))
    this->canPinMessages = object.get("can_pin_messages", "").asBool();

  if (object.isMember("can_promote_members"))
    this->canPromoteMembers = object.get("can_promote_members", "").asBool();

  if (object.isMember("can_send_messages"))
    this->canSendMessages = object.get("can_send_messages", "").asBool();

  if (object.isMember("can_send_media_messages"))
    this->canSendMediaMessages =
        object.get("can_send_media_messages", "").asBool();

  if (object.isMember("can_send_other_messages"))
    this->canSendOtherMessages =
        object.get("can_send_other_messages", "").asBool();

  if (object.isMember("can_add_web_page_previews"))
    this->canAddWebPagePreviews =
        object.get("can_add_web_page_previews", "").asBool();
}

tgbot::types::Animation::Animation(const Json::Value &object)
    : fileId(object.get("file_id", "").asCString()) {

  if (object.isMember("file_size"))
    this->fileSize = object.get("file_size", "").asInt();

  if (object.isMember("thumb"))
    this->thumb = Ptr<PhotoSize>(new PhotoSize(object.get("thumb", "")));

  if (object.isMember("file_name"))
    this->fileName = Ptr<std::string>(
        new std::string(object.get("file_name", "").asCString()));

  if (object.isMember("mime_type"))
    this->mimeType = Ptr<std::string>(
        new std::string(object.get("mime_type", "").asCString()));
}

tgbot::types::WebhookInfo::WebhookInfo(const Json::Value &object)
    : url(object.get("url", "").asCString()),
      pendingUpdateCount(object.get("pending_update_count", "").asInt()),
      hasCustomCertificate(object.get("has_custom_certificate", "").asBool()) {
  if (object.isMember("last_error_date"))
    this->lastErrorDate = object.get("last_error_date", "").asInt();

  if (object.isMember("last_error_message"))
    this->lastErrorMessage = Ptr<std::string>(
        new std::string(object.get("last_error_message", "").asCString()));

  if (object.isMember("max_connections"))
    this->maxConnections = object.get("max_connections", "").asInt();

  if (object.isMember("allowed_updates")) {
    this->allowedUpdates =
        Ptr<std::vector<std::string>>(new std::vector<std::string>{});
    for (auto const &singleAllowedUpdate : object.get("allowed_updates", ""))
      this->allowedUpdates->emplace_back(singleAllowedUpdate.asCString());
  }
}

tgbot::types::GameHighScore::GameHighScore(const Json::Value &object)
    : user(object.get("user", "")),
      position(object.get("position", "").asInt()),
      score(object.get("score", "").asInt()) {}
