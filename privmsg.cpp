/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   privmsg.cpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbouguet <lbouguet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/22 18:13:49 by jquil             #+#    #+#             */
/*   Updated: 2024/05/01 15:52:26 by lbouguet         ###   ########.fr       */
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
	std::cout << BOLD << BLUE << "\tIn  private_msg_chan(): " << END_C << std::endl;
	size_t	idxChan = 0;
	
	while (idxChan < this->channels.size())
	{
		if (channels[idxChan].getName() == channel)
			break;
		idxChan++;
	}

	// Is sender part of the channel ? 
	size_t i = 0;
	while(i < this->channels[idxChan].getClients().size())
	{
		if (sender.GetSock() == this->channels[idxChan].getClients()[i])
			break;
		i++;
	}

	if (i == this->channels[idxChan].getClients().size())
		return ;
	for (size_t i = 0; i < this->channels[idxChan].getClients().size(); i++)
	{
			
			std::string nick = getNameFromSock(this->channels[idxChan].getClients()[i]);
			// if(channels[idxChan].isOperator(sender))
			// {
			// 	nick = "@" + nick;
			// 	sendRPL(RPL_NAMREPLY(sender.GetNick(), channels[idxChan].getName() , nick), sender.GetSock());
			// }
			if (nick != sender.GetNick())
			{
				sendRPL(RPL_PRIVMSG(sender.GetNick(), nick, channel, msg), this->channels[idxChan].getClients()[i]);
			}
	}
}

bool	IRC::privmsg(client &clients, std::string cmd)
{
	std::string chan;
	std::string msg;
	std::string::size_type x;
	std::string::size_type doubl_point;

	std::cout << BLUE << BOLD << "\tIn privmsg()" << END_C << std::endl;
	if ((x = cmd.find("#", 0)) == std::string::npos)
		return (0);
	if ((doubl_point = cmd.find(":", 0)) == std::string::npos)
		return (0);
	std::cout << BOLD << "Check0" << END_C << std::endl;
	chan = cmd.substr(x , doubl_point - 1);
	msg = cmd.substr(doubl_point + 1, cmd.size());
	private_msg_chan(msg, clients, chan);
	std::cout << BOLD << "Check1" << END_C << std::endl;
	return (1);
}
