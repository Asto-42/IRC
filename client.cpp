/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   client.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbouguet <lbouguet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/03 18:05:17 by jquil             #+#    #+#             */
/*   Updated: 2024/04/19 15:49:21 by lbouguet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "IRC.hpp"

IRC::client::client()
{
	this->sock = 0;
};

// Recoit la socket créé par accept, 
IRC::client::client(int sock, char *serv_rec, std::string mdp)
{
	//std::cout << "Default client constructor called" << std::endl;
	std::string tmp = serv_rec;
	this->sock = sock;
	int x = tmp.find("PASS");
	if (x <= -1)
	{
		std::cout << "Find fail ??\n" << serv_rec << std::endl;
		return ;
	}
	x += 5;
	int y = -1;
	char str[100];
	while (tmp[x] != '\r')
	{
		str[++y] = tmp[x];
		x++;
	}
	str[++y] = '\0';
	this->pass = str;
	if (this->pass == mdp)
		this->pass_check = 1;
	else
		this->pass_check = 0;
	x = tmp.find("NICK");
	x += 5;
	y = -1;
	while (tmp[x] != '\r')
	{
		str[++y] = tmp[x];
		x++;
	}
	str[++y] = '\0';
	this->nick = str;
	x = tmp.find("USER");
	x += 5;
	y = -1;
	while (tmp[x] != '\r')
	{
		str[++y] = tmp[x];
		x++;
	}
	str[++y] = '\0';
	this->user = str;
};

int IRC::client::GetSock()
{
	return (this->sock);
}


std::string IRC::client::GetPass()
{
	return (this->pass);
}

std::string IRC::client::GetNick()
{
	return (this->nick);
}

std::string IRC::client::GetUser()
{
	return (this->user);
}
