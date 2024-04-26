/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   join.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jquil <jquil@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/22 18:14:55 by jquil             #+#    #+#             */
/*   Updated: 2024/04/26 17:35:57 by jquil            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "IRC.hpp"

bool						IRC::join(client &client, std::string cmd)
{
	Channel			*chanFound = NULL;
	std::string 	chanNam("");
	std::string		rplList;

	if (cmd.empty() == 1)
		return ((void)sendRPL(ERR_NOTENOUGHPARAM(client.GetUser()), client.GetSock()), false);
	// Extract channel name and key
	if(cmd.find(' ') == std::string::npos)
		chanNam = cmd.substr(cmd.find('#'), cmd.find(' ') - cmd.find('#') - 1);
	else
		chanNam = cmd.substr(cmd.find('#'), cmd.find('\r') - cmd.find('#') - 1);
	// Does channel exists ?
	for (size_t i = 0; i < this->channels.size(); i++)
	{
		if (this->channels[i].getName() == chanNam)
			chanFound = &this->channels[i];
	}
	//Is the client already part of the channel ?
	// if (std::find(chanFound->getClientSockets().begin(), chanFound->getClientSockets().end(), client.GetSock()) != chanFound->getClientSockets().end())
	// 	return (1);
	// YES - ADD client to channel
	if (chanFound != NULL)
	{
		//std::cout << BLUE << "CHANNEL EXISTS" << END_C << std::endl;
		// Checks modes (i, k, l)
			// Invitation only
		if (chanFound->getModes().find('i') != std::string::npos)
		{
			// Checks if client has the invitation
				// No
			if (std::find(chanFound->getInvitations().begin(), chanFound->getInvitations().end(), client.GetUser()) == chanFound->getInvitations().end()) // NO
				return ((void)sendRPL(ERR_INVITEONLYCHAN(client.GetUser(), chanNam), client.GetSock()), false);
		}// Key
		if (chanFound->getModes().find('k') != std::string::npos)
		{
			if (cmd.find(" ") == std::string::npos)
				return ((void)sendRPL(ERR_BADCHANNELKEY(client.GetUser(), chanNam), client.GetSock()), false);
			std::string key = cmd.substr(cmd.find(" ") + 1, cmd.find('\r') - cmd.find(" ") - 1);
			if (key != chanFound->getModes())
				return ((void)sendRPL(ERR_BADCHANNELKEY(client.GetUser(), chanNam), client.GetSock()), false);
		}// Limit
		if (static_cast<int>(chanFound->getClients().size() + 1) > chanFound->getLimitClients())
			return ((void)sendRPL(ERR_CHANNELISFULL(client.GetUser(), chanNam), client.GetSock()), false);

		chanFound->setClients(client);
		for (size_t i = 0; i < chanFound->getClients().size(); i++)
		{
			if (std::find(chanFound->getOperators().begin(), chanFound->getOperators().end(), chanFound->getClients()[i]) != chanFound->getOperators().end())
				rplList += "@" + users[chanFound->getClients()[i]].GetNick();
			else
				rplList += users[chanFound->getClients()[i]].GetNick();
		}
		//std::vector<int> clientsVec2 = chanFound->getClients();
		//std::cout << BLUE << " 2 - JOINING CHANNEL" << END_C << std::endl;
		//for (std::vector<int>::iterator ite = clientsVec2.begin(); ite != clientsVec2.end(); ite++)
		//	std::cout << GREEN << *ite << END_C << std::endl;

		std::cout << YELLOW << rplList << END_C << std::endl;
		sendRPL(RPL_JOIN(client.GetNick(), chanNam), client.GetSock());
		sendRPL(RPL_NAMREPLY(client.GetNick(), chanNam, rplList), client.GetSock());
		sendRPL(RPL_TOPIC(client.GetNick(), chanNam, ""), client.GetSock());
		sendRPL(RPL_ENDOFNAMES(client.GetNick(), chanNam), client.GetSock());
		return (true);
	}

	// NO - CREATE channel
	Channel newChannel(chanNam, client);
	setChannels(newChannel);
	// need to check limit
	channels.push_back(newChannel);
	//std::cout << BLUE << " 1 - CHANNEL CREATED" << END_C << std::endl;
	//std::vector<int> clientsVec = newChannel.getClients();
	//for (std::vector<int>::iterator ite = clientsVec.begin(); ite != clientsVec.end(); ite++)
	//	std::cout << GREEN << *ite << END_C << std::endl;
	for (size_t i = 0; i < newChannel.getClients().size(); i++)
	{
		if (std::find(newChannel.getOperators().begin(), newChannel.getOperators().end(), newChannel.getClients()[i]) != newChannel.getOperators().end())
			rplList += "@" + users[newChannel.getClients()[i]].GetNick() + " ";
		else
			rplList += users[newChannel.getClients()[i]].GetNick() + " ";
	}
	std::cout << BLUE << rplList << END_C << std::endl;
	sendRPL(RPL_JOIN(client.GetNick(), chanNam), client.GetSock());
	sendRPL(RPL_NAMREPLY(client.GetNick(), chanNam, rplList), client.GetSock());
	sendRPL(RPL_TOPIC(client.GetNick(), chanNam, ""), client.GetSock());
	sendRPL(RPL_ENDOFNAMES(client.GetNick(), chanNam), client.GetSock());
	return (true);
}
