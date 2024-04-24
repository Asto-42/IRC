/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   join.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbouguet <lbouguet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/22 18:14:55 by jquil             #+#    #+#             */
/*   Updated: 2024/04/24 14:38:34 by lbouguet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "IRC.hpp"

// bool						IRC::join(client &client, std::string cmd)
// {
// 	Channel			*chanFound = NULL;
// 	std::string 	chanNam("");
	
	
// 	if (cmd.empty())
// 		return ((void)sendRPL(ERR_NOTENOUGHPARAM(client.GetNick()), client.GetSock()), false);

// 	// Extract channel name and key
// 	chanNam = cmd.substr(cmd.find('#') + 1, cmd.find('\r') - cmd.find('#') - 1);
	
// 	// Does channel exists ? 
// 	for (size_t i = 0; i < this->channels.size(); i++)
// 	{
// 		if (this->channels[i].getName() == chanNam)	
// 			chanFound = &this->channels[i];
// 	}
	
// 	//Is the client already part of the channel ?
// 	// if (std::find(chanFound->getClientSockets().begin(), chanFound->getClientSockets().end(), client.GetSock()) != chanFound->getClientSockets().end())
// 	// 	return (1);
		
// 	// YES - ADD client to channel 
// 	if (chanFound != NULL)
// 	{
// 		// Checks modes (i, k, l)
// 			// Invitation only
// 		if (chanFound->getModes().find('i') != std::string::npos)
// 		{
// 			// Checks if client has the invitation
// 				// No
// 			if (std::find(chanFound->getInvitations().begin(), chanFound->getInvitations().end(), client.GetNick()) == chanFound->getInvitations().end()) // NO
// 				return ((void)sendRPL(ERR_INVITEONLYCHAN(client.GetNick(), chanNam), client.GetSock()), false);
// 		}// Key 
// 		else if (chanFound->getModes().find('k') != std::string::npos)
// 		{
// 			if (cmd.find(" ") == std::string::npos)
// 				return ((void)sendRPL(ERR_BADCHANNELKEY(client.GetNick(), chanNam), client.GetSock()), false);
// 			std::string key = cmd.substr(cmd.find(" ") + 1, cmd.find('\r') - cmd.find(" ") - 1);
// 			if (key != chanFound->getModes())
// 				return ((void)sendRPL(ERR_BADCHANNELKEY(client.GetNick(), chanNam), client.GetSock()), false);
// 		}// Limit
// 		else if (chanFound->getClientSockets().size() + 1 > chanFound->getLimitClients())
// 			return ((void)sendRPL(ERR_CHANNELISFULL(client.GetNick(), chanNam), client.GetSock()), false);
// 		else
// 		{
// 			chanFound->setClients(client);
// 			chanFound->setClientSockets(client.GetSock());
// 			sendRPL(RPL_TOPIC(client.GetNick(), chanNam, chanFound->getTopic()), client.GetSock());
// 			sendRPL(RPL_NAMREPLY(client.GetNick(), chanNam, chanFound->getClients()), client.GetSock());
// 			return (true);
// 		}
// 	}
	
// 			chanFound->setClients(client);
// 			chanFound->setClientSockets(client.GetSock());
// 			return (true);


	
	// for (size_t i = 0; i < this->channels.size(); i++)
	// {
	// 	// Yes
	// 	if (this->channels[i].getName() == chanNam)r
	// 	{	
	// 		// Is this channel is on invitation only ?
	// 		if (this->channels[i].getIsPrivate()) // PRIVATE
	// 		{
	// 			// Does the client has the inviations ?
	// 			for (size_t i = 0; i < client.GetChannelsInvitations().size(); i++)
	// 			{
	// 				// Yes
	// 				if (client.GetChannelsInvitations()[i] == chanNam)
	// 				{
	// 					// Adding the client to the channel
	// 					if (client.GetChannelsInvitations()[i] == chanNam)
	// 					{
	// 						this->channels[i].setClients(client);
	// 						this->channels[i].setClientSockets(client.GetSock());
	// 						return (true);
	// 					}
	// 				}
	// 				else
	// 				{
	// 					// No
	// 					return ((void)sendRPL(ERR_INVITEONLYCHAN(client.GetNick(), chanNam), client.GetSock()), false);
	// 				}
	// 			}
	// 		}
	// 		}
	// 		else // PUBLIC
	// 		{
	// 			// Adding the client to the channel
	// 			this->channels[i].setClients(client);
	// 			this->channels[i].setClientSockets(client.GetSock());
	// 			return (true);
	// 		}
	// }
	// else 
	// {	
	// 	// No. Creating the channel
	// 	Channel newChan(chanNam, client);
	// 	this->channels.push_back(newChan);
	// 	// Adding the client to the channel
	// 	this->channels.back().setClients(client);
	// 	this->channels.back().setClientSockets(client.GetSock());
	// 	// Setting the client as operator
	// 	this->channels.back().setOperators(client.GetSock());
	// 	return (true);
	// }
	// return (true);
//}
