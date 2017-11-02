#include <string>
#include <tgbot/bot.h>
#include<iostream>
using namespace tgbot;
using namespace types;
using namespace methods;

void PinMsg(const Message message, const Api& api){

	try{
		api.sendVideo(std::to_string(message.chat.id),"example.mp4",tgbot::methods::types::FileSource::LOCAL_UPLOAD,"mp4",-1,-1,-1,"",false,-1,"");
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
