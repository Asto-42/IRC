/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   nick.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rencarna <rencarna@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/22 18:12:57 by jquil             #+#    #+#             */
/*   Updated: 2024/04/22 19:15:06 by rencarna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "IRC.hpp"

bool	IRC::nick(client &client, std::string cmd)
{
	if (cmd.size() == 0){
		std::string tmp = "USER";
		sendRPL(ERR_NOTENOUGHPARAM("localhost"), client.GetSock());
		return (0);
	}
	if(client.GetSetup() != 2 && client.GetSetup() != 4)
		sendRPL(ERR_NOTREGISTERED("localhost"), client.GetSock());
	else if(cmd == "")
		sendRPL(ERR_NOTENOUGHPARAM("localhost"), client.GetSock());
	else if(cmd_used_name(cmd, 1))
		sendRPL(ERR_ALREADYREGISTERED("localhost"), client.GetSock());
	else if((cmd)[0] == '#')
		sendRPL(ERR_ERRONEUSNICK("localhost"), client.GetSock());
	else{
		client.SetNick(cmd);
		client.SetSetup(3);
		return (1);
	}
}
