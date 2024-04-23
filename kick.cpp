/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   kick.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jquil <jquil@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/22 18:16:05 by jquil             #+#    #+#             */
/*   Updated: 2024/04/23 17:20:38 by jquil            ###   ########.fr       */
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
	(void)client;
	//if (client.GetOperStat() == 1 && chan.GetUserStat == 1)
		//chan.remove(chan.clients.find(user));
	//else
	return (0);
}
