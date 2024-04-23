/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   join.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbouguet <lbouguet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/22 18:14:55 by jquil             #+#    #+#             */
/*   Updated: 2024/04/23 18:40:10 by lbouguet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "IRC.hpp"

bool						IRC::join(client &client, std::string cmd)
{
	std::string 				chanNam = cmd.substr(0, cmd.find("\r") - 1);
	
	if (cmd.empty())
		return ((void)sendRPL(ERR_NOTENOUGHPARAM(client.GetNick()), client.GetSock()), false);
	
	// DOES it exists ? 
	for (size_t i = 0; i < this->channels.size(); i++)
	{
		// Yes. Adding client to the channel
		if (this->channels[i].getName() == chanNam)
		{	
			this->channels[i].setClients(client);
			return (true);
		}
	}
	// No. Creating the channel
	Channel newChan(chanNam, client);
	this->channels.push_back(newChan);
	return (true);
}
