/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   invite.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jquil <jquil@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/22 18:16:25 by jquil             #+#    #+#             */
/*   Updated: 2024/04/23 19:00:45 by jquil            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "IRC.hpp"

bool	IRC::invite(client &clients, std::string cmd)
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
				//if user existe, add au chan
				for (std::map<int, client>::iterator it2 = this->users.begin(); it2 != this->users.end(); it2++)
				{
					if (it2->second.GetUser() == user)
					{
						it->add_client(it2->second);
						return (true);
					}
					return (false);
				}
			}
		}

	}
	return (false);
}
