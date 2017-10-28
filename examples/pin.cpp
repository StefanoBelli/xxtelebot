#include <string>
#include <tgbot/bot.h>
#include<iostream>
using namespace tgbot;
using namespace types;
using namespace methods;

void PinMsg(const Message message, const Api& api){
	try{
		api.pinChatMessage(std::to_string(message.chat.id), std::to_string(message.messageId),false);
	}catch(TelegramException& excp){
			std::cerr<<"Exception catched, it says:" << excp.what() << "\n";
		}
}

int main() {
	LongPollBot bot("token");
	bot.callback(PinMsg);
	bot.start();
	//unreachable code
}
