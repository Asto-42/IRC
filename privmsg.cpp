/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   privmsg.cpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbouguet <lbouguet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/22 18:13:49 by jquil             #+#    #+#             */
/*   Updated: 2024/04/25 18:17:36 by lbouguet         ###   ########.fr       */
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
	// std::string::size_type end;

	std::cout << RED <<" in privmsg" << END_C << std::endl;
	std::cout << BOLD << "Check " << cmd << END_C << std::endl;
	//(void)clients;
	if ((x = cmd.find("#", 0)) == std::string::npos)
		return (0);
	if ((doubl_point = cmd.find(":", 0)) == std::string::npos)
		return (0);
	// if ((end = cmd.find("\r\n", 0)) == std::string::npos)
	// 	return (0);
	std::cout << BOLD << "Check0" << END_C << std::endl;
	chan = cmd.substr(x , doubl_point - 1);
	msg = cmd.substr(doubl_point + 1, cmd.size());
	//chan -> vector channel == chan
	// if (it->getName() == chan)
	// 	{
			private_msg_chan(msg, clients.GetNick(), chan);
	std::cout << BOLD << "Check1" << END_C << std::endl;

	//	}

	return (1);
}
