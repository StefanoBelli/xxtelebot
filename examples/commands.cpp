#include <string>
#include <tgbot/bot.h>

using namespace tgbot;
using namespace types;
using namespace methods;
using namespace utils;

void replyHello(const Message m, const Api& api, const std::vector<std::string> args) {
	api.sendMessage(std::to_string(m.chat.id), "Hello");
}

void replyArguments(const Message m, const Api& api, const std::vector<std::string> args) {
	
	if(args.size()-1 == 0)
		api.sendMessage(std::to_string(m.chat.id), "Not enough arguments");
	else
		api.sendMessage(std::to_string(m.chat.id), "Got something from you...");
}

void triggerMe(const Message m, const Api& api, const std::vector<std::string> args) {
	api.sendMessage(std::to_string(m.chat.id), "TRIGGERED!");
}

//No command supplied
void echoBack(const Message m, const Api& api) {
	api.sendMessage(std::to_string(m.chat.id), *m.text);
}

int main() {
	LongPollBot bot("token");
	
	// using "/hello" will make this work
	// even when user sends "/helloman" for example.
	bot.callback(whenStarts, replyHello, "/hello");

	// using "/provide " will make this work
	// when user types /provide following commands
	bot.callback(whenStarts, replyArguments, "/provide ");
	
	// if any LOL is found inside the message string
	// then trigger function call
	bot.callback(whenContains, triggerMe, "LOL");

	// on simple message (unregistered command)
	// call this
	bot.callback(echoBack);

	// start bot
	bot.start();

	//unreachable code
}
