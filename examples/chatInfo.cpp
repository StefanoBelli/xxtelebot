#include <string>
#include <tgbot/bot.h>
#include <iostream>
using namespace tgbot;
using namespace types;
using namespace methods;
void groupInfo(const Message message, const Api& api){
    std::string ChatInfo;
    try{
        api_types::Chat GChat=api.getChat(std::to_string(message.chat.id));
        if(GChat.title){
            ChatInfo+="Title:"+*(GChat.title)+"\n";
        }
        if(GChat.username){
            ChatInfo+="Username or link:"+*(GChat.username)+"\n";
        }
        if(GChat.firstName){
            ChatInfo+="First Name:"+*(GChat.firstName)+"\n";
        }
        if(GChat.lastName){
            ChatInfo+="Last Name:"+*(GChat.lastName)+"\n";
        }
        if(GChat.description){
            ChatInfo+="Description:"+*(GChat.description)+"\n";
        }
        if(GChat.inviteLink){
            ChatInfo+="InviteLink:"+*(GChat.inviteLink)+"\n";
        }
        api.sendMessage(std::to_string(message.chat.id),ChatInfo);
    }catch(TelegramException& excp){
        std::cerr<<"Exception catched, it says:" << excp.what() << "\n";
    }
}
int main() {
    LongPollBot bot("token");
    bot.callback(groupInfo);
    bot.start();
    //unreachable code
}
