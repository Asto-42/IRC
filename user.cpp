/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   user.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jquil <jquil@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/22 18:13:25 by jquil             #+#    #+#             */
/*   Updated: 2024/04/22 18:25:47 by jquil            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "IRC.hpp"

bool	IRC::user(client &client, std::string cmd)
{
	std::cout << client.GetSetup() << std::endl;
	if (client.GetSetup() != 3)
		return (0);
	client.SetUser(cmd);
	client.SetSetup(4);
	std::string					msg;
	std::string					name;
	msg = ":localhost 001 " + client.GetNick() + " :Welcome to SUUUUUServer " + client.GetNick() + "!~" + client.GetUser() + "@127.0.0.1\r\n";
	if (send(client.GetSock(), msg.c_str(), msg.size(), 0) < 1)
	{
		//del_user(client.getFd());
		return (0);
	}
	return (1);
}