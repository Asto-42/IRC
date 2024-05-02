/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   kick.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbouguet <lbouguet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/22 18:16:05 by jquil             #+#    #+#             */
/*   Updated: 2024/05/02 15:10:07 by lbouguet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "IRC.hpp"
//<< KICK #rgioNF jquil_ :
//>> :jquil!~jquil@5dc0-87b-e09c-1be2-a46.210.62.ip KICK #rgioNF jquil_ :jquil

bool	IRC::kick(client &client, std::string cmd)
{
	std::cout << BOLD << BLUE << "In kick()" << END_C << std::endl;
	std::string chanNam = "";
	std::string	targetNam = "";
	std::string	reason = "";
	size_t		idxChan = 0;
	int			targSock = 0;

	//----- Parsing 
	if (cmd.find("#") == std::string::npos)
		return ((void)sendRPL(ERR_NOTENOUGHPARAM(client.GetUser()), client.GetSock()), false);
	if (cmd.find(":") == std::string::npos)
		return ((void)sendRPL(ERR_NOTENOUGHPARAM(cmd.substr(cmd.find(" "), cmd.find("\r") - cmd.find(" "))), client.GetSock()), false);
	//----- Extract
	chanNam = cmd.substr(cmd.find("#"), cmd.find(" ") - cmd.find("#"));
	reason	= cmd.substr(cmd.find(":") + 1, cmd.find("\r") - cmd.find(":"));
	targetNam	= cmd.substr(cmd.find(" ") + 1, cmd.find(":") - cmd.find(" ") - 2);
	//----- Defining channel idx
	for (size_t i = 0; i <= this->channels.size(); i++)
	{
		if (i == this->channels.size())
			return (void(sendRPL(ERR_NOSUCHCHANNEL(chanNam), client.GetSock())), false);
		if (chanNam == this->channels[i].getName())
		{	
			idxChan = i;
			break ;
		}
	}
	//----- Defining target sock
	for (size_t i = 0; i <= this->channels[idxChan].getClients().size(); i++)
	{
		if (i == this->channels[idxChan].getClients().size())
			return (void(sendRPL(ERR_USERNOTINCHANNEL(client.GetNick(), client.GetNick(), chanNam), client.GetSock())), false);
		if (targetNam == getNameFromSock(this->channels[idxChan].getClients()[i]))
		{	
			targSock = this->channels[idxChan].getClients()[i];
			break ;
		}
	}
	//----- Erasing sock from channel
	//----- IRC server validation answer
	for (size_t i = 0; i < this->channels[idxChan].getClients().size(); i++)
	{
		sendRPL(RPL_KICK(userID(client.GetNick(), client.GetNick()), chanNam, targetNam, reason), this->channels[idxChan].getClients()[i]);
	}
	std::vector<int>::iterator ite;
	ite = std::find(this->channels[idxChan].getClients().begin(), this->channels[idxChan].getClients().end(), targSock);
	this->channels[idxChan].getClients().erase(ite);
	return (true);
}

// bool	IRC::kick(client &clients, std::string cmd)
// {
// 	std::string::size_type x;
// 	std::string::size_type space1;
// 	std::string::size_type doubl;
// 	if ((x = cmd.find("#", 0)) == std::string::npos)
// 		return (0);
// 	if ((space1 = cmd.find(" ", 0)) == std::string::npos)
// 		return (0);
// 	if ((doubl = cmd.find(":", 0)) == std::string::npos)
// 		return (0);
// 	chan = cmd.substr(x, space1);
// 	user = cmd.substr(space1 + 1, doubl);
// 	user = user.substr(0, user.find(" ", 0));
// 	std::cout << "START KICK ROUTINE\nchan : " << chan << "	user : " << user << std::endl;
// 	for (std::vector<Channel>::iterator it = (this->channels.begin()); it != (this->channels.end()); ++it)
// 	{
// 		if (chan == it->getName())
// 		{
// 			std::cout << "Chan name found" << std::endl;
// 			if (it->isOperator(clients) == 1)
// 			{
// 				std::cout << "Operator check achieve" << std::endl;
// 				//if user appartient a chan -> go kick
// 				for (std::map<int, client>::iterator it2 = this->users.begin(); it2 != (this->users.end()); ++it2)
// 				{
// 					if (it2->second.GetNick() == user)
// 					{
// 						std::cout << "User found in chan" << std::endl;
// 						std::string msg;
// 						if (it->remove_client(it2->second.GetSock()) == 0)
// 						{
// 							std::cout << clients.GetNick() << " is not in " << chan << std::endl;
// 							msg = ":localhost 442 " + clients.GetNick() + chan + " :You're not on that channel";
// 							std::cout << msg << std::endl;
// 							send(clients.GetSock(), msg.c_str(), msg.size(), 0);
// 							//>> :bitcoin.uk.eu.dal.net 442 jquil_ #test :You're not on that channel
// 							return (0);
// 						}
// 						else
// 						{
// 						//	msg = ":" + clients.GetNick() + "!~" + clients.GetNick() + " PART " + chan;
// 						//	std::cout << msg << std::endl;
// 						//	send(clients.GetSock(), msg.c_str(), msg.size(), 0);
// 						sendRPL(RPL_KICK(userID(clients.GetNick(), clients.GetNick()), chan, user, "because il casse les couilles"), clients.GetSock());
// 							//	:jquil!~jquil@5dc0-87b-e09c-1be2-a46.210.62.ip PART #testjeubnssodf
// 							return (true);
// 						}
// 						return (true);
// 					}
// 				}
// 			}
// 		}

// 	}
// 	return (false);
// }
