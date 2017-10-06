#include <tgbot/bot.h>
#include <iostream>

using namespace tgbot;
using namespace types;

void cb(const Message m, const Bot& b) {
	std::cout << "received message\n";
}

int main()
{
	Bot b("381582265:AAGF_PaNLVs-4Nso1VuuhmuB8i8bzed5z9k","cpptest", { UpdateType::MESSAGE });
	b.callback(UpdateCallback<Message>(cb));
	b.start();

	return 0;
}
