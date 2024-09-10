/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   kick.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jquil <jquil@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/22 18:16:05 by jquil             #+#    #+#             */
/*   Updated: 2024/09/10 12:35:40 by jquil            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "include/IRC.hpp"

bool	IRC::kick(client &clients, std::string cmd)
{
	std::string chan;
	std::string user;
	std::string::size_type x;
	std::string::size_type space;
	std::string::size_type end;
	if ((x = cmd.find("#", 0)) == std::string::npos)
		return (0);
	if ((space = cmd.find(" ", 0)) == std::string::npos)
		return (0);
	if ((end = cmd.find("\r\n", 0)) == std::string::npos)
		return (0);
	chan = cmd.substr(x + 1, space);
	user = cmd.substr(space + 1, end);
	for (std::vector<Channel>::iterator it = (this->channels.begin()); it != (this->channels.end()); ++it)
	{
		if (chan == it->getName())
		{
			if (it->isOperator(clients) == 1)
			{
				//if user appartient a chan -> go kick
				for (std::map<int, client>::iterator it2 = this->users.begin(); it2 != (this->users.end()); ++it2)
				{
					if (it2->second.GetUser() == user)
					{
						if (it->remove_client(it2->second.GetSock()) == 0)
							std::cout << user << " is not in " << chan << std::endl;
						return (true);
					}
				}
			}
		}

	}
	return (false);
}
