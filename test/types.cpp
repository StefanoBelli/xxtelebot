#include <jsoncpp/json/json.h>
#include <tgbot/types.h>
#include <iostream>
#include "facility.h"

#define PARSE(what, xstring) \
	Json::Reader reader; \
	Json::Value root; \
	reader.parse(xstring,root); \
	what(root)

using namespace tgbot::types;

int main()
{
	UNIT_BEGIN("Types");

	TEST_BEGIN("TypesLocation");
	
	PARSE(Location loc,
		"{ \"longitude\": \"3.450040\", \"latitude\": \"4.56757545\" }");

	CHECK_EQ_VALUES(loc.latitude, "4.56757545");
	CHECK_EQ_VALUES(loc.longitude, "3.450040");

	TEST_END();

	TEST_BEGIN("TypesUser");

	{
		PARSE(User user,
			"{ \"first_name\": \"TestBot\", \"id\": 123456, \"is_bot\": false }");

		CHECK_EQ_VALUES(user.firstName,"TestBot");
		CHECK_EQ_VALUES(user.id,123456);
		CHECK_EQ_VALUES(user.isBot,false);
	}

	{ 
		PARSE(User user,
			"{ \"first_name\": \"TestBot\", \"id\": 123456, \"is_bot\": true }");

		CHECK_EQ_VALUES(user.firstName,"TestBot");
		CHECK_EQ_VALUES(user.id,123456);
		CHECK_EQ_VALUES(user.isBot,true);
	}
	
	{ 
		PARSE(User user,
			"{ \"first_name\": \"TestBot\", \"id\": 123456, \"is_bot\": true, \"last_name\": \"Botter\",\"username\": \"@realuserbot\", \"language_code\": \"IT\"}");

		CHECK_EQ_VALUES(user.firstName,"TestBot");
		CHECK_EQ_VALUES(user.id,123456);
		CHECK_EQ_VALUES(user.isBot,true);
		CHECK_EQ_VALUES(*user.lastName.get(),"Botter");
		CHECK_EQ_VALUES(*user.username.get(),"@realuserbot");
		CHECK_EQ_VALUES(*user.languageCode.get(),"IT");
	}

	TEST_END();

	TEST_BEGIN("TypesChatPhoto");

	PARSE(ChatPhoto chatPhoto,
		"{ \"small_file_id\": \"123456\", \"big_file_id\": \"654321\" }");

	CHECK_EQ_VALUES(chatPhoto.smallFileId, "123456");
	CHECK_EQ_VALUES(chatPhoto.bigFileId, "654321");

	TEST_END();

	TEST_BEGIN("TypesAudio");

	{
		PARSE(Audio audio,
			"{ \"file_id\": \"123456\", \"file_size\": 123456, \"duration\": 120 }");

		CHECK_EQ_VALUES(audio.fileId, "123456");
		CHECK_EQ_VALUES(audio.fileSize, 123456);
		CHECK_EQ_VALUES(audio.duration, 120);
	}

	{
		PARSE(Audio audio,
			"{ \"file_id\": \"123456\", \"file_size\": 123456, \"duration\": 120 , \"performer\": \"someone\", \"title\": \"Someone who sing\", \"mime_type\": \"audio/type\" }");

		CHECK_EQ_VALUES(audio.fileId, "123456");
		CHECK_EQ_VALUES(audio.fileSize, 123456);
		CHECK_EQ_VALUES(audio.duration, 120);
		CHECK_EQ_VALUES(*audio.performer.get(),"someone");
		CHECK_EQ_VALUES(*audio.title.get(),"Someone who sing");
		CHECK_EQ_VALUES(*audio.mimeType.get(),"audio/type");
	}
	TEST_END();

	TEST_BEGIN("TypesPhotoSize");
	
	PARSE(PhotoSize photoSize,
		"{ \"file_id\": \"123456\", \"file_size\": 123456, \"width\": 1366, \"height\": 768 }");

	CHECK_EQ_VALUES(photoSize.fileId, "123456");
	CHECK_EQ_VALUES(photoSize.fileSize,123456);
	CHECK_EQ_VALUES(photoSize.width,1366);
	CHECK_EQ_VALUES(photoSize.height,768);
	
	TEST_END();

	TEST_BEGIN("TypesVoice");
	
	{
		PARSE(Voice voice,
				"{ \"file_id\": \"123456\", \"file_size\": 123456, \"duration\": 10 }");

		CHECK_EQ_VALUES(voice.fileId, "123456");
		CHECK_EQ_VALUES(voice.fileSize,123456);
		CHECK_EQ_VALUES(voice.duration,10);
	}

	{
		PARSE(Voice voice,
				"{ \"file_id\": \"123456\", \"file_size\": 123456, \"duration\": 10, \"mime_type\": \"audio/type\"}");

		CHECK_EQ_VALUES(voice.fileId, "123456");
		CHECK_EQ_VALUES(voice.fileSize,123456);
		CHECK_EQ_VALUES(voice.duration,10);
		CHECK_EQ_VALUES(*voice.mimeType.get(),"audio/type");
	}
	
	TEST_END();

	TEST_BEGIN("TypesContact");
	{
		PARSE(Contact contact,
				"{ \"phone_number\": \"123456\", \"first_name\": \"Name\", \"user_id\": 10111213 }");

		CHECK_EQ_VALUES(contact.phoneNumber, "123456");
		CHECK_EQ_VALUES(contact.firstName,"Name");
		CHECK_EQ_VALUES(contact.userId, 10111213);
	}

	{
		PARSE(Contact contact,
				"{ \"last_name\": \"Last\", \"phone_number\": \"123456\", \"first_name\": \"Name\", \"user_id\": 10111213 }");

		CHECK_EQ_VALUES(contact.phoneNumber, "123456");
		CHECK_EQ_VALUES(contact.firstName,"Name");
		CHECK_EQ_VALUES(contact.userId, 10111213);
		CHECK_EQ_VALUES(*contact.lastName.get(), "Last");
	}
	TEST_END();

	TEST_BEGIN("TypesMaskPosition");
	PARSE(MaskPosition maskPosition,
			"{ \"point\": \"RandomPointPosition\", \"scale\": 10.0, \"x_shift\": 11.1, \"y_shift\": 11.2 }");

	CHECK_EQ_VALUES(maskPosition.point, "RandomPointPosition");
	CHECK_EQ_VALUES(maskPosition.scale, 10);
	CHECK_EQ_VALUES(maskPosition.xShift, 11.1);
	CHECK_EQ_VALUES(maskPosition.yShift, 11.2);
	TEST_END();

	TEST_BEGIN("TypesInvoice");
	PARSE(Invoice invoice,
			"{ \"title\":\"Invoice for transaction\", \"description\": \"Hydrogen bomb invoice\", \"start_parameter\": \"ParamStart\", \"currency\":\"USD\", \"total_amount\": 50000000 }");

	CHECK_EQ_VALUES(invoice.title, "Invoice for transaction");
	CHECK_EQ_VALUES(invoice.description, "Hydrogen bomb invoice");
	CHECK_EQ_VALUES(invoice.startParameter, "ParamStart");
	CHECK_EQ_VALUES(invoice.currency,"USD");
	CHECK_EQ_VALUES(invoice.totalAmount,50000000);
	TEST_END();

	TEST_BEGIN("TypesShippingAddress");
	PARSE(ShippingAddress shippingAddress,
			"{ \"country_code\": \"IT\", \"state\":\"Italy\", \"city\": \"Rome\", \"street_line_one\":\"streetLine\",\"street_line_two\": \"streetLineTwo\", \"post_code\": \"000111\"}");
	
	CHECK_EQ_VALUES(shippingAddress.countryCode,"IT");
	CHECK_EQ_VALUES(shippingAddress.state,"Italy");
	CHECK_EQ_VALUES(shippingAddress.city,"Rome");
	CHECK_EQ_VALUES(shippingAddress.streetLineOne,"streetLine");
	CHECK_EQ_VALUES(shippingAddress.streetLineTwo,"streetLineTwo");
	CHECK_EQ_VALUES(shippingAddress.postCode,"000111");
	TEST_END();

	TEST_BEGIN("TypesResponseParameters");
	PARSE(ResponseParameters responseParameters,
			"{ \"migrate_to_chat_id\": -100010001, \"retry_after\": 3 }");
	
	CHECK_EQ_VALUES(responseParameters.migrateToChatId, -100010001);
	CHECK_EQ_VALUES(responseParameters.retryAfter,3);
	TEST_END();

	TEST_BEGIN("TypesFile");
	{
		PARSE(File file,
				"{ \"file_id\": \"123456\", \"file_size\": 10000 }");
		CHECK_EQ_VALUES(file.fileId, "123456");
		CHECK_EQ_VALUES(file.fileSize, 10000);
	}
	
	{
		PARSE(File file,
				"{ \"file_path\": \"/path/to/file\", \"file_id\": \"123456\", \"file_size\": 10000 }");
		CHECK_EQ_VALUES(*file.filePath.get(), "/path/to/file");
		CHECK_EQ_VALUES(file.fileId, "123456");
		CHECK_EQ_VALUES(file.fileSize, 10000);
	}
	TEST_END();

	//KEYBOARD BUTTON NOT HERE
	
	TEST_BEGIN("TypesMessageEntity");
	{
		PARSE(MessageEntity messageEntity,
				"{ \"offset\": 10, \"length\": 11, \"type\": \"bot_command\" }");
		CHECK_EQ_VALUES(messageEntity.offset,10);
		CHECK_EQ_VALUES(messageEntity.length, 11);
		CHECK_EQ_VALUES(messageEntity.type, MessageEntityType::BOT_COMMAND);
	}
	
	{
		PARSE(MessageEntity messageEntity,
				"{ \"user\": {\"first_name\": \"name\",\"id\":100, \"is_bot\": false}, \"offset\": 10, \"length\": 11, \"type\": \"bot_command\", \"url\":\"some_url\"}");
		CHECK_EQ_VALUES(messageEntity.offset,10);
		CHECK_EQ_VALUES(messageEntity.length, 11);
		CHECK_EQ_VALUES(messageEntity.type, MessageEntityType::BOT_COMMAND);
		CHECK_EQ_VALUES(messageEntity.user.operator bool(),true);
		CHECK_EQ_VALUES(*messageEntity.url.get(),"some_url");
	}
	TEST_END();

	TEST_BEGIN("TypesDocument");
	{
		PARSE(Document document,
				"{ \"file_id\": \"111000\", \"file_size\":10000 }");

		CHECK_EQ_VALUES(document.fileId, "111000");
		CHECK_EQ_VALUES(document.fileSize, 10000);
	}
	
	{
		PARSE(Document document,
				"{ \"file_id\": \"111000\", \"file_size\":10000, \"file_name\":\"name.txt\", \"mime_type\":\"text/plain\", \"thumb\": { \"file_id\": \"111001\", \"file_size\":11111, \"width\": 100, \"height\": 10 } }");

		CHECK_EQ_VALUES(document.fileId,"111000");
		CHECK_EQ_VALUES(document.fileSize,10000);
		CHECK_EQ_VALUES(*document.fileName.get(), "name.txt");
		CHECK_EQ_VALUES(*document.mimeType.get(), "text/plain");
		CHECK_EQ_VALUES(document.thumb.operator bool(), true);
	}
	TEST_END();

	TEST_BEGIN("TypesAnimation");
	{
		PARSE(Animation animation,
				"{ \"file_id\": \"111000\", \"file_size\":10000 }");

		CHECK_EQ_VALUES(animation.fileId, "111000");
		CHECK_EQ_VALUES(animation.fileSize, 10000);
	}

	{
		PARSE(Animation animation,
				"{ \"file_id\": \"111000\", \"file_size\":10000, \"file_name\":\"name.txt\", \"mime_type\":\"text/plain\", \"thumb\": { \"file_id\": \"111001\", \"file_size\":11111, \"width\": 100, \"height\": 10 } }");

		CHECK_EQ_VALUES(animation.fileId,"111000");
		CHECK_EQ_VALUES(animation.fileSize,10000);
		CHECK_EQ_VALUES(*animation.fileName.get(), "name.txt");
		CHECK_EQ_VALUES(*animation.mimeType.get(), "text/plain");
		CHECK_EQ_VALUES(animation.thumb.operator bool(), true);
	}
	TEST_END();

	TEST_BEGIN("TypesVenue");
	{
		PARSE(Venue venue,
				"{ \"location\": { \"longitude\": \"10\", \"latitude\": \"11\" }, \"title\": \"Title\", \"address\": \"Address\" }");

		CHECK_EQ_VALUES(venue.title, "Title");
		CHECK_EQ_VALUES(venue.address,"Address");
	}

	{
		PARSE(Venue venue,
				"{ \"foursquare_id\": \"some_fsid\", \"location\": { \"longitude\": \"10\", \"latitude\": \"11\" }, \"title\": \"Title\", \"address\": \"Address\" }");

		CHECK_EQ_VALUES(*venue.fourSquareId.get(), "some_fsid");
		CHECK_EQ_VALUES(venue.title, "Title");
		CHECK_EQ_VALUES(venue.address,"Address");
	}
	TEST_END();

	TEST_BEGIN("TypesVideoNote");
	{
		PARSE(VideoNote videoNote,
				"{ \"file_id\": \"123456\", \"file_size\": 10000, \"length\": 10, \"duration\": 11 }");
		
		CHECK_EQ_VALUES(videoNote.fileId, "123456");
		CHECK_EQ_VALUES(videoNote.fileSize, 10000);
		CHECK_EQ_VALUES(videoNote.duration,11);
	}
	{
		PARSE(VideoNote videoNote,
				"{ \"file_id\": \"123456\", \"file_size\": 10000, \"length\": 10, \"duration\": 11, \"thumb\": { \"file_id\": \"111001\", \"file_size\":11111, \"width\": 100, \"height\": 10 }}");
		CHECK_EQ_VALUES(videoNote.thumb.operator bool(), true);
		CHECK_EQ_VALUES(videoNote.fileId, "123456");
		CHECK_EQ_VALUES(videoNote.fileSize, 10000);
		CHECK_EQ_VALUES(videoNote.duration,11);
	}
	TEST_END();

	TEST_BEGIN("TypesSticker");
	{
		PARSE(Sticker sticker,
				"{ \"file_id\": \"123456\", \"width\": 10, \"height\": 11, \"file_size\": 120 }");

		CHECK_EQ_VALUES(sticker.fileId, "123456");
		CHECK_EQ_VALUES(sticker.width,10);
		CHECK_EQ_VALUES(sticker.height,11);
		CHECK_EQ_VALUES(sticker.fileSize,120);
	}

	{
		PARSE(Sticker sticker,
				"{ \"emoji\": \"some_emoji_bytes\", \"set_name\": \"favset\", \"thumb\": { \"file_id\": \"123456\", \"file_size\": 123456, \"width\": 1366, \"height\": 768 }, \"file_id\":\"123456\", \"width\": 10, \"height\": 11, \"file_size\": 120, \"mask_position\": { \"point\": \"RandomPointPosition\", \"scale\": 10.0, \"x_shift\": 11.1, \"y_shift\": 11.2 }");

		CHECK_EQ_VALUES(sticker.fileId, "123456");
		CHECK_EQ_VALUES(sticker.width,10);
		CHECK_EQ_VALUES(sticker.height,11);
		CHECK_EQ_VALUES(sticker.fileSize,120);
		CHECK_EQ_VALUES(sticker.emoji.operator bool(), true);
		CHECK_EQ_VALUES(sticker.setName.operator bool(), true);
		CHECK_EQ_VALUES(sticker.thumb.operator bool(), true);
		CHECK_EQ_VALUES(sticker.maskPosition.operator bool(), true);
	}
	TEST_END();

	TEST_BEGIN("TypesVideo");
	{
		PARSE(Video video,
				"{ \"file_id\":\"123456\", \"width\": 10, \"height\": 11, \"file_size\": 120, \"duration\": 100 }");

		CHECK_EQ_VALUES(video.width, 10);
		CHECK_EQ_VALUES(video.height,11);
		CHECK_EQ_VALUES(video.fileSize,120);
		CHECK_EQ_VALUES(video.duration, 100);
		CHECK_EQ_VALUES(video.fileId, "123456");
	}

	{
		PARSE(Video video,
				"{ \"mime_type\": \"video/mp4\", \"thumb\": { \"file_id\": \"123456\", \"file_size\": 123456, \"width\": 1366, \"height\": 768 },\"file_id\":\"123456\", \"width\": 10, \"height\": 11, \"file_size\": 120, \"duration\": 100 }");

		CHECK_EQ_VALUES(video.width, 10);
		CHECK_EQ_VALUES(video.height,11);
		CHECK_EQ_VALUES(video.fileSize,120);
		CHECK_EQ_VALUES(video.duration, 100);
		CHECK_EQ_VALUES(video.fileId, "123456");
		CHECK_EQ_VALUES(video.mimeType.operator bool(), true);
		CHECK_EQ_VALUES(video.thumb.operator bool(), true);
	}
	TEST_END();

	TEST_BEGIN("TypesOrderInfo");
	{
		PARSE(OrderInfo orderInfo,
				"{}");
	}
	
	{
		PARSE(OrderInfo orderInfo,
				"{ \"name\": \"Name\", \"phone_number\": \"911\", \"email\": \"lol@lol.troll\", \"shipping_address\": { \"country_code\": \"IT\", \"state\":\"Italy\", \"city\": \"Rome\", \"street_line_one\":\"streetLine\",\"street_line_two\": \"streetLineTwo\", \"post_code\": \"000111\"}");
		
		CHECK_EQ_VALUES(orderInfo.shippingAddress.operator bool(), true);
		CHECK_EQ_VALUES(orderInfo.name.operator bool(), true);
		CHECK_EQ_VALUES(orderInfo.email.operator bool(), true);
		CHECK_EQ_VALUES(orderInfo.phoneNumber.operator bool(), true);
	}
	TEST_END();

	TEST_BEGIN("TypesSuccessfulPayment");
	{
		PARSE(SuccessfulPayment successfulPayment,
				"{ \"currency\": \"EUR\", \"invoice_payload\": \"payload\", \"telegram_payment_charge_id\": \"some_id\", \"provider_payment_charge_id\": \"some_id_prov\", \"total_amount\": 100 }");

		CHECK_EQ_VALUES(successfulPayment.invoicePayload, "payload");
		CHECK_EQ_VALUES(successfulPayment.currency, "EUR");
		CHECK_EQ_VALUES(successfulPayment.telegramPaymentChargeId,"some_id");
		CHECK_EQ_VALUES(successfulPayment.providerPaymentChargeId,"some_id_prov");
		CHECK_EQ_VALUES(successfulPayment.totalAmount,100);
	}
	 
	{
		PARSE(SuccessfulPayment successfulPayment,
				"{ \"order_info\": { \"name\": \"Name\", \"phone_number\": \"911\", \"email\": \"lol@lol.troll\", \"shipping_address\": { \"country_code\": \"IT\", \"state\":\"Italy\", \"city\": \"Rome\", \"street_line_one\":\"streetLine\",\"street_line_two\": \"streetLineTwo\", \"post_code\": \"000111\"} }, \"shipping_option_id\": \"some_id\", \"currency\": \"EUR\", \"invoice_payload\": \"payload\", \"telegram_payment_charge_id\": \"some_id\", \"provider_payment_charge_id\": \"some_id_prov\", \"total_amount\": 100 }");

		CHECK_EQ_VALUES(successfulPayment.invoicePayload, "payload");
		CHECK_EQ_VALUES(successfulPayment.currency, "EUR");
		CHECK_EQ_VALUES(successfulPayment.telegramPaymentChargeId,"some_id");
		CHECK_EQ_VALUES(successfulPayment.providerPaymentChargeId,"some_id_prov");
		CHECK_EQ_VALUES(successfulPayment.totalAmount,100);
		CHECK_EQ_VALUES(successfulPayment.shippingOptionId.operator bool(), true);
		CHECK_EQ_VALUES(successfulPayment.orderInfo.operator bool(), true);
	}
	TEST_END();

	TEST_BEGIN("TypesGame");
	{
		PARSE(Game game,
				"{ \"title\": \"MyVeryOwnGame\", \"description\": \"such a description\", \"photo\": [{ \"file_id\": \"123456\", \"file_size\": 123456, \"width\": 1366, \"height\": 768 }]}");
		CHECK_EQ_VALUES(game.title,"MyVeryOwnGame");
		CHECK_EQ_VALUES(game.description, "such a description");
		CHECK_EQ_VALUES(game.photo.at(0).fileId, "123456");
	}
	
	{
		PARSE(Game game,
				"{ \"text_entities\": [  { \"offset\": 10, \"length\": 11, \"type\": \"bot_command\"}, { \"offset\": 10, \"length\": 11, \"type\": \"bot_command\"} ],\"animation\": { \"file_id\": \"111000\", \"file_size\":10000 }, \"text\": \"some game text\", \"title\": \"MyVeryOwnGame\", \"description\": \"such a description\", \"photo\": [{ \"file_id\": \"123456\", \"file_size\": 123456, \"width\": 1366, \"height\": 768 }, { \"file_id\": \"223456\", \"file_size\": 123456, \"width\": 1366, \"height\": 768 }]}");
		CHECK_EQ_VALUES(game.title,"MyVeryOwnGame");
		CHECK_EQ_VALUES(game.description, "such a description");
		CHECK_EQ_VALUES(game.photo.at(1).fileId,"223456"); 
		CHECK_EQ_VALUES(game.animation.operator bool(), true);
		CHECK_EQ_VALUES(game.textEntities.operator bool(), true);
	}
	TEST_END();

	TEST_BEGIN("TypesGameHighScore");
	PARSE(GameHighScore gameHighScore,
			"{ \"user\": { \"first_name\": \"MyName\", \"is_bot\": false, \"id\": 1000 }, \"position\": 11, \"score\": 10000 }");

	CHECK_EQ_VALUES(gameHighScore.score,10000);
	CHECK_EQ_VALUES(gameHighScore.position,11);
	TEST_END();

	TEST_BEGIN("TypesInlineQuery");
	{
		PARSE(InlineQuery inlineQuery,
				"{ \"from\": { \"first_name\": \"MyName\", \"is_bot\": false, \"id\": 1000 }, \"id\": \"iqid\", \"query\": \"query_terms\", \"offset\": \"quoffset\" }");

		CHECK_EQ_VALUES(inlineQuery.id,"iqid");
		CHECK_EQ_VALUES(inlineQuery.query,"query_terms");
		CHECK_EQ_VALUES(inlineQuery.offset,"quoffset");
	}
	 
	{
		PARSE(InlineQuery inlineQuery,
				"{ \"location\": { \"longitude\": \"3.450040\", \"latitude\": \"4.56757545\" },\"from\": { \"first_name\": \"MyName\", \"is_bot\": false, \"id\": 1000 }, \"id\": \"iqid\", \"query\": \"query_terms\", \"offset\": \"quoffset\" }");

		CHECK_EQ_VALUES(inlineQuery.id,"iqid");
		CHECK_EQ_VALUES(inlineQuery.query,"query_terms");
		CHECK_EQ_VALUES(inlineQuery.offset,"quoffset");
		CHECK_EQ_VALUES(inlineQuery.location.operator bool(), true);
	}
	TEST_END();

	TEST_BEGIN("TypesUserProfilePhotos");
	PARSE(UserProfilePhotos userProfilePhotos,
			"{ \"total_count\": 4, \"photos\": [   [  { \"file_id\": \"123456\", \"file_size\": 123456, \"width\": 1366, \"height\": 768 }], [  { \"file_id\": \"123456\", \"file_size\": 123456, \"width\": 1366, \"height\": 768 },{ \"file_id\": \"123456\", \"file_size\": 123456, \"width\": 1366, \"height\": 768 }] ] }");

	TEST_END();

	TEST_BEGIN("TypesChosenInlineResult");
	{
		PARSE(ChosenInlineResult chosenInlineResult,
				"{ \"from\": { \"first_name\": \"MyName\", \"is_bot\": false, \"id\": 1000 }, \"result_id\": \"result\", \"query\":\"wordquery\" }");
		
		CHECK_EQ_VALUES(chosenInlineResult.resultId,"result");
		CHECK_EQ_VALUES(chosenInlineResult.query,"wordquery");
	}
	
	{
		PARSE(ChosenInlineResult chosenInlineResult,
				"{ \"inline_message_id\": \"my_id\", \"location\": { \"longitude\": \"3.450040\", \"latitude\": \"4.56757545\" }, \"from\": { \"first_name\": \"MyName\", \"is_bot\": false, \"id\": 1000 }, \"result_id\": \"result\", \"query\":\"wordquery\" }");
		
		CHECK_EQ_VALUES(chosenInlineResult.resultId,"result");
		CHECK_EQ_VALUES(chosenInlineResult.query,"wordquery");
		CHECK_EQ_VALUES(chosenInlineResult.inlineMessageId.operator bool(),true);
		CHECK_EQ_VALUES(chosenInlineResult.location.operator bool(),true);
	}
	TEST_END();
	
	TEST_BEGIN("TypesWebhookInfo")
	{
		PARSE(WebhookInfo webhookInfo,
				"{ \"url\": \"my_url\", \"pending_update_count\": 3, \"last_error_date\": 53550, \"max_connections\": 10, \"has_custom_certificate\": true }");
				
		CHECK_EQ_VALUES(webhookInfo.url, "my_url");
		CHECK_EQ_VALUES(webhookInfo.pendingUpdateCount, 3);
		CHECK_EQ_VALUES(webhookInfo.lastErrorDate, 53550);
		CHECK_EQ_VALUES(webhookInfo.maxConnections, 10);
		CHECK_EQ_VALUES(webhookInfo.hasCustomCertificate, true);
	}
	{
		PARSE(WebhookInfo webhookInfo,
				"{ \"last_error_message\": \"pork dio\", \"allowed_updates\": [ \"message\", \"inline_query\" ], \"url\": \"my_url\", \"pending_update_count\": 3, \"last_error_date\": 53550, \"max_connections\": 10, \"has_custom_certificate\": true }");
				
		CHECK_EQ_VALUES(webhookInfo.url, "my_url");
		CHECK_EQ_VALUES(webhookInfo.pendingUpdateCount, 3);
		CHECK_EQ_VALUES(webhookInfo.lastErrorDate, 53550);
		CHECK_EQ_VALUES(webhookInfo.maxConnections, 10);
		CHECK_EQ_VALUES(webhookInfo.hasCustomCertificate, true);
		CHECK_EQ_VALUES(webhookInfo.lastErrorMessage.operator bool(),true);
		CHECK_EQ_VALUES(webhookInfo.allowedUpdates.operator bool(), true);
	}
	TEST_END();
	
	TEST_BEGIN("TypesCallbackQuery");
	{
		PARSE(CallbackQuery callbackQuery,
				"{ \"from\": { \"first_name\": \"TestBot\", \"id\": 123456, \"is_bot\": true }, \"id\": \"1111\", \"chat_instance\": \"instance\" }");
				
		CHECK_EQ_VALUES(callbackQuery.id, "1111");
		CHECK_EQ_VALUES(callbackQuery.chatInstance, "instance");
	}
	
	{
		PARSE(CallbackQuery callbackQuery,
				"{ \"inline_message_id\": \"id\", \"data\": \"my_data\", \"game_short_name\":\"short\", \"from\": { \"first_name\": \"TestBot\", \"id\": 123456, \"is_bot\": true }, \"id\": \"1111\", \"chat_instance\": \"instance\" }");
				
		CHECK_EQ_VALUES(callbackQuery.id, "1111");
		CHECK_EQ_VALUES(callbackQuery.chatInstance, "instance");
		CHECK_EQ_VALUES(callbackQuery.inlineMessageId.operator bool(), true);
		CHECK_EQ_VALUES(callbackQuery.data.operator bool(), true);
		CHECK_EQ_VALUES(callbackQuery.gameShortName.operator bool(), true);
	}
	TEST_END();
	
	TEST_BEGIN("TypesShippingQuery");
	PARSE(ShippingQuery shippingQuery,
			"{\"id\": \"myId\", \"invoice_payload\": \"payload\",\"shipping_address\": { \"country_code\": \"IT\", \"state\":\"Italy\", \"city\": \"Rome\", \"street_line_one\":\"streetLine\",\"street_line_two\": \"streetLineTwo\", \"post_code\": \"000111\"}, \"from\": { \"first_name\": \"TestBot\", \"id\": 123456, \"is_bot\": true }}");
	CHECK_EQ_VALUES(shippingQuery.id, "myId");
	CHECK_EQ_VALUES(shippingQuery.invoicePayload, "payload");
	TEST_END();
	
	TEST_BEGIN("TypesPreCheckoutQuery");
	{
		PARSE(PreCheckoutQuery preCheckoutQuery,
			"{ \"shipping_option_id\": \"some_options\", \"order_info\": { \"name\": \"Name\", \"phone_number\": \"911\", \"email\": \"lol@lol.troll\", \"shipping_address\": { \"country_code\": \"IT\", \"state\":\"Italy\", \"city\": \"Rome\", \"street_line_one\":\"streetLine\",\"street_line_two\": \"streetLineTwo\", \"post_code\": \"000111\"}},\"from\": { \"first_name\": \"TestBot\", \"id\": 123456, \"is_bot\": true }, \"currency\": \"USD\", \"id\": \"myId\", \"invoice_payload\": \"payload\", \"total_amount\": 10}");
			
		CHECK_EQ_VALUES(preCheckoutQuery.currency,"USD");
		CHECK_EQ_VALUES(preCheckoutQuery.id,"myId");
		CHECK_EQ_VALUES(preCheckoutQuery.invoicePayload,"payload");
		CHECK_EQ_VALUES(preCheckoutQuery.totalAmount, 10);
		CHECK_EQ_VALUES(preCheckoutQuery.shippingOptionId.operator bool(), true);
		CHECK_EQ_VALUES(preCheckoutQuery.orderInfo.operator bool(), true)
	}
	TEST_END();
	
	UNIT_END();
}
