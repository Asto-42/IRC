/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   channel.cpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbouguet <lbouguet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/19 17:57:58 by jquil             #+#    #+#             */
/*   Updated: 2024/04/26 14:11:05 by lbouguet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "IRC.hpp"

IRC::Channel::Channel(std::string name, client &creator)
{
	std::cout << "Parametric constructor called for Channel " << this->name << " destructor called" << std::endl;
	this->name = name;
	this->operators.push_back(creator.GetSock());
	this->clients.push_back(creator.GetSock());
	this->topic.clear();
	this->modes.clear();
	this->limitClients = 10;
}

IRC::Channel::~Channel()
{
	std::cout << "Channel " << this->name << " destructor called" << std::endl;
	return ;
}

std::vector<std::string> IRC::Channel::getInvitations(void)
{
	return (this->invitations);
}

std::string IRC::Channel::getModes(void)
{
	return (this->modes);
}

std::string					IRC::Channel::getName(void)
{
	return (this->name);
}

std::string					IRC::Channel::getTopic(void)
{
	return (this->topic);
}

std::vector<int>			IRC::Channel::getOperators(void)
{
	return (this->operators);
}

std::vector<int>			IRC::Channel::getClients(void)
{
	return (this->clients);
}

void						IRC::Channel::setName(std::string& name)
{
	this->name = name;
}

void						IRC::Channel::setTopic(std::string& topic)
{
	this->topic.clear();
	this->topic = topic;
}

void						IRC::Channel::setOperators(int operateur)
{
	this->operators.push_back(operateur);
}

int							IRC::Channel::getLimitClients(void)
{
	return (this->limitClients);
}

void						IRC::Channel::setLimitClients(int limit)
{
	this->limitClients = limit;

}

void							IRC::Channel::setModes(char c)
{
	if(modes.find(c) == std::string::npos)
		modes += c;
	std::cout << "MODES STRING = " << modes << std::endl;
	return ;
}

void							IRC::Channel::delModes(char c)
{
	std::size_t position_c = modes.find(c);
	if(position_c != std::string::npos)
		modes.erase(position_c);
	std::cout << "MODES STRING = " << modes << std::endl;
	return ;
}

void	IRC::Channel::setClients(client& client)
{
	this->clients.push_back(client.GetSock());
}

bool						IRC::Channel::isOperator(client &client)
{
	for (std::vector<int>::iterator it = this->operators.begin(); it != this->operators.end(); ++it)
	{
		if (*it == client.GetSock())
			return (true);
	}
	return (false);
}
bool						IRC::Channel::isClient(int sock)
{
	for (std::vector<int>::iterator it = this->clients.begin(); it != this->clients.end(); ++it)
	{
		if (*it == sock)
			return (true);
	}
	return (false);
}

bool						IRC::Channel::remove_client(int sock)
{
	if (this->isClient(sock) == 1)
	{
		for (std::vector<int>::iterator it = this->clients.begin(); it != this->clients.end(); ++it)
		{
			if (*it == sock)
			{
				delete(&it);
				return (true);
			}
		}
	}
	return (false);
}

bool	IRC::Channel::add_client(client &new_client)
{
	if (this->isClient(new_client.GetSock()) == 0)
	{
		this->white_list.push_back(new_client.GetSock());
		std::cout << new_client.GetUser() << " successfully add to " << this->getName() << "'s white list" << std::endl;
		//add to whitelist
	}
	else
		std::cout << new_client.GetUser() << " is already in " << this->getName() << std::endl;
	return (false);
}
// bool							IRC::Channel::isOperator(int fd){
// 	for (std::vector<int>::iterator it = operators.begin(); it != operators.end(); ++it){
// 		if (*it == fd)
// 			return (true);
// 	}
// 	return (false);
// }
