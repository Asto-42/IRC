/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   part.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbouguet <lbouguet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/22 18:15:09 by jquil             #+#    #+#             */
/*   Updated: 2024/04/26 18:32:08 by jquil            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "IRC.hpp"
//<< PART #testjeubnssodf
bool	IRC::part(client &clients, std::string cmd)
{
	std::cout << "PART MODE\n\ncmd : " << cmd << std::endl;
	std::string chan;
	std::string::size_type x;
	if ((x = cmd.find("#", 0)) == std::string::npos)
	{
		std::cout << "# not found" << std::endl;
		return (0);
	}
	chan = cmd.substr(x, cmd.size());
	for (std::vector<Channel>::iterator it = (this->channels.begin()); it != (this->channels.end()); ++it)
	{
		if (chan == it->getName())
		{
			for (std::map<int, client>::iterator it2 = this->users.begin(); it2 != (this->users.end()); ++it2)
			{
				if (it2->second.GetUser() == clients.GetUser())
				{
					std::string msg;
					if (it->remove_client(it2->second.GetSock()) == 0)
					{
						std::cout << clients.GetUser() << " is not in " << chan << std::endl;
						msg = ":localhost 442 " + clients.GetNick() + chan + " :You're not on that channel";
						std::cout << msg << std::endl;
						send(clients.GetSock(), msg.c_str(), msg.size(), 0);
						//>> :bitcoin.uk.eu.dal.net 442 jquil_ #test :You're not on that channel
						return (0);
					}
					else
					{
						msg = ":" + clients.GetNick() + "!~" + clients.GetUser() + " PART " + chan;
						std::cout << msg << std::endl;
						send(clients.GetSock(), msg.c_str(), msg.size(), 0);
					//	:jquil!~jquil@5dc0-87b-e09c-1be2-a46.210.62.ip PART #testjeubnssodf
						return (true);
					}
				}
			}
		}
	}
	std::cout << "returning false" << std::endl;
	return (false);
}
