#pragma once

#include <string>

#define CRLF "\r\n"

#define RPL_CONNECTED(nickname) (": 001 " + nickname + " : Welcome to the IRC server!" + CRLF)

#define ERR_NOTREGISTERED(nickname) (": 451 " + nickname + " :You have not registered!" + CRLF)
#define ERR_NOTENOUGHPARAM(nickname) (": 461 " + nickname + " :Not enough parameters." + CRLF)
#define ERR_ALREADYREGISTERED(nickname) (": 462 " + nickname + " :You may not reregister !" + CRLF )
#define ERR_ERRONEUSNICK(nickname) (": 432 " + nickname + " :Erroneus nickname" + CRLF)
#define ERR_NONICKNAME(nickname) (": 431 " + nickname + " :No nickname given" + CRLF )