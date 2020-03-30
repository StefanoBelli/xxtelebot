#include <string>
#include <tgbot/bot.h>
#include <iostream>

using namespace tgbot;
using namespace types;
using namespace methods;
using namespace methods::types;

void sendPhoto(const Message message, const Api& api){
	try{
		api.sendPhoto(std::to_string(message.chat.id),"example.jpg",FileSource::LOCAL_UPLOAD,"image/jpeg");
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
