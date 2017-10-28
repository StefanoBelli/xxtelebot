#include <string>
#include <tgbot/bot.h>
#include<iostream>
using namespace tgbot;
using namespace types;
using namespace methods;

void PinMsg(const Message message, const Api& api)
{
	try
	{
		api.setChatPhoto(std::to_string(message.chat.id),"example.jpg","jpg");
	}catch(TelegramException& excp)
		{
			std::cerr<<"Exception catched, it says:" << excp.what() << "\n";
		}
}

int main() {
	LongPollBot bot("token");
	bot.callback(PinMsg);
	bot.start();
	//unreachable code
}
