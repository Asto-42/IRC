/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   nick.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbouguet <lbouguet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/22 18:12:57 by jquil             #+#    #+#             */
/*   Updated: 2024/05/03 16:47:53 by lbouguet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "IRC.hpp"

int IRC::cmd_used_name(std::string &name, int mode)
{
	if(mode == 1)
	{
		for(std::map<int, client>::iterator it = users.begin(); it != users.end(); it++)
		{
			if(name == it->second.GetUser())
				return (1);
		}
	}
	if(mode == 0)
	{
		for(std::map<int, client>::iterator it = users.begin(); it != users.end(); it++)
		{
			if(name == it->second.GetNick())
				return (1);
		}
	}
	return(0);
}

bool	IRC::nick(client &client, std::string cmd)
{
	std::string err = "localhost";
	if (cmd.size() == 0)
	{
		std::string tmp = "USER";
		sendRPL(ERR_NOTENOUGHPARAM(err), client.GetSock());
		return (0);
	}
	if(client.GetSetup() != 2 && client.GetSetup() != 4)
		sendRPL(ERR_NOTREGISTERED(err), client.GetSock());
	else if(cmd == "")
		sendRPL(ERR_NOTENOUGHPARAM(err), client.GetSock());
	else if(cmd_used_name(cmd, 0) == 1)
	{
		sendRPL(NICKNAMEINUSE_ERR(err), client.GetSock());
		cmd.insert(cmd.end(), '_');
		nick(client, cmd);
		return (1);
	}
	else if((cmd)[0] == '#')
		sendRPL(ERR_ERRONEUSNICK(err), client.GetSock());
	else{
		client.SetNick(cmd);
		client.SetSetup(3);
		return (1);
	}
	return (1);
}
