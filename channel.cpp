/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   channel.cpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbouguet <lbouguet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/19 17:57:58 by jquil             #+#    #+#             */
/*   Updated: 2024/04/24 14:39:31 by lbouguet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "IRC.hpp"

IRC::Channel::Channel(std::string name, client &creator)
{
	std::cout << "Parametric constructor called for Channel " << this->name << " destructor called" << std::endl;
	this->name = name;
	this->operators.push_back(creator.GetSock());
	this->clients.push_back(creator);
	this->clientSockets.push_back(creator.GetSock());
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

std::vector<IRC::client>	IRC::Channel::getClients(void)
{
	return (this->clients);
}

std::vector<int>		IRC::Channel::getClientSockets(void)
{
	return (this->clientSockets);
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

void							IRC::Channel::setClients(client& client)
{
	this->clients.push_back(client);
}

void							IRC::Channel::setClientSockets(int Socket)
{
	this->clientSockets.push_back(Socket);

}
// bool							IRC::Channel::isOperator(int fd){
// 	for (std::vector<Client>::iterator it = operators.begin(); it != operators.end(); ++it){
// 		if (it->GetFd() == fd)
// 			return (true);
// 	}
// 	return (false);
// }
