/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ping.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jquil <jquil@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/22 18:14:36 by jquil             #+#    #+#             */
/*   Updated: 2024/04/23 16:31:00 by jquil            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "IRC.hpp"

bool	IRC::ping(client &client, std::string cmd)
{
	if (cmd == "localhost")
	{
		std::string msg2 = ":localhost PONG localhost :"+ client.GetUser() + "\n--> lag pong";
		if (send(client.GetSock(), msg2.c_str(), msg2.size(), 0) > 0)
		{
			//std::cout << "PING SENDED" << std::endl;
			return (1);
		}
		std::cout << "PING failed" << std::endl;
		return (0);
	}
	else
		return (1);
}
