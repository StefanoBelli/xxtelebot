#include <tgbot/methods/types.h>
#include <tgbot/utils/make_ptr.h>
#include <iostream>
#include "facility.h"

using namespace tgbot::methods::types;

int main()
{
	UNIT_BEGIN("ApiTypes");
	TEST_BEGIN("TestReplyMarkupBase");
	{
		ReplyMarkup replyMarkup { "" };
		CHECK_EQ_VALUES(replyMarkup.toString(),"");
	}

	{
		ReplyMarkup replyMarkup { "{ \"some\":\"markup\" }" };
		CHECK_EQ_VALUES(replyMarkup.toString(), "{ \"some\":\"markup\" }");
	}
	
	{
		ReplyMarkup replyMarkup { std::string("") };
		CHECK_EQ_VALUES(replyMarkup.toString(),"");
	}

	{
		ReplyMarkup replyMarkup { std::string("{ \"some\":\"markup\" }") };
		CHECK_EQ_VALUES(replyMarkup.toString(), "{ \"some\":\"markup\" }");
	}
	TEST_END();
	
	TEST_BEGIN("TestInputMessageContentBase");
	{
		InputMessageContent inputMessageContent { "" };
		CHECK_EQ_VALUES(inputMessageContent.toString(),"");
	}

	{
		InputMessageContent inputMessageContent { "{ \"some\":\"markup\" }" };
		CHECK_EQ_VALUES(inputMessageContent.toString(), "{ \"some\":\"markup\" }");
	}
	
	{
		InputMessageContent inputMessageContent { std::string("") };
		CHECK_EQ_VALUES(inputMessageContent.toString(),"");
	}

	{
		InputMessageContent inputMessageContent { std::string("{ \"some\":\"markup\" }") };
		CHECK_EQ_VALUES(inputMessageContent.toString(), "{ \"some\":\"markup\" }");
	}
	TEST_END();
	
	TEST_BEGIN("TestInlineQueryResultBase");
	{
		InlineQueryResult inlineQueryResult { "" };
		CHECK_EQ_VALUES(inlineQueryResult.toString(),"");
	}

	{
		InlineQueryResult inlineQueryResult { "{ \"some\":\"markup\" }" };
		CHECK_EQ_VALUES(inlineQueryResult.toString(), "{ \"some\":\"markup\" }");
	}
	
	{
		InlineQueryResult inlineQueryResult { std::string("") };
		CHECK_EQ_VALUES(inlineQueryResult.toString(),"");
	}

	{
		InlineQueryResult inlineQueryResult { std::string("{ \"some\":\"markup\" }") };
		CHECK_EQ_VALUES(inlineQueryResult.toString(), "{ \"some\":\"markup\" }");
	}
	TEST_END();
	
	TEST_BEGIN("TestReplyKeyboardRemove");

	const ReplyMarkup& replyMarkup = ReplyKeyboardRemove();
	CHECK_EQ_VALUES(replyMarkup.toString(), "{\"remove_keyboard\": true, \"selective\": false}");
	
	TEST_END();
	
	TEST_BEGIN("TestInlineKeyboardMarkup");
	{
		InlineKeyboardButton buttonOk { .text = "OK" };
		InlineKeyboardButton buttonAbort { .text = "Abort" };
		InlineKeyboardButton buttonPayNow { .text = "Pay Now" };
		buttonPayNow.pay = true;

		std::vector<InlineKeyboardButton> firstRow;
		firstRow.push_back(std::move(buttonOk));
		firstRow.push_back(std::move(buttonAbort));

		std::vector<InlineKeyboardButton> secondRow;
		secondRow.push_back(std::move(buttonPayNow));

		InlineKeyboardMarkup keyboardMarkup;
		keyboardMarkup.inlineKeyboard.push_back(std::move(firstRow));
		keyboardMarkup.inlineKeyboard.push_back(std::move(secondRow));

		const ReplyMarkup& replyMarkup = keyboardMarkup;
		CHECK_EQ_VALUES(replyMarkup.toString(), "{ \"inline_keyboard\": [[{ \"text\": \"OK\", \"pay\": false},{ \"text\": \"Abort\", \"pay\": false}],[{ \"text\": \"Pay Now\", \"pay\": true}]}");
	}
	
	{
		InlineKeyboardButton buttonOk { .text = "OK" };
		InlineKeyboardButton buttonAbort { .text = "Abort" };
		InlineKeyboardButton buttonPayNow { .text = "Pay Now" };
		buttonPayNow.pay = true;
		buttonPayNow.url = tgbot::utils::makePtr<std::string>("my_url.com"); 
		buttonPayNow.callbackData = tgbot::utils::makePtr<std::string>("UserWantsToPayRightNow");
		buttonPayNow.switchInlineQueryCurrentChat = tgbot::utils::makePtr<std::string>("someIdentifier");
		buttonPayNow.switchInlineQuery = tgbot::utils::makePtr<std::string>("OtherIdentifier");

		std::vector<InlineKeyboardButton> firstRow;
		firstRow.push_back(std::move(buttonOk));
		firstRow.push_back(std::move(buttonAbort));

		std::vector<InlineKeyboardButton> secondRow;
		secondRow.push_back(std::move(buttonPayNow));

		InlineKeyboardMarkup keyboardMarkup;
		keyboardMarkup.inlineKeyboard.push_back(std::move(firstRow));
		keyboardMarkup.inlineKeyboard.push_back(std::move(secondRow));

		const ReplyMarkup& replyMarkup = keyboardMarkup;
		CHECK_EQ_VALUES(replyMarkup.toString(), "{ \"inline_keyboard\": [[{ \"text\": \"OK\", \"pay\": false},{ \"text\": \"Abort\", \"pay\": false}],[{ \"text\": \"Pay Now\", \"pay\": true, \"url\": \"my_url.com\", \"callback_data\": \"UserWantsToPayRightNow\", \"switch_inline_query\": \"OtherIdentifier\", \"switch_inline_query_current_chat\": \"someIdentifier\"}]}");
	}
	TEST_END();
	
	TEST_BEGIN("TestReplyKeyboardMarkup");

	KeyboardButton buttonAbort { .text = "abort" };
	buttonAbort.requestContact = true;

	std::vector<KeyboardButton> firstRow;
	firstRow.emplace_back(KeyboardButton { .text = "ok" });
	firstRow.emplace_back(KeyboardButton { .text = "not ok" });

	std::vector<KeyboardButton> secondRow;
	secondRow.push_back(std::move(buttonAbort));
	
	ReplyKeyboardMarkup replyKeyboardMarkup;
	replyKeyboardMarkup.keyboard.push_back(std::move(firstRow));
	replyKeyboardMarkup.keyboard.push_back(std::move(secondRow));
	replyKeyboardMarkup.oneTimeKeyboard = true;
	replyKeyboardMarkup.resizeKeyboard = true;

	const ReplyMarkup& replyMarkup = replyKeyboardMarkup;
	CHECK_EQ_VALUES(replyMarkup.toString(), "{ \"resize_keyboard\": true, \"one_time_keyboard\": true, \"selective\": false, [[{ \"text\": \"ok\",\"request_contact\": false,\"request_location\": false},{ \"text\": \"not ok\",\"request_contact\": false,\"request_location\": false}],[{ \"text\": \"abort\",\"request_contact\": true,\"request_location\": false}]]}");
	TEST_END();

	TEST_BEGIN("TestForceReply");

	const ReplyMarkup& replyMarkup = ForceReply();
	CHECK_EQ_VALUES(replyMarkup.toString(), "{\"force_reply\": true, \"selective\": false}");
	TEST_END();

	TEST_BEGIN("TestInputTextMessageContent");
	{
		InputTextMessageContent inputTextMessageContent;
		inputTextMessageContent.messageText = "some text";
		inputTextMessageContent.disableWebPagePreview = true;

		const InputMessageContent& inputMessageContent = inputTextMessageContent;
		CHECK_EQ_VALUES(inputMessageContent.toString(), "{ \"message_text\": \"some text\",\"disable_web_page_preview\": true}");
	}
	
	{
		InputTextMessageContent inputTextMessageContent;
		inputTextMessageContent.messageText = "some text";
		inputTextMessageContent.parseMode = ParseMode::MARKDOWN;
		inputTextMessageContent.disableWebPagePreview = false;

		const InputMessageContent& inputMessageContent = inputTextMessageContent;
		CHECK_EQ_VALUES(inputMessageContent.toString(), "{ \"message_text\": \"some text\",\"disable_web_page_preview\": false,\"parse_mode\": \"Markdown\"}");
	}
	
	{
		InputTextMessageContent inputTextMessageContent;
		inputTextMessageContent.messageText = "some text";
		inputTextMessageContent.parseMode = ParseMode::HTML;
		inputTextMessageContent.disableWebPagePreview = false;

		const InputMessageContent& inputMessageContent = inputTextMessageContent;
		CHECK_EQ_VALUES(inputMessageContent.toString(), "{ \"message_text\": \"some text\",\"disable_web_page_preview\": false,\"parse_mode\": \"HTML\"}");
	}
	TEST_END();

	TEST_BEGIN("TestInputLocationMessageContent");
	InputLocationMessageContent inputLocationMessageContent;
	inputLocationMessageContent.longitude = 10.4567;
	inputLocationMessageContent.latitude = 11.1456;

	const InputMessageContent& inputMessageContent = inputLocationMessageContent;
	CHECK_EQ_VALUES(inputMessageContent.toString(), "{ \"latitude\": 11.1456,\"longitude\": 10.4567}");
	TEST_END();

	TEST_BEGIN("TestInputContactMessageContent");
	{
		InputContactMessageContent inputContactMessageContent;
		inputContactMessageContent.firstName = "Loller";
		inputContactMessageContent.phoneNumber = "666666";
		
		const InputMessageContent& inputMessageContent = inputContactMessageContent;
		CHECK_EQ_VALUES(inputMessageContent.toString(), "{ \"phone_number\": \"666666\", \"first_name\": \"Loller\"}");
	}
	
	{
		InputContactMessageContent inputContactMessageContent;
		inputContactMessageContent.firstName = "Loller";
		inputContactMessageContent.phoneNumber = "666666";
		inputContactMessageContent.lastName = tgbot::utils::makePtr<std::string>("lolname");

		const InputMessageContent& inputMessageContent = inputContactMessageContent;
		CHECK_EQ_VALUES(inputMessageContent.toString(), "{ \"phone_number\": \"666666\", \"first_name\": \"Loller\",\"last_name\": \"lolname\"}");
	}
	TEST_END();
	
	TEST_BEGIN("TestInputVenueMessageContent");
	{
		InputVenueMessageContent inputVenueMessageContent;
		inputVenueMessageContent.title = "VenueTitle";
		inputVenueMessageContent.address = "address";
		inputVenueMessageContent.latitude = 10.113;
		inputVenueMessageContent.longitude = 11.114;

		const InputMessageContent& inputMessageContent = inputVenueMessageContent;
		CHECK_EQ_VALUES(inputMessageContent.toString(), "{ \"title\": \"VenueTitle\", \"address\":\"address\", \"latitude\": 10.113, \"longitude\": 11.114}");
	}
	
	{
		InputVenueMessageContent inputVenueMessageContent;
		inputVenueMessageContent.title = "VenueTitle";
		inputVenueMessageContent.address = "address";
		inputVenueMessageContent.latitude = 10.113;
		inputVenueMessageContent.longitude = 11.114;
		inputVenueMessageContent.foursquareId = tgbot::utils::makePtr<std::string>("some_id");

		const InputMessageContent& inputMessageContent = inputVenueMessageContent;
		CHECK_EQ_VALUES(inputMessageContent.toString(), "{ \"title\": \"VenueTitle\", \"address\":\"address\", \"latitude\": 10.113, \"longitude\": 11.114,\"foursquare_id\":\"some_id\"}");
	}
	TEST_END();
	
	UNIT_END();
}
