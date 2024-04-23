#pragma once

#include <string>

#define CRLF "\r\n"

#define RPL_CONNECTED(nickname) (": 001 " + nickname + " : Welcome to the IRC server!" + CRLF)
#define RPL_TOPIC(nickname, channelName, topic) (nickname + " " + channelName + " :" + topic + CRLF)

#define ERR_NOTREGISTERED(nickname) (": 451 " + nickname + " :You have not registered!" + CRLF)
#define ERR_NOTENOUGHPARAM(nickname) (": 461 " + nickname + " :Not enough parameters." + CRLF)
#define ERR_ALREADYREGISTERED(nickname) (": 462 " + nickname + " :You may not reregister !" + CRLF )
#define ERR_ERRONEUSNICK(nickname) (": 432 " + nickname + " :Erroneus nickname" + CRLF)
#define ERR_NONICKNAME(nickname) (": 431 " + nickname + " :No nickname given" + CRLF )
#define ERR_NOTOPERATOR(nickname) (": 482 #" + nickname + " :You're not a channel operator" + CRLF)
#define ERR_CHANNELNOTFOUND(nickname, channelname) (": 403 " + nickname + " " + channelname + " :No such channel" + CRLF)
#define ERR_CHANOPRIVSNEEDED(nickname, channelname) (": 482 " + nickname + " " + channelname + " :You're not channel operator" + CRLF)
#define ERR_NEEDMOREPARAMS(nickname, cmd) (": 461 " + nickname + " " + cmd + " :Not enough parameters" + CRLF)
