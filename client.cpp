/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   client.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbouguet <lbouguet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/03 18:05:17 by jquil             #+#    #+#             */
/*   Updated: 2024/04/22 12:23:28 by lbouguet         ###   ########.fr       */
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
	std::cout << "Default client constructor called" << std::endl;
	std::string tmp = serv_rec;
	this->sock = sock;
	int x = 0;
	std::cout << "\tServ_rec value \n" << serv_rec << std::endl << "\tEND serv_rec value " << std::endl;
	x = tmp.find("PASS");
	std::cout << "find() return value " << tmp.find("PASS") << std::endl;
	if (tmp.find("PASS") == std::string::npos)
	{
		std::cout << "Find fail ??\n" << serv_rec << std::endl;
		return ;
	}

	// Skipping "PASS"
	x += 5;
	int y = -1;
	char str[100];
	memset(str, 0, 100);
	while (tmp[x] != '\r')
	{
		str[++y] = tmp[x];
		x++;
	}
	
	str[++y] = '\0';
	std::cout << "FIND MDP PARSING: " << str << std::endl;
	this->pass = str;
	std::cout <<  "MDP IN PASS: " << pass << std::endl; 
	if (this->pass == mdp)
		this->pass_check = 1;
	else
		this->pass_check = 0;
	std::cout <<  "pass_check = " << pass_check << std::endl; 
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
