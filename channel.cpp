/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   channel.cpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbouguet <lbouguet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/19 17:57:58 by jquil             #+#    #+#             */
/*   Updated: 2024/05/01 12:33:15 by lbouguet         ###   ########.fr       */
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
	this->channelPassword = "";
}

IRC::Channel::~Channel()
{
	std::cout << "Channel " << this->name << " destructor called" << std::endl;
	return ;
}

//-------------------- Utils ------------------------------------------------//
void				IRC::Channel::setInvitations(int &socket)
{
	invitations.push_back(socket);
}

bool				IRC::Channel::isOperator(client &client)
{
	for (std::vector<int>::iterator it = this->operators.begin(); it != this->operators.end(); ++it)
	{
		if (*it == client.GetSock())
			return (true);
	}
	return (false);
}

bool				IRC::Channel::isOperator(int sock)
{
	for (std::vector<int>::iterator it = this->operators.begin(); it != this->operators.end(); ++it)
	{
		if (*it == sock)
			return (true);
	}
	return (false);
}

bool				IRC::Channel::isClient(int sock)
{
	for (std::vector<int>::iterator it = this->clients.begin(); it != this->clients.end(); ++it)
	{
		if (*it == sock)
			return (true);
	}
	return (false);
}

bool				IRC::Channel::remove_client(int sock)
{
	if (this->isClient(sock) == 1)
	{
		for (std::vector<int>::iterator it = this->clients.begin(); it != this->clients.end(); ++it)
		{
			if (*it == sock)
			{
				this->clients.erase(it);
				return (true);
			}
		}
	}
	return (false);
}

bool				IRC::Channel::add_client(client &new_client)
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

void				IRC::Channel::send_topic_rpl(std::string rpl)
{
	int bytes = 0;
	for (std::vector<int>::iterator it = this->clients.begin(); it != this->clients.end(); it++)
	{
		std::cout << "Response sent to " << *it << ": " << rpl << std::endl;
		bytes = send(*it, rpl.c_str(), rpl.size(), 0);
		if (bytes < 0)
			std::cout << "Error sending data to client." << std::endl;
	}
}
void				IRC::Channel::delOperators(int operateur)
{
	std::cout << GREEN << "operator deleted" << END_C << std::endl;
	for (std::vector<int>::iterator it = this->operators.begin(); it != this->operators.end(); ++it) {
    	if (*it == operateur) {
    	    this->operators.erase(it);
    	    break;
    	}
    }
}

void				IRC::Channel::delModes(char c)
{
	std::size_t position_c = modes.find(c);
	if(position_c != std::string::npos)
		modes.erase(position_c);
	std::cout << "MODES STRING = " << modes << std::endl;
	return ;
}

//-------------------- Getters ----------------------------------------------//
std::string			IRC::Channel::getModes(void)
{
	return (this->modes);
}

std::string			IRC::Channel::getName(void)
{
	return (this->name);
}

std::string			IRC::Channel::getTopic(void)
{
	return (this->topic);
}

std::vector<int>	IRC::Channel::getOperators(void)
{
	return (this->operators);
}

std::vector<int>&	IRC::Channel::getClients(void)
{
	return (this->clients);
}

int&				IRC::Channel::getLimitClients(void)
{
	return (this->limitClients);
}

std::vector<int>&	IRC::Channel::getInvitations(void)
{
	return (this->invitations);
}

std::string&		IRC::Channel::getChannelPassword(void)
{
	return (this->channelPassword);
}

//-------------------- Setters ----------------------------------------------//
void				IRC::Channel::setName(std::string& name)
{
	this->name = name;
}

void				IRC::Channel::setTopic(std::string& topic)
{
	this->topic.clear();
	this->topic = topic;
}

void				IRC::Channel::setOperators(int operateur)
{
	std::cout << GREEN << "New operator added" << END_C << std::endl;
	this->operators.push_back(operateur);
}

void				IRC::Channel::setLimitClients(int limit)
{
	this->limitClients = limit;
	return ;
}

void				IRC::Channel::setModes(char c)
{
	if(modes.find(c) == std::string::npos)
		modes += c;
	std::cout << "MODES STRING = " << modes << std::endl;
	return ;
}

void				IRC::Channel::setPassword(std::string pass)
{
	this->channelPassword = pass;
	return ;
}

void				IRC::Channel::setClients(client& client)
{
	std::cout << "Client " << client.GetSock() << " added to " << this->getName();
	this->clients.push_back(client.GetSock());
}

// bool							IRC::Channel::isOperator(int fd){
// 	for (std::vector<int>::iterator it = operators.begin(); it != operators.end(); ++it){
// 		if (*it == fd)
// 			return (true);
// 	}
// 	return (false);
// }
