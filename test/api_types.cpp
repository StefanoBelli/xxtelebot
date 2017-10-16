#include <tgbot/methods/types.h>
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
	
	UNIT_END();
}
