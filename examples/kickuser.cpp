#include <iostream>
#include <tgbot/bot.h>

using namespace tgbot;
using namespace types;
using namespace methods;

void kickMem(const Message message, const Api& api){
	try{
		api.kickChatMember(std::to_string(message.chat.id), message.from->id,-1);
	}catch(TelegramException& excp){
		std::cerr<<"Exception catched, it says:" << excp.what() << "\n";
		api.sendMessage(std::to_string(message.chat.id),"Could not kick this user");
	}
}

int main() {
	LongPollBot bot("token");
	bot.callback(kickMem);
	bot.start();
	//unreachable code
}
