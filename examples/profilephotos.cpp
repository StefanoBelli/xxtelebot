#include <string>
#include <tgbot/bot.h>
#include <iostream>

using namespace tgbot;
using namespace types;
using namespace methods;

void numPh(const Message message, const Api& api){
	try{
		tgbot::types::UserProfilePhotos Photo=api.getUserProfilePhotos(message.from->id,0,100);;
		api.sendMessage(std::to_string(message.from->id),std::to_string(Photo.totalCount));//send the number of photos
	}catch(TelegramException& excp){
			std::cerr<<"Exception catched, it says:" << excp.what() << "\n";
		}
}

int main() {
	LongPollBot bot("token");
	bot.callback(numPh);
	bot.start();
	//unreachable code
}
