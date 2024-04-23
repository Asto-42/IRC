/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   kick.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jquil <jquil@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/22 18:16:05 by jquil             #+#    #+#             */
/*   Updated: 2024/04/23 18:27:24 by jquil            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "IRC.hpp"

bool	IRC::kick(client &client, std::string cmd)
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
			if (it->isOperator(client) == 1)
			{
				//if user appartient a chan -> go kick
				if (it->remove_client(user) == 0)
					std::cout << user << " is not in " << chan << std::endl;
				return (true);
			}
		}

	}
	return (false);
}
