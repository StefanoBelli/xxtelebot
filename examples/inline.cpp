#include <string>
#include <tgbot/bot.h>
#include <tgbot/utils/make_ptr.h>
#include <iostream>
#include <sstream>

using namespace tgbot;
using namespace utils;
using namespace types;
using namespace methods;
using namespace methods::types;

void inQu(const InlineQuery Myq, const Api& api){
	tgbot::methods::types::InlineQueryResultsVector result;
	api.sendMessage(std::to_string(Myq.from.id),Myq.query);//send query
	Ptr<InlineQueryResultPhoto> ph = makePtr<InlineQueryResultPhoto>();
	std::stringstream Num;//random query id
	for(int i = 0;i<2;i++){
		ph = tgbot::utils::makePtr<tgbot::methods::types::InlineQueryResultPhoto>();
		Num<<i;
		ph->type=iqrTypePhoto;
		ph->id=Num.str();
		ph->photoUrl="myurl.jpg";
		ph->thumbUrl="myurl.jpg";
		result.push_back(std::move(ph));
	}
	try{
		api.answerInlineQuery(Myq.id,result,0,true,"","","");
	}catch(TelegramException& excp){
		std::cerr<<"Exception catched, it says:" << excp.what() << "\n";
	}
}

int main() {
	LongPollBot bot("token");
	bot.callback(inQu);
	bot.start();
	//unreachable code
}
