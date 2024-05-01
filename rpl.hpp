#pragma once

#include <string>

#define CRLF "\r\n"

#define RPL_CONNECTED(nickname) (": 001 " + nickname + " : Welcome to the IRC server!" + CRLF)
#define RPL_TOPIC(nickname, channelName, topic) (": 332 " + nickname + " " + channelName + " :" + topic + CRLF)
#define RPL_CHANGEMODE(hostname, channelname, mode, arguments) (":" + hostname + " MODE " + channelname + " " + mode + " " + arguments + CRLF)

#define ERR_NOTREGISTERED(nickname) (": 451 " + nickname + " :You have not registered!" + CRLF)
#define ERR_NOTENOUGHPARAM(nickname) (": 461 " + nickname + " :Not enough parameters given" + CRLF)
#define ERR_ALREADYREGISTERED(nickname) (": 462 " + nickname + " :You may not reregister !" + CRLF )
#define ERR_ERRONEUSNICK(nickname) (": 432 " + nickname + " :Erroneus nickname" + CRLF)
#define ERR_NONICKNAME(nickname) (": 431 " + nickname + " :No nickname given" + CRLF )
#define ERR_NOTOPERATOR(nickname) (": 482 #" + nickname + " :You're not a channel operator" + CRLF)
#define ERR_CHANNELNOTFOUND(nickname, channelname) (": 403 " + nickname + " " + channelname + " :No such channel" + CRLF)
#define ERR_CHANOPRIVSNEEDED(nickname, channelname) (": 482 " + nickname + " " + channelname + " :You're not channel operator" + CRLF)
#define ERR_NEEDMOREPARAMS(nickname, cmd) (": 461 " + nickname + " " + cmd + " :Not enough parameters" + CRLF)
#define ERR_NOTOPIC(nickname, channelname) (": 331 " + nickname + " " + channelname + " :No topic is set" + CRLF)


#define ERR_NOSUCHNICK(nickname, nonUser) (":localhost 401 " + nickname + " " + nonUser + " :no such nickname" + CRLF)
//---- Mode +i activated/deactivated
#define RPL_INVEXLIST1(nick, channel) (":localhost 346 " + nick + " " + channel + " :Invite-only mode has been activated" + CRLF)
#define RPL_INVEXLIST2(nick, channel) (":localhost 346 " + nick + " " + channel + " :Invite-only mode has been deactivated" + CRLF)

//---- /INVITE
//#define RPL_INVITE(client, invited, channel) (":localhost ")

#define RPL_INVITING(client, nick, channel) (":localhost 341 " + client + " " + nick + " " + channel + CRLF)

//#define RPL_INVITINGCHANMSG(client, chan) (":localhost 341 " + client + " " + chan + " :HEYYYYYYY" + CRLF)

#define ERR_USERONCHANNEL(client, nick, channel) (":localhost 343 " + client + " " + nick + " " + channel + " :is already on channel" + CRLF)
#define ERR_INVITEONLYCHAN(nickname, channel) (":localhost 473 " + nickname + " " + channel + " :Cannot join channel (+i)" + CRLF)


#define ERR_BADCHANNELKEY(client, channel) (":localhost 475 " + client + " " + channel + " :Cannot join channel (+k)" + CRLF)
#define ERR_CHANNELISFULL(client, channel) (":localhost 471 " + client + " " + channel + " :Cannot join channel (+l)" + "\r\n")
// #define ERR_NOTOPERATOR(channelname) (": 482 #" + channelname + " :You're not a channel operator" + CRLF)
#define RPL_NAMREPLY(client, channel, list) (":localhost 353 " + client + " = " + channel + " :" + list + CRLF)
//#define ERR_NOSUCHNICK(channelname, name) (": 401 #" + channelname + " " + name + " :No such nick/channel" + CRLF )
#define RPL_ENDOFNAMES(client, channel) (":localhost 366 " + client + " " + channel + " :End of /NAMES list" + CRLF)
#define RPL_CAPLS()(":localhost 451 * :You have not registered \r\n")
#define RPL_JOIN(nick, channelName) (":" + nick + "!" + nick + "@" + "localhost" + " JOIN " + channelName + CRLF)
#define RPL_PRIVMSG(nick, user, target, msg) (":" + nick + "!" + user + "@localhost PRIVMSG " + target + " :" + msg + CRLF)
//# define userID(nickname, username) (":" + nickname + "!" + username + "@localhost")

//#define RPL_PARTNOTICE1(client, channel) (":localhost NOTICE " + client + " :You have left the channel " + channel + CRLF)

#define RPL_PARTNOTICE1(client, channel) (":localhost NOTICE " + channel + " :" + client + " has left the channel" + CRLF)

#define RPL_PARTNOTICE2(client, channel) (":localhost NOTICE " + client + " :You're not in the channel " + channel + CRLF)