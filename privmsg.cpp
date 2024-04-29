/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   privmsg.cpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbouguet <lbouguet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/22 18:13:49 by jquil             #+#    #+#             */
/*   Updated: 2024/04/26 14:47:31 by lbouguet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "IRC.hpp"



void					IRC::private_msg_chan(std::string msg, client &sender, std::string channel)
{
	std::cout << BOLD << BLUE << "\tIn  private_msg_chan(): " << END_C << std::endl;
	size_t	idxChan = 0;
	//Channel *chanFound = NULL;
	
	// Search for the corresponding channel object
	// for (std::vector<Channel>::iterator it = this->channels.begin(); it != this->channels.end(); ++it)
	// {
	// 	if (it->getName() == channel)
	// 		chanFound = &*it;
	// }
	while (idxChan < this->channels.size())
	{
		if (channels[idxChan].getName() == channel)
			break;
		idxChan++;
	}
	for (size_t i = 0; i < this->channels[idxChan].getClients().size(); i++)
	{

			std::string nick = getNameFromSock(this->channels[idxChan].getClients()[i]);
			//std::string tmp = ":" + sender.GetNick() + "!" + nick + "@" + "localhost" + " PRIVMSG " + channel + " :" + msg;
			if (nick != sender.GetNick())
				sendRPL(RPL_PRIVMSG(sender.GetNick(), nick, channel, msg), this->channels[idxChan].getClients()[i]);
	}
}

bool	IRC::privmsg(client &clients, std::string cmd)
{
	std::string chan;
	std::string msg;
	std::string::size_type x;
	std::string::size_type doubl_point;
	// std::string::size_type end;

	std::cout << RED <<" in privmsg" << END_C << std::endl;
	std::cout << BOLD << "Check " << cmd << END_C << std::endl;
	//(void)clients;
	if ((x = cmd.find("#", 0)) == std::string::npos)
		return (0);
	if ((doubl_point = cmd.find(":", 0)) == std::string::npos)
		return (0);
	// if ((end = cmd.find("\r\n", 0)) == std::string::npos)
	// 	return (0);
	std::cout << BOLD << "Check0" << END_C << std::endl;
	chan = cmd.substr(x , doubl_point - 1);
	msg = cmd.substr(doubl_point + 1, cmd.size());
	//chan -> vector channel == chan
	// if (it->getName() == chan)
	// 	{
		private_msg_chan(msg, clients, chan);
	std::cout << BOLD << "Check1" << END_C << std::endl;

	//	}

	return (1);
}
