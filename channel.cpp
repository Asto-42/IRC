/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   channel.cpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jquil <jquil@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/19 17:57:58 by jquil             #+#    #+#             */
/*   Updated: 2024/04/23 19:36:32 by jquil            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "IRC.hpp"

IRC::Channel::Channel(std::string name, client &creator)
{
	std::cout << "Parametric constructor called for Channel " << this->name << " destructor called" << std::endl;
	this->name = name;
	this->operators.push_back(creator.GetSock());
	this->clients.push_back(creator);
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

std::vector<IRC::client>	IRC::Channel::getClients(void)
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

void						IRC::Channel::setClients(client& client)
{
	this->clients.push_back(client);
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
bool	IRC::Channel::isClient(std::string user)
{
	for (std::vector<client>::iterator it = this->clients.begin(); it != this->clients.end(); ++it)
	{
		if (it->GetUser() == user)
			return (true);
	}
	return (false);
}

bool	IRC::Channel::remove_client(client &new_client)
{
	if (this->isClient(new_client.GetUser()) == 1)
	{
		for (std::vector<client>::iterator it = this->clients.begin(); it != this->clients.end(); ++it)
		{
			if (it->GetSock() == new_client.GetSock())
				delete(&it);
		}
		for (std::vector<int>::iterator it = this->white_list.begin(); it != this->white_list.end(); ++it)
		{
			if (*it == new_client.GetSock())
			{
				delete(&it);
			}
		}
	}

	return (false);
}

bool	IRC::Channel::add_client(client &new_client)
{
	if (this->isClient(new_client.GetUser()) == 0)
	{
		this->white_list.push_back(new_client.GetSock());
		std::cout << new_client.GetUser() << " successfully add to " << this->getName() << "'s white list" << std::endl;
		//add to whitelist
	}
	else
		std::cout << new_client.GetUser() << " is already in " << this->getName() << std::endl;
	return (false);
}
