#include <string>
#include <tgbot/bot.h>
#include <iostream>

using namespace tgbot;
using namespace types;
using namespace methods;

void sendPhoto(const Message message, const Api& api){
	try{
		api.sendPhoto(std::to_string(message.chat.id),"example.jpg",tgbot::methods::types::FileSource::LOCAL_UPLOAD,"image","",false,-1,"");
	}catch(TelegramException& excp){
			std::cerr<<"Exception catched, it says:" << excp.what() << "\n";
		}
}

int main() {
	LongPollBot bot("token");
	bot.callback(sendPhoto);
	bot.start();
	//unreachable code
}
