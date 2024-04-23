/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   channel.cpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbouguet <lbouguet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/19 17:57:58 by jquil             #+#    #+#             */
/*   Updated: 2024/04/23 17:06:55 by lbouguet         ###   ########.fr       */
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

// bool							IRC::Channel::isOperator(int fd){
// 	for (std::vector<Client>::iterator it = operators.begin(); it != operators.end(); ++it){
// 		if (it->GetFd() == fd)
// 			return (true);
// 	}
// 	return (false);
// }
