#include <sstream>
#include <string>
#include <jsoncpp/json/json.h>
#include <tgbot/types.h>

#define BOOL_TOSTR(xvalue) \
	((xvalue) ? "true" : "false")

using ArrayIndex = Json::Value::ArrayIndex;
using namespace tgbot::types;

tgbot::types::Update::Update(const Json::Value &object) : 
	updateId(object.get("update_id","").asInt()) {

	if(object.isMember("message")) {
		message = Ptr<Message>(
				new Message(object.get("message","")));
		updateType = UpdateType::MESSAGE;
	} else if(object.isMember("edited_message")) {
		editedMessage = Ptr<Message>(
				new Message(object.get("edited_message","")));
		updateType = UpdateType::EDITED_MESSAGE;
	} else if(object.isMember("callback_query")) {
		callbackQuery = Ptr<CallbackQuery>(
				new CallbackQuery(object.get("callback_query","")));
		updateType = UpdateType::CALLBACK_QUERY;
	} else if(object.isMember("chosen_inline_result")) {
		chosenInlineResult = Ptr<ChosenInlineResult>(
				new ChosenInlineResult(object.get("chosen_inline_result","")));
		updateType = UpdateType::CHOSEN_INLINE_RESULT;
	} else if(object.isMember("inline_query")) {
		inlineQuery = Ptr<InlineQuery>(
				new InlineQuery(object.get("inline_query","")));
		updateType = UpdateType::INLINE_QUERY;
	} else if(object.isMember("shipping_query")) {
		shippingQuery = Ptr<ShippingQuery>(
				new ShippingQuery(object.get("shipping_query","")));
		updateType = UpdateType::SHIPPING_QUERY;
	} else if(object.isMember("pre_checkout_query")) {
		preCheckoutQuery = Ptr<PreCheckoutQuery>(
				new PreCheckoutQuery(object.get("pre_checkout_query","")));
		updateType = UpdateType::PRE_CHECKOUT_QUERY;
	} else if(object.isMember("edited_channel_post")) {
		editedChannelPost = Ptr<Message>(
				new Message(object.get("edited_channel_post","")));
		updateType = UpdateType::EDITED_CHANNEL_POST;
	} else if(object.isMember("channel_post")) {
        channelPost = Ptr<Message>(
        		new Message(object.get("channel_post","")));
        updateType = UpdateType::CHANNEL_POST;
    }
}

tgbot::types::Message::Message(const Json::Value &object) :
    chat(object.get("chat","")),
	messageId(object.get("message_id","").asInt()),
	date(object.get("date","").asInt()) {

}

tgbot::types::CallbackQuery::CallbackQuery(const Json::Value &object) :
    from(object.get("from","")),
	id(object.get("id","").asCString()),
	chatInstance(object.get("chat_instance","").asCString()) {

	if(object.isMember("message"))
		this->message = Ptr<Message>(
				new Message(object.get("message","")));

	if(object.isMember("inline_message_id"))
		this->inlineMessageId = Ptr<std::string>(
				new std::string(object.get("inline_message_id","").asCString()));

	if(object.isMember("data"))
		this->data = Ptr<std::string>(
				new std::string(object.get("data","").asCString()));
	
	if(object.isMember("game_short_name"))
		this->gameShortName = Ptr<std::string>(
				new std::string(object.get("game_short_name","").asCString()));
}

tgbot::types::ChosenInlineResult::ChosenInlineResult(const Json::Value &object) :
    from(object.get("from","")),
	resultId(object.get("result_id","").asCString()),
	query(object.get("query","").asCString()) {

	if(object.isMember("location"))
		this->location = Ptr<Location>(
				new Location(object.get("location","")));

	if(object.isMember("inline_message_id"))
		this->inlineMessageId = Ptr<std::string>(
				new std::string(object.get("inline_message_id","").asCString()));
}

tgbot::types::InlineQuery::InlineQuery(const Json::Value &object) :
    user(object.get("from","")),
	id(object.get("id","").asCString()),
	query(object.get("query","").asCString()),
	offset(object.get("offset","").asCString()) {

	if(object.isMember("location"))
		this->location = Ptr<Location>(
				new Location(object.get("location","")));
}

tgbot::types::ShippingQuery::ShippingQuery(const Json::Value &object) :
    shippingAddress(object.get("shipping_address","")), 
    from(object.get("from","")),
	id(object.get("id","").asCString()),
	invoicePayload(object.get("invoice_payload","").asCString()) {}

tgbot::types::PreCheckoutQuery::PreCheckoutQuery(const Json::Value &object) :
    from(object.get("from","")),
	currency(object.get("currency","").asCString()),
	invoicePayload(object.get("invoice_payload","").asCString()),
	id(object.get("id","").asCString()),
	totalAmount(object.get("total_amount","").asInt()) {
	
	if(object.isMember("shipping_option_id"))
		this->shippingOptionId = Ptr<std::string>(
				new std::string(object.get("shipping_option_id","").asCString()));

	if(object.isMember("order_info"))
		this->orderInfo = Ptr<OrderInfo>(
				new OrderInfo(object.get("order_info","")));
}

tgbot::types::Chat::Chat(const Json::Value &object) {
    const std::string& type = object.get("type","").asCString();
    if(type == "private")
        this->type = ChatType::PRIVATE;
    else if(type == "supergroup")
        this->type = ChatType::SUPERGROUP;
    else if(type == "group")
        this->type = ChatType::GROUP;
    else if(type == "channel")
        this->type = ChatType::CHANNEL;

    id = object.get("id","").asInt();

    if(this->type != ChatType::PRIVATE)
        allMembersAreAdministrators = 
        	object.get("all_members_are_administrators","").asBool();

	if(object.isMember("title"))
    	this->title = Ptr<std::string>(
    			new std::string(object.get("title","").asCString()));
    
    if(object.isMember("username"))
    	this->username = Ptr<std::string>(
    			new std::string(object.get("username","").asCString()));
    
    if(object.isMember("first_name"))
    	this->firstName = Ptr<std::string>(
    			new std::string(object.get("first_name","").asCString()));

    if(object.isMember("last_name"))
    	this->lastName = Ptr<std::string>(
    			new std::string(object.get("last_name","").asCString()));
    
    if(object.isMember("description"))
    	this->description = Ptr<std::string>(
    			new std::string(object.get("description","").asCString()));

    if(object.isMember("invite_link"))
    	this->inviteLink = Ptr<std::string>(
    			new std::string(object.get("invite_link","").asCString()));
    
    if(object.isMember("pinned_message"))
    	this->pinnedMessage = Ptr<Message>(
    			new Message(object.get("pinned_message","")));
    
    if(object.isMember("photo"))
    	this->photo = Ptr<ChatPhoto>(
    			new ChatPhoto(object.get("first_name","")));
}

tgbot::types::User::User(const Json::Value &object) :
    firstName(object.get("first_name","").asCString()),
    id(object.get("id","").asInt()),
    isBot(object.get("is_bot","").asBool()) {
   
   	if(object.isMember("last_name"))
   		this->lastName = Ptr<std::string>(
   				new std::string(object.get("last_name","").asCString()));
   	
   	if(object.isMember("username"))
   		this->username = Ptr<std::string>(
   				new std::string(object.get("username","").asCString()));
   	
   	if(object.isMember("language_code"))
   		this->languageCode = Ptr<std::string>(
   				new std::string(object.get("language_code","").asCString()));
}

tgbot::types::ShippingAddress::ShippingAddress(const Json::Value &object) :
	countryCode(object.get("country_code","").asCString()),
	state(object.get("state","").asCString()),
	city(object.get("city","").asCString()),
	streetLineOne(object.get("street_line_one","").asCString()),
	streetLineTwo(object.get("street_line_two","").asCString()),
	postCode(object.get("post_code","").asCString()) {}

tgbot::types::ChatPhoto::ChatPhoto(const Json::Value &object) :
	smallFileId(object.get("small_file_id","").asCString()),
	bigFileId(object.get("big_file_id","").asCString()) {}

tgbot::types::Audio::Audio(const Json::Value &object) :
	fileId(object.get("file_id","").asCString()),
	duration(object.get("duration","").asInt()) {
	
	if(object.isMember("file_size"))
		this->fileSize = object.get("file_size","").asInt();

	if(object.isMember("performer"))
		this->performer = Ptr<std::string>(
				new std::string(object.get("performer","").asCString()));
	
	if(object.isMember("title"))
		this->title = Ptr<std::string>(
				new std::string(object.get("title","").asCString()));

	if(object.isMember("mime_type"))
		this->mimeType = Ptr<std::string>(
				new std::string(object.get("mime_type","").asCString()));
}

tgbot::types::Document::Document(const Json::Value &object) :
	fileId(object.get("file_id","").asCString()) {
	
	if(object.isMember("thumb"))
		this->thumb = Ptr<PhotoSize>(
				new PhotoSize(object.get("thumb","")));

	if(object.isMember("file_name"))
		this->fileName = Ptr<std::string>(
				new std::string(object.get("file_name","").asCString()));

	if(object.isMember("mime_type"))
		this->mimeType = Ptr<std::string>(
				new std::string(object.get("mime_type","").asCString()));

	if(object.isMember("file_size"))
		this->fileSize = object.get("file_size","").asInt();
}

tgbot::types::PhotoSize::PhotoSize(const Json::Value &object) :
	fileId(object.get("file_id","").asCString()),
	width(object.get("width","").asInt()),
	height(object.get("height","").asInt()) {
	
	if(object.isMember("file_size"))
		this->fileSize = object.get("file_size","").asInt();
}

tgbot::types::Game::Game(const Json::Value &object) :
	title(object.get("title","").asCString()),
	description(object.get("description","").asCString()),
	photo({}) {

	for(auto const& singlePhoto : object.get("photo",""))
		this->photo.emplace_back(singlePhoto);

	if(object.isMember("animation"))
		this->animation = Ptr<Animation>(
				new Animation(object.get("animation","")));

	if(object.isMember("text_entities")) {
		this->textEntities = Ptr<std::vector<MessageEntity>>(
				new std::vector<MessageEntity>);

		for (auto const& singleEntity : object.get("text_entities",""))
			this->textEntities->emplace_back(singleEntity);
	}

	if(object.isMember("text"))
		this->text = Ptr<std::string>(
				new std::string(object.get("text","").asCString()));
}

tgbot::types::MaskPosition::MaskPosition(const Json::Value &object) :
	point(object.get("point","").asCString()),
	xShift(object.get("x_shift","").asDouble()),
	yShift(object.get("y_shift","").asDouble()),
	scale(object.get("scale","").asDouble()) {}

tgbot::types::Sticker::Sticker(const Json::Value &object) :
	fileId(object.get("file_id","").asCString()),
	width(object.get("width", "").asInt()),
	height(object.get("height", "").asInt()),
	fileSize(object.get("file_size", "").asInt()) {
	
	if(object.isMember("thumb"))
		this->thumb = Ptr<PhotoSize>(
				new PhotoSize(object.get("thumb","")));
	
	if(object.isMember("emoji"))
		this->emoji = Ptr<std::string>(
				new std::string(object.get("emoji","").asCString()));

	if(object.isMember("set_name"))
		this->setName = Ptr<std::string>(
				new std::string(object.get("set_name","").asCString()));

	if(object.isMember("mask_position"))
		this->maskPosition = Ptr<MaskPosition>(
				new MaskPosition(object.get("mask_position","").asCString()));

	if(object.isMember("file_size"))
		this->fileSize = object.get("file_size","").asInt();
}

tgbot::types::Video::Video(const Json::Value &object) :
	fileId(object.get("file_id","").asCString()),
	width(object.get("width","").asInt()),
	height(object.get("height","").asInt()),
	duration(object.get("duration","").asInt()) {

	if(object.isMember("file_size"))
		this->fileSize = object.get("file_size","").asInt();

	if(object.isMember("thumb"))
		this->thumb = Ptr<PhotoSize>(
				new PhotoSize(object.get("thumb","")));

	if(object.isMember("mime_type"))
		this->mimeType = Ptr<std::string>(
				new std::string(object.get("mime_type","").asCString()));

}

tgbot::types::Voice::Voice(const Json::Value &object) :
	fileId(object.get("file_id","").asCString()),
	duration(object.get("duration","").asInt()) {
	
	if(object.isMember("file_size"))
		this->fileSize = object.get("file_size","").asInt();

	if(object.isMember("mime_type"))
		this->mimeType = Ptr<std::string>(
				new std::string(object.get("mime_type","").asCString()));
}

tgbot::types::VideoNote::VideoNote(const Json::Value &object) :
	fileId(object.get("file_id","").asCString()),
	length(object.get("length","").asInt()),
	duration(object.get("duration","").asInt()) {
	
	if(object.isMember("file_size"))
		this->fileSize = object.get("file_size","").asInt();

	if(object.isMember("thumb"))
		this->thumb = Ptr<PhotoSize>(
				new PhotoSize(object.get("thumb","")));
}

tgbot::types::Contact::Contact(const Json::Value &object) :
	phoneNumber(object.get("phone_number","").asCString()),
	firstName(object.get("first_name","").asCString()) {
	
	if(object.isMember("last_name"))
		this->lastName = Ptr<std::string>(
				new std::string(object.get("last_name","").asCString()));

	if(object.isMember("user_id"))
		this->userId = object.get("user_id","").asInt();
}

tgbot::types::Location::Location(const Json::Value &object) :
	longitude(object.get("longitude","").asCString()),
	latitude(object.get("latitude","").asCString()) {}

tgbot::types::Venue::Venue(const Json::Value &object) :
	location(object.get("location","")),
	title(object.get("title","").asCString()),
	address(object.get("address","").asCString()) {

	if(object.isMember("foursquare_id"))
		this->fourSquareId = Ptr<std::string>(
				new std::string(object.get("foursquare_id","").asCString()));
}

tgbot::types::Invoice::Invoice(const Json::Value &object) :
	title(object.get("title","").asCString()),
	description(object.get("description","").asCString()),
	startParameter(object.get("start_parameter","").asCString()),
	currency(object.get("currency","").asCString()),
	totalAmount(object.get("total_amount","").asInt()) {}

tgbot::types::SuccessfulPayment::SuccessfulPayment(const Json::Value &object) :
	currency(object.get("currency","").asCString()),
	invoicePayload(object.get("invoice_payload","").asCString()),
	telegramPaymentChargeId(object.get("telegram_payment_charge_id","").asCString()),
	providerPaymentChargeId(object.get("provider_payment_charge_id","").asCString()),
	totalAmount(object.get("total_amount","").asInt()) {

	if(object.isMember("shipping_option_id"))
		this->shippingOptionId = Ptr<std::string>(
				new std::string(object.get("shipping_option_id","").asCString()));

	if(object.isMember("order_info"))
		this->orderInfo = Ptr<OrderInfo>(
				new OrderInfo(object.get("order_info","")));
}

tgbot::types::MessageEntity::MessageEntity(const Json::Value &object) :
	offset(object.get("offset","").asInt()),
	length(object.get("length","").asInt()) {
	
	const std::string& entityTypeStr = object.get("type","").asString();
	if(entityTypeStr == "mention")
		type = MessageEntityType::MENTION;
	else if(entityTypeStr == "hashtag")
		type = MessageEntityType::HASHTAG;
	else if(entityTypeStr == "bot_command")
		type = MessageEntityType::BOT_COMMAND;
	else if(entityTypeStr == "url")
		type = MessageEntityType::URL;
	else if(entityTypeStr == "email")
		type = MessageEntityType::EMAIL;
	else if(entityTypeStr == "bold")
		type = MessageEntityType::BOLD;
	else if(entityTypeStr == "italic")
		type = MessageEntityType::ITALIC;
	else if(entityTypeStr == "code")
		type = MessageEntityType::CODE;
	else if(entityTypeStr == "pre")
		type = MessageEntityType::PRE;
	else if(entityTypeStr == "text_link")
		type = MessageEntityType::TEXT_LINK;
	else if(entityTypeStr == "text_mention")
		type = MessageEntityType::TEXT_MENTION;

	if(object.isMember("user"))
		this->user = Ptr<User>(
				new User(object.get("user","")));

	if(object.isMember("url"))
		this->url = Ptr<std::string>(
				new std::string(object.get("url","").asCString()));
}

tgbot::types::OrderInfo::OrderInfo(const Json::Value &object) {
	if(object.isMember("shipping_address"))
		this->shippingAddress = Ptr<ShippingAddress>(
				new ShippingAddress(object.get("shipping_address","")));

	if(object.isMember("name"))
		this->name = Ptr<std::string>(
				new std::string(object.get("name","").asCString()));

	if(object.isMember("phone_number"))
		this->phoneNumber = Ptr<std::string>(
				new std::string(object.get("phone_number","").asCString()));

	if(object.isMember("email"))
		this->email = Ptr<std::string>(
				new std::string(object.get("email","").asCString()));
}

tgbot::types::StickerSet::StickerSet(const Json::Value &object) :
	name(object.get("name","").asCString()),
	title(object.get("title","").asCString()),
	stickers(std::vector<Sticker>{}),
	containsMasks(object.get("contains_masks","").asBool()) {

	for(auto const& singleSticker : object.get("stickers",""))
		stickers.emplace_back(singleSticker);
}

tgbot::types::ResponseParameters::ResponseParameters(const Json::Value &object) {
	if(object.isMember("migrate_to_chat_id"))
		this->migrateToChatId = object.get("migrate_to_chat_id","").asInt();

	if(object.isMember("retry_after"))
		this->retryAfter = object.get("retry_after","").asInt();
}

tgbot::types::File::File(const Json::Value &object) :
	fileId(object.get("file_id","").asCString()) {
	
	if(object.isMember("file_size"))
		this->fileSize = object.get("file_size","").asInt();

	if(object.isMember("file_path"))
		this->filePath = Ptr<std::string>(
				new std::string(object.get("file_path","").asCString()));
}

tgbot::types::UserProfilePhotos::UserProfilePhotos(const Json::Value &object) :
	totalCount(object.get("total_count","").asInt()) {
    const Json::Value& matArr { object.get("photos","") };
    for(ArrayIndex i=0; i < matArr.size(); i++)
        for(ArrayIndex j=0; j < matArr[i].size(); j++)
            this->photos.put(PhotoSize(matArr[i][j]),i,j);
}

std::string tgbot::types::KeyboardButton::toString() const {
	std::stringstream jsonify;
	jsonify << "{ \"text\":" << this->text
			<< "\", \"request_contact\": " << BOOL_TOSTR(this->requestContact)
			<< ", \"request_location\": " << BOOL_TOSTR(this->requestLocation)
			<< " } ";
	
	return jsonify.str();
}

tgbot::types::ChatMember::ChatMember(const Json::Value &object) :
	user(object.get("user","")),
	status(object.get("status","").asCString()),
	untilDate(object.get("until_date","").asInt()) {

	if(object.isMember("can_be_edited"))
		this->canBeEdited = object.get("can_be_edited","").asBool();
	
	if(object.isMember("can_change_info"))
		this->canChangeInfo = object.get("can_change_info","").asBool();
	
	if(object.isMember("can_post_messages"))
		this->canPostMessages = object.get("can_post_messages","").asBool();
	
	if(object.isMember("can_edit_messages"))
		this->canEditMessages = object.get("can_edit_messages","").asBool();
	
	if(object.isMember("can_delete_messages"))
		this->canDeleteMessages = object.get("can_delete_messages","").asBool();
	
	if(object.isMember("can_invite_users"))
		this->canInviteUsers = object.get("can_invite_users","").asBool();
	
	if(object.isMember("can_restrict_members"))
		this->canRestrictMembers = object.get("can_restrict_members","").asBool();
	
	if(object.isMember("can_pin_messages"))
		this->canPinMessages = object.get("can_pin_messages","").asBool();
	
	if(object.isMember("can_promote_members"))
		this->canPromoteMembers = object.get("can_promote_members","").asBool();
	
	if(object.isMember("can_send_messages"))
		this->canSendMessages = object.get("can_send_messages","").asBool();
	
	if(object.isMember("can_send_media_messages"))
		this->canSendMediaMessages = object.get("can_send_media_messages","").asBool();
	
	if(object.isMember("can_send_other_messages"))
		this->canSendOtherMessages = object.get("can_send_other_messages","").asBool();

	if(object.isMember("can_add_web_page_previews"))
		this->canAddWebPagePreviews = object.get("can_add_web_page_previews","").asBool();
}
