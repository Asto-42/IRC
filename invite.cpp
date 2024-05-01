/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   invite.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbouguet <lbouguet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/22 18:16:25 by jquil             #+#    #+#             */
/*   Updated: 2024/05/01 12:42:01 by lbouguet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "IRC.hpp"

bool	IRC::invite(client &client, std::string cmd)
{
	std::cout << BOLD << "\tIn invite(): " << END_C << std::endl;
	std::string chan;
	std::string user;
	size_t		idxChan = 0;
	int 		socketInvited;

	std::cout << "cmd :" << cmd << std::endl;
	if (cmd.find("#") == std::string::npos)
		return (0);
	std::cout << "CHECK0" << std::endl;
	if (cmd.find(" ") == std::string::npos)
		return (0);
	std::cout << "CHECK1" << std::endl;
	// if ((end = cmd.find("\r\n")) == std::string::npos)
	// 	return (0);
	std::cout << "CHECK2" << std::endl;
	chan = cmd.substr(cmd.find('#'), cmd.find(' ') - cmd.find('#'));
	std::cout << "chan: \"" << MAGENTA << chan << END_C << "\"" << std::endl;
	user = cmd.substr(0, cmd.find('#') - 1);
	std::cout << "user: \"" << MAGENTA << user << END_C << "\"" << std::endl;
	
	while (idxChan < this->channels.size())
	{
		if (chan == this->channels[idxChan].getName())
			break;
		idxChan++;
	}
	if (idxChan == this->channels.size())
		return ((void)sendRPL(ERR_CHANNELNOTFOUND(client.GetNick(), chan), client.GetSock()), false);
	
	//is the client operator of the channel ?
	for (size_t i = 0; i <= this->channels[idxChan].getOperators().size(); i++)
	{
		if (i == this->channels[idxChan].getOperators().size())
			return ((void)sendRPL(ERR_CHANOPRIVSNEEDED(client.GetNick(), chan), client.GetSock()), false);
		if (client.GetSock() == this->channels[idxChan].getOperators()[i])
			break;
	}

	// add user to invitations
	if ((socketInvited = getSockFromName(user)) == -1)
		return ((void)sendRPL(ERR_NOSUCHNICK(client.GetNick(), user), client.GetSock()), false);
	// checking if the user being invited is already in invitations
	for (size_t i = 0; i <= this->channels[idxChan].getInvitations().size(); i++)
	{
		if (i == this->channels[idxChan].getInvitations().size())
			break;
		if (socketInvited == this->channels[idxChan].getInvitations()[i])
			return ((void)sendRPL(ERR_USERONCHANNEL(client.GetNick(), user, chan), client.GetSock()), false);
	}
			//sendRPL(RPL_INVITINGCHANMSG(client.GetNick(), chan), client.GetSock());
	this->channels[idxChan].setInvitations(socketInvited);
	return ((void)sendRPL(RPL_INVITING(client.GetNick(), user, chan), client.GetSock()), false);
	return (false);
}
