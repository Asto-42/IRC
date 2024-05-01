/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   kick.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbouguet <lbouguet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/22 18:16:05 by jquil             #+#    #+#             */
/*   Updated: 2024/05/01 19:49:33 by lbouguet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "IRC.hpp"
//<< KICK #rgioNF jquil_ :
//>> :jquil!~jquil@5dc0-87b-e09c-1be2-a46.210.62.ip KICK #rgioNF jquil_ :jquil
bool	IRC::kick(client &clients, std::string cmd)
{
	std::cout << cmd << std::endl;
	std::string chan;
	std::string user;
	std::string::size_type x;
	std::string::size_type space1;
	std::string::size_type doubl;
	if ((x = cmd.find("#", 0)) == std::string::npos)
		return (0);
	if ((space1 = cmd.find(" ", 0)) == std::string::npos)
		return (0);
	if ((doubl = cmd.find(":", 0)) == std::string::npos)
		return (0);
	chan = cmd.substr(x, space1);
	user = cmd.substr(space1 + 1, doubl);
	user = user.substr(0, user.find(" ", 0));
	std::cout << "START KICK ROUTINE\nchan : " << chan << "	user : " << user << std::endl;
	for (std::vector<Channel>::iterator it = (this->channels.begin()); it != (this->channels.end()); ++it)
	{
		if (chan == it->getName())
		{
			std::cout << "Chan name found" << std::endl;
			if (it->isOperator(clients) == 1)
			{
				std::cout << "Operator check achieve" << std::endl;
				//if user appartient a chan -> go kick
				for (std::map<int, client>::iterator it2 = this->users.begin(); it2 != (this->users.end()); ++it2)
				{
					if (it2->second.GetNick() == user)
					{
						std::cout << "User found in chan" << std::endl;
						std::string msg;
						if (it->remove_client(it2->second.GetSock()) == 0)
						{
							std::cout << clients.GetNick() << " is not in " << chan << std::endl;
							msg = ":localhost 442 " + clients.GetNick() + chan + " :You're not on that channel";
							std::cout << msg << std::endl;
							send(clients.GetSock(), msg.c_str(), msg.size(), 0);
							//>> :bitcoin.uk.eu.dal.net 442 jquil_ #test :You're not on that channel
							return (0);
						}
						else
						{
						//	msg = ":" + clients.GetNick() + "!~" + clients.GetNick() + " PART " + chan;
						//	std::cout << msg << std::endl;
						//	send(clients.GetSock(), msg.c_str(), msg.size(), 0);
						sendRPL(RPL_KICK(userID(clients.GetNick(), clients.GetNick()), chan, user, "because il casse les couilles"), clients.GetSock());
							//	:jquil!~jquil@5dc0-87b-e09c-1be2-a46.210.62.ip PART #testjeubnssodf
							return (true);
						}
						return (true);
					}
				}
			}
		}

	}
	return (false);
}
