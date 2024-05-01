/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   part.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbouguet <lbouguet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/22 18:15:09 by jquil             #+#    #+#             */
/*   Updated: 2024/05/01 19:00:51 by lbouguet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "IRC.hpp"
//<< PART #testjeubnssodf
bool	IRC::part(client &client, std::string cmd)
{
	std::cout << BLUE << BOLD << "In part(): " <<  END_C << "cmd: " << cmd << std::endl;
	std::string chan;
	std::string::size_type x;

	if ((x = cmd.find("#", 0)) == std::string::npos)
	{
		std::cout << "# not found" << std::endl;
		return (0);
	}
	chan = cmd.substr(x, cmd.size());

	// do channels exit ?
	if (!this->channels.size())
		return 0;
	// find channel
	size_t idxChan = 0;
	while (idxChan < this->channels.size())
	{
		if (chan == this->channels[idxChan].getName())
			break;
		idxChan++;
	}
	if (idxChan == this->channels.size())
		return ((void)sendRPL(ERR_CHANNELNOTFOUND(client.GetNick(), chan), client.GetSock()), false);
	size_t i = 0;
	while (i < this->channels[idxChan].getClients().size())
	{
		if (client.GetSock() == this->channels[idxChan].getClients()[i])
		{
			this->channels[idxChan].getClients().erase(this->channels[idxChan].getClients().begin() + i);
			sendRPL(RPL_PART(userID(client.GetNick(), client.GetNick()), chan, "because vous puez la merde"), client.GetSock());
			// Broadcasting msg to all clients in channel
			for (size_t j = 0; j < this->channels[idxChan].getClients().size(); j++)
				sendRPL(RPL_PART(userID(client.GetNick(), client.GetNick()), chan, "because vous puez la merde"), this->channels[idxChan].getClients()[j]);
			break;
		}
		i++;
	}
	if (i == this->channels[idxChan].getClients().size())
		sendRPL(RPL_PARTNOTICE2(client.GetNick(), chan), client.GetSock());

			// JUJU tu flexes trop la
			// for (std::map<int, client>::iterator it2 = this->users.begin(); it2 != (this->users.end()); ++it2)
			// {
			// 	if (it2->second.GetUser() == clients.GetUser())
			// 	{
			// 		std::string msg;
			// 		if (it->remove_client(it2->second.GetSock()) == 0)
			// 		{
			// 			std::cout << clients.GetUser() << " is not in " << chan << std::endl;
			// 			msg = ":localhost 442 " + clients.GetNick() + chan + " :You're not on that channel";
			// 			std::cout << msg << std::endl;
			// 			send(clients.GetSock(), msg.c_str(), msg.size(), 0);
			// 			//>> :bitcoin.uk.eu.dal.net 442 jquil_ #test :You're not on that channel
			// 			return (0);
			// 		}
			// 		else
			// 		{
			// 			msg = ":" + clients.GetNick() + "!~" + clients.GetUser() + " PART " + chan;
			// 			std::cout << msg << std::endl;
			// 			send(clients.GetSock(), msg.c_str(), msg.size(), 0);
			// 		//	:jquil!~jquil@5dc0-87b-e09c-1be2-a46.210.62.ip PART #testjeubnssodf
			// 			return (true);
			// 		}
			// 	}
			// }
	std::cout << "returning false" << std::endl;
	return (false);
}
