/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   join.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbouguet <lbouguet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/22 18:14:55 by jquil             #+#    #+#             */
/*   Updated: 2024/04/24 16:20:05 by lbouguet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "IRC.hpp"

bool						IRC::join(client &client, std::string cmd)
{
	Channel			*chanFound = NULL;
	std::string 	chanNam("");
	std::string		rplList;
	
	
	if (cmd.empty())
		return ((void)sendRPL(ERR_NOTENOUGHPARAM(client.GetNick()), client.GetSock()), false);

	// Extract channel name and key
	if(cmd.find(' ') == std::string::npos)
		chanNam = cmd.substr(cmd.find('#') + 1, cmd.find(' ') - cmd.find('#') - 1);
	else
		chanNam = cmd.substr(cmd.find('#') + 1, cmd.find('\r') - cmd.find('#') - 1);
	
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
		// Checks modes (i, k, l)
			// Invitation only
		if (chanFound->getModes().find('i') != std::string::npos)
		{
			// Checks if client has the invitation
				// No
			if (std::find(chanFound->getInvitations().begin(), chanFound->getInvitations().end(), client.GetNick()) == chanFound->getInvitations().end()) // NO
				return ((void)sendRPL(ERR_INVITEONLYCHAN(client.GetUser(), chanNam), client.GetSock()), false);
		}// Key 
		else if (chanFound->getModes().find('k') != std::string::npos)
		{
			if (cmd.find(" ") == std::string::npos)
				return ((void)sendRPL(ERR_BADCHANNELKEY(client.GetNick(), chanNam), client.GetSock()), false);
			std::string key = cmd.substr(cmd.find(" ") + 1, cmd.find('\r') - cmd.find(" ") - 1);
			if (key != chanFound->getModes())
				return ((void)sendRPL(ERR_BADCHANNELKEY(client.GetNick(), chanNam), client.GetSock()), false);
		}// Limit
		else if (static_cast<int>(chanFound->getClients().size() + 1) > chanFound->getLimitClients())
			return ((void)sendRPL(ERR_CHANNELISFULL(client.GetNick(), chanNam), client.GetSock()), false);
		else
		{
			chanFound->setClients(client);
			for (size_t i = 0; i < chanFound->getClients().size(); i++)
			{
				if (std::find(chanFound->getOperators().begin(), chanFound->getOperators().end(), chanFound->getClients()[i]) != chanFound->getOperators().end())
					rplList += "@" + users[chanFound->getClients()[i]].GetUser();
				else
					rplList += users[chanFound->getClients()[i]].GetUser();
			}
			sendRPL(RPL_NAMREPLY(client.GetNick(), chanNam, rplList), client.GetSock());
			sendRPL(RPL_TOPIC(client.GetNick(), chanNam, chanFound->getTopic()), client.GetSock());
			sendRPL(RPL_ENDOFNAMES(client.GetNick(), chanNam), client.GetSock());
			return (true);
		}
	}
	// NO - CREATE channel
	Channel newChannel(chanNam, client);
	sendRPL(RPL_NAMREPLY(client.GetNick(), chanNam, rplList), client.GetSock());
	sendRPL(RPL_TOPIC(client.GetNick(), chanNam, chanFound->getTopic()), client.GetSock());
	sendRPL(RPL_ENDOFNAMES(client.GetNick(), chanNam), client.GetSock());
	return (true);
	
}
