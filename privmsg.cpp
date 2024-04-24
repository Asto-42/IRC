/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   privmsg.cpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jquil <jquil@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/22 18:13:49 by jquil             #+#    #+#             */
/*   Updated: 2024/04/24 14:36:28 by jquil            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "IRC.hpp"

//#test :Wsh magle on test ici

bool	IRC::privmsg(client &clients, std::string cmd)
{
	std::string chan;
	std::string msg;
	std::string::size_type x;
	std::string::size_type doubl_point;
	std::string::size_type end;

	(void)clients;
	if ((x = cmd.find("#", 0)) == std::string::npos)
		return (0);
	if ((doubl_point = cmd.find(":", 0)) == std::string::npos)
		return (0);
	if ((end = cmd.find("\r\n", 0)) == std::string::npos)
		return (0);
	chan = cmd.substr(x + 1, doubl_point);
	msg = cmd.substr(doubl_point + 1, end);
	//chan -> vector channel == chan
	for (std::vector<Channel>::iterator it = this->channels.begin(); it != this->channels.end(); ++it)
	{
		if (it->getName() == chan)
		{
			it->private_msg_chan(msg);
		}
	}
	return (1);
}
