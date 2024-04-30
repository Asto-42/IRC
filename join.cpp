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


bool	isOperator(int& socket, std::vector<int> opertors)
{
	for (size_t i = 0; i < opertors.size(); i++)
	{
		if (opertors[i] == socket)
			return (true);
	}
	return (false);
}


bool						IRC::join(client &client, std::string cmd)
{
	std::string 	chanNam("");
	std::string		rplList;
	size_t				idxChan = 0;

	
	std::cout << BOLD<< "\tIn join(): " << END_C  << std::endl;
	std::cout << "Content cmd: \"" << cmd <<  "\""<< std::endl;
	if (cmd.empty())
		return ((void)sendRPL(ERR_NOTENOUGHPARAM(client.GetUser()), client.GetSock()), false);
	if (cmd.find("#") == std::string::npos)
		return (0);
	else if(cmd.find(' ') == std::string::npos)
		chanNam = cmd.substr(cmd.find('#'), cmd.find(' ') - cmd.find('#') - 1);
	else
		chanNam = cmd.substr(cmd.find('#'), cmd.find('\r') - cmd.find('#') - 1);
	while (idxChan < this->channels.size())
	{
		if (this->channels[idxChan].getName() == chanNam)
			break;
		idxChan++;
	}
	
	// ADD client to existing channel
	if (idxChan != this->channels.size())
	{
		//checking if client is already in channel
		for (size_t i = 0; i <= this->channels[idxChan].getClients().size(); i++)
		{
			if (i == this->channels[idxChan].getClients().size())
				break;
			if (client.GetSock() == this->channels[idxChan].getClients()[i])
			{	
				std::cout << YELLOW << BOLD << "ALREADY IN CHANNEL" << END_C << std::endl;
				return (false);
			}
		}
		if (this->channels[idxChan].getModes().find('i') != std::string::npos)// I
		{
			std::cout << YELLOW << "in Mode i check: " << chanNam << END_C <<std::endl;
			for (size_t i = 0; i <= this->channels[idxChan].getInvitations().size(); i++)
			{
				if (i == this->channels[idxChan].getInvitations().size())
					return ((void)sendRPL(ERR_INVITEONLYCHAN(client.GetNick(), chanNam), client.GetSock()), false);
				if (client.GetSock() == this->channels[idxChan].getInvitations()[i])
					break;
			}
		}// K
		if (this->channels[idxChan].getModes().find('k') != std::string::npos)
		{
			std::string key = cmd.substr(cmd.find(" ") + 1, cmd.find('\r') - cmd.find(" ") - 1);
			std::cout << "key entered: \"" << MAGENTA << key << END_C << "\"" << std::endl;
			std::cout << "key of channel: \"" << MAGENTA << this->channels[idxChan].getChannelPassword() << END_C << "\"" << std::endl;
			
			if (key != this->channels[idxChan].getChannelPassword())
				return ((void)sendRPL(ERR_BADCHANNELKEY(client.GetNick(), chanNam), client.GetSock()), false);
		}// L
		if (static_cast<int>(this->channels[idxChan].getClients().size() + 1) > this->channels[idxChan].getLimitClients())
			return ((void)sendRPL(ERR_CHANNELISFULL(client.GetNick(), chanNam), client.GetSock()), false);

		this->channels[idxChan].setClients(client);
		
		// RPL LIST
		for (size_t i = 0; i < this->channels[idxChan].getClients().size(); i++)
		{
			if (isOperator(this->channels[idxChan].getClients()[i], this->channels[idxChan].getOperators()) == true)
				rplList += "@" + users[this->channels[idxChan].getClients()[i]].GetNick() + " ";
			else
				rplList += users[this->channels[idxChan].getClients()[i]].GetNick() + " ";
		}
		
		//std::vector<int> clientsVec2 = this->channels[idxchan].getClients();
		//std::cout << BLUE << " 2 - JOINING CHANNEL" << END_C << std::endl;
		//for (std::vector<int>::iterator ite = clientsVec2.begin(); ite != clientsVec2.end(); ite++)
		//	std::cout << GREEN << *ite << END_C << std::endl;

		std::cout << YELLOW << rplList << END_C << std::endl;
		sendRPL(RPL_JOIN(client.GetNick(), chanNam), client.GetSock());
		sendRPL(RPL_NAMREPLY(client.GetNick(), chanNam, rplList), client.GetSock());
		//for (size_t j = 0; j < this->channels[idxChan].getClients().size(); j++)
		//	this->channels[idxChan].send_topic_rpl(RPL_TOPIC(client.GetSock(), this->channels[idxChan].getName(), this->channels[idxChan].getTopic()));
		sendRPL(RPL_TOPIC(client.GetNick(), chanNam, this->channels[idxChan].getTopic()), client.GetSock());
		sendRPL(RPL_ENDOFNAMES(client.GetNick(), chanNam), client.GetSock());
		return (true);
	}

	// NO - CREATE channel
	Channel newChannel(chanNam, client);
	newChannel.setOperators(client.GetSock());
	setChannels(newChannel);
	// need to check limit
	//channels.push_back(newChannel);
	//std::cout << BLUE << " 1 - CHANNEL CREATED" << END_C << std::endl;
	//std::vector<int> clientsVec = newChannel.getClients();
	//for (std::vector<int>::iterator ite = clientsVec.begin(); ite != clientsVec.end(); ite++)
	//	std::cout << GREEN << *ite << END_C << std::endl;
	for (size_t i = 0; i < newChannel.getClients().size(); i++)
	{
		if (isOperator(newChannel.getClients()[i], newChannel.getOperators()) == true)
			rplList += "@" + users[newChannel.getClients()[i]].GetNick() + " ";
		else
			rplList += users[newChannel.getClients()[i]].GetNick() + " ";
	}
	//std::cout << BLUE << rplList << END_C << std::endl;
	sendRPL(RPL_JOIN(client.GetNick(), chanNam), client.GetSock());
	sendRPL(RPL_NAMREPLY(client.GetNick(), chanNam, rplList), client.GetSock());
	sendRPL(RPL_TOPIC(client.GetNick(), chanNam, ""), client.GetSock());
	sendRPL(RPL_ENDOFNAMES(client.GetNick(), chanNam), client.GetSock());
	return (true);
}
