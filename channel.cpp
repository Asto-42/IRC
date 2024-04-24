/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   channel.cpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jquil <jquil@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/19 17:57:58 by jquil             #+#    #+#             */
/*   Updated: 2024/04/24 14:41:47 by jquil            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "IRC.hpp"

IRC::Channel::Channel(std::string name, client &creator)
{
	std::cout << "Parametric constructor called for Channel " << this->name << " destructor called" << std::endl;
	this->name = name;
	this->operators.push_back(creator.GetSock());
	this->clients.push_back(creator.GetSock());
	this->isProtected = false;
	this->topic.clear();
	this->limitClients = 10;
}

IRC::Channel::~Channel()
{
	std::cout << "Channel " << this->name << " destructor called" << std::endl;
	return ;
}

bool						IRC::Channel::getIsProtected(void)
{
	return(this->isProtected);
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

std::vector<int>	IRC::Channel::getClients(void)
{
	return (this->clients);
}

void						IRC::Channel::setName(std::string& name)
{
	this->name = name;
}

void						IRC::Channel::setTopic(std::string& topic)
{
	this->topic = topic;
}

void						IRC::Channel::setOperators(int& operateur)
{
	this->operators.push_back(operateur);
}

int							IRC::Channel::getLimitClients(void)
{
	return (this->limitClients);
}

void							IRC::Channel::setLimitClients(int limit)
{
	this->limitClients = limit;

}

void	IRC::Channel::setClients(client& client)
{
	this->clients.push_back(client.GetSock());
}

bool	IRC::Channel::isOperator(client &client)
{
	for (std::vector<int>::iterator it = this->operators.begin(); it != this->operators.end(); ++it)
	{
		if (*it == client.GetSock())
			return (true);
	}
	return (false);
}
bool	IRC::Channel::isClient(int sock)
{
	for (std::vector<int>::iterator it = this->clients.begin(); it != this->clients.end(); ++it)
	{
		if (*it == sock)
			return (true);
	}
	return (false);
}

bool	IRC::Channel::remove_client(int sock)
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

void	IRC::Channel::private_msg_chan(std::string msg)
{
	for (std::vector<int>::iterator it = this->clients.begin(); it != this->clients.end(); ++it)
	{
		send(*it, msg.c_str(), msg.size(), 0);
	}
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
