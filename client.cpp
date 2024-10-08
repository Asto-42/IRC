/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   client.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jquil <jquil@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/03 18:05:17 by jquil             #+#    #+#             */
/*   Updated: 2024/09/10 12:35:40 by jquil            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "include/IRC.hpp"

IRC::client::client()
{
	this->sock = 0;
	this->setup = 0;
};

IRC::client::client(int sock)
{
	std::cout << "Default client constructor called" << std::endl;
	this->sock = sock;
	this->setup = 0;
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

std::string	IRC::client::GetBuffer() const
{
	return this->buffer;
}

std::string	IRC::client::GetCurrentChannel() const
{
	return this->current_channel;
}

int	IRC::client::GetSetup() const
{
	return this->setup;
}

void IRC::client::SetBuffer(std::string buf)
{
	this->buffer = buf;
}

void IRC::client::SetPass(std::string pas)
{
	this->pass = pas;
}

void IRC::client::SetNick(std::string nic)
{
	this->nick = nic;
}

void IRC::client::SetUser(std::string use)
{
	this->user = use;
}

void IRC::client::SetSetup(int x)
{
	this->setup = x;
}

void IRC::client::SetCurrentChannel(std::string str)
{
	this->current_channel = str;
}
