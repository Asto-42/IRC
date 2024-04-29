/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   privmsg.cpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: russelenc <russelenc@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/22 18:13:49 by jquil             #+#    #+#             */
/*   Updated: 2024/04/27 17:02:26 by russelenc        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "IRC.hpp"


IRC::client 						IRC::getclientfromsock(int sock){
	for(std::map<int, client>::iterator ite = this->users.begin(); ite != users.end() ; ite++)
	{
		if(ite->first == sock)
			return ite->second;
	}
	return 0;
}

void					IRC::private_msg_chan(std::string msg, client &sender, std::string channel)
{
	std::cout << BOLD << BLUE << "private_msg_chan" << END_C << std::endl;
	Channel *chanFound = NULL;
	// int isad = -1;
	// std::vector<int>		op;
	// Search for the corresponding channel object
	for (std::vector<Channel>::iterator it = this->channels.begin(); it != this->channels.end(); ++it)
	{
		if (it->getName() == channel)
			chanFound = &*it;
	}
	// op = chanFound->getOperators();
	for (size_t i = 0; i < chanFound->getClients().size(); i++)
	{
		// Only send message to destination clients
		if (chanFound->getClients()[i] != sender.GetSock())
		{
			std::string nick = getNameFromSock(chanFound->getClients()[i]);;
			// if(chanFound->isOperator(chanFound->getClients()[i]))
			// 	nick = "@" + nick;
			// std::cout << "NICK " << nick << std::endl;
			std::string tmp = ":" + sender.GetNick() + "!" + nick + "@" + "localhost" + " PRIVMSG " + channel + " :" + msg;
			sendRPL(RPL_PRIVMSG(sender.GetNick(), nick, channel, msg), chanFound->getClients()[i]);
		}
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
