/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   channel.cpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jquil <jquil@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/19 17:57:58 by jquil             #+#    #+#             */
/*   Updated: 2024/04/19 17:58:00 by jquil            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "IRC.hpp"

IRC::Channel::Channel(std::string name, client &creator)
{
	std::cout << "Parametric constructor called for Channel " << this->name << " destructor called" << std::endl;
	this->name = name;
	this->operators.push_back(creator.GetSock());
	this->clients.push_back(creator);

}

IRC::Channel::~Channel()
{
	std::cout << "Channel " << this->name << " destructor called" << std::endl;
	return ;
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

void						IRC::Channel::setClients(client& client)
{
	this->clients.push_back(client);
}
