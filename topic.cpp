/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   topic.cpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbouguet <lbouguet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/22 18:15:23 by jquil             #+#    #+#             */
/*   Updated: 2024/04/23 17:22:16 by lbouguet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "IRC.hpp"

bool						IRC::topic(client &client, std::string cmd)
{
	std::string				err = "localhost";
	std::string 			topicNam;
	std::string 			chanNam;
	std::string::size_type 	posHash = cmd.find('#');
	std::string::size_type 	posSpace = cmd.find(posHash, ' ');
	std::string::size_type 	posColon = cmd.find(posSpace, ':');
	

	if (cmd.empty())
		return ((void)sendRPL(ERR_NOTENOUGHPARAM(err), client.GetSock()), false);
	
	// Need '#'
	if (posHash == std::string::npos)
		return ((void)sendRPL(ERR_NOTENOUGHPARAM(err), client.GetSock()), false);
	
	// Extracting channel name from cmd
	chanNam = cmd.substr(posHash, posSpace - posHash - 1);
	
	// Checking existence of channel
	size_t					i = 0;
	while (i < this->channels.size() || this->channels[i].getName() != chanNam)
		i++;
	
	// Not found channel
	if (i == 10)
		return ((void)sendRPL(ERR_CHANNELNOTFOUND(cmd, chanNam), client.GetSock()), false);

	// No topic specified
	if (posColon == std::string::npos)
		return ((void)sendRPL(RPL_TOPIC(client.GetNick(), this->channels[i].getName(), this->channels[i].getTopic()), client.GetSock()), false);
	
	// Extracting topic name from cmd
	topicNam = cmd.substr(posColon + 1, cmd.size() - posColon - 1);
	
	// Checking if the channel's topic is protected
	if (this->channels[i].getIsProtected())
	{
		//if Yes, does the client has the right to change the topic ?
		for (size_t i = 0; i < this->channels[i].getOperators().size(); i++)
		{	
			//if Yes, change the channel's topic
			if (this->channels[i].getOperators()[i] == client.GetSock())
			{	
				this->channels[i].setTopic(topicNam);
				return (true);
			}
		}
		return ((void)sendRPL(ERR_CHANOPRIVSNEEDED(client.GetNick(), this->channels[i].getName()), client.GetSock()), false);
	}
	else
	{	
		this->channels[i].setTopic(topicNam);
		return (true);
	}
	return (false);
}	