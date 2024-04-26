/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   part.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbouguet <lbouguet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/22 18:15:09 by jquil             #+#    #+#             */
/*   Updated: 2024/04/26 17:33:50 by lbouguet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "IRC.hpp"

bool	IRC::part(client& client, std::string cmd)
{
	//std::string 					chanNam;
	//Channel							*chanFound = NULL;
	//std::vector<Channel>::iterator 	ite = channels.begin();

(void)client;
(void)cmd;
	// if (cmd.empty())
	// 	return ((void)sendRPL(ERR_NOTENOUGHPARAM(client.GetUser()), client.GetSock()), false);
	// chanNam = cmd;
	// for (ite != channels.end(); ite++)
	// {
	// 	if (ite->getName() == chanNam)
	// 	{	
	// 		chanFound = &(*ite);
	// 		break;
	// 	}
	// }
	// if (ite == channels.end())
	// 	return ((void)sendRPL(ERR_NOSUCHCHANNEL(chanNam), client.GetSock()), false);
	
	return false;
	
}