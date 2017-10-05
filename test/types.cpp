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
	
	UNIT_END();
}
