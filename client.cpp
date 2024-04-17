/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   client.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jquil <jquil@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/03 18:05:17 by jquil             #+#    #+#             */
/*   Updated: 2024/04/10 18:46:04 by jquil            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "IRC.hpp"

IRC::client::client(int sock, char *serv_rec, std::string mdp)
{
	//std::cout << "Default client constructor called" << std::endl;
	std::string tmp = serv_rec;
	this->sock = sock;
	int x = tmp.find("PASS");
	x += 5;
	int y = -1;
	char str[10];
	while (tmp[x] != '\r')
	{
		str[++y] = tmp[x];
		x++;
	}
	str[++y] = '\0';
	this->pass = str;
	//std::cout << this->pass << "	" << mdp << std::endl;
	if (this->pass == mdp)
		this->pass_check = 1;
	else
		this->pass_check = 0;
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

IRC::client::~client()
{
	std::cout << "Default client destructor called" << std::endl;
};
