#include <tgbot/bot.h>
#include <iostream>
using namespace tgbot;
using namespace types;
using namespace methods;
void deleteMsg(const Message message, const Api& api){
  try{
    if(api.deleteMessage(std::to_string(message.chat.id),std::to_string(message.messageId))){
      api.sendMessage(std::to_string(message.chat.id),"Message deleted");
    }else{
      api.sendMessage(std::to_string(message.chat.id),"Impossible to delete the message!");
    }
  }catch(TelegramException& excp){
    api.sendMessage(std::to_string(message.chat.id),"Impossible to delete the message!");
    std::cerr<<"Exception catched, it says:" << excp.what() << "\n";
  }
}
int main() {
        LongPollBot bot("token");
        bot.callback(deleteMsg);
        bot.start();
        //unreachable code
}
