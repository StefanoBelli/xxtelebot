#include <tgbot/bot.h>

using namespace tgbot;
using namespace types;
using namespace methods;

void cb(const Message m, const Api& a) {
	a.sendMessage(std::to_string(m.chat.id),"aa");
}

int main() {
	LongPollBot a { "478921848:AAFE5F5elKhldxQnNYydT5OH9VY9eCFnxd8" };
	a.callback(cb);
	a.start();
}

