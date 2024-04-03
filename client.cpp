/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   client.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jquil <jquil@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/03 18:05:17 by jquil             #+#    #+#             */
/*   Updated: 2024/04/03 18:54:53 by jquil            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "IRC.hpp"

IRC::client::client(int sock, char *serv_rec)
{
	std::string tmp = serv_rec;
	std::cout << "Default client constructor called" << std::endl;
	std::cout << serv_rec << std::endl;
	this->sock = sock;
	int x = tmp.find('\n');
	int z = tmp.find('\r', x);
	for (int y = x; y < z; y++)
		this->pass[y - x] = tmp[y];
	// x = tmp.find('\n', x + 1);
	// z = 0;
	// for (int y = x + 1; tmp[y] != '\n'; y++)
	// {
	// 	if (tmp[y] != '\r')
	// 		this->nick[z] = tmp[y];
	// 	z++;
	// }
	// x = tmp.find('\n', x + 1);
	// z = 0;
	// for (int y = x + 1; tmp[y] != '\n'; y++)
	// {
	// 	if (tmp[y] != '\r')
	// 		this->user[z] = tmp[y];
	// 	z++;
	// }
	std::cout << "pass = " << this->pass << std::endl;
	// std::cout << "nick = " << this->nick << std::endl;
	// std::cout << "user = " << this->user << std::endl;

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
