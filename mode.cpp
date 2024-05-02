/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mode.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rencarna <rencarna@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/22 18:15:39 by jquil             #+#    #+#             */
/*   Updated: 2024/05/02 15:08:29 by rencarna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "IRC.hpp"


// Sign 0 = - || 1 = +

typedef struct t_option {
    int		sign;
    char	opt;
} s_option;

std::vector<std::string> split(const std::string& s, const std::string& delimiters)
{
	std::vector<std::string> tokens;
	size_t start = 0, end = 0;

	while ((start = s.find_first_not_of(delimiters, end)) != std::string::npos)
	{
		end = s.find_first_of(delimiters, start);
		if (end == std::string::npos)
			tokens.push_back(s.substr(start));
		else
			tokens.push_back(s.substr(start, end - start));
	}
	return tokens;
}
void IRC::add_options(char c, int sign, std:: string channelName){
	for (std::vector<Channel>::iterator ite = channels.begin(); ite != channels.end(); ite++)
	{
		if(ite->getName() == channelName){
			if(sign == 1)
				ite->setModes(c);
			if(sign == 0)
				ite->delModes(c);
		}
	}
}

bool IRC::mode(client &_client, std::string cmd){

	// std::cout << "mode param "<<cmd << std::endl;
	std::vector<std::string> argument = split(cmd ," \r\n");
	std::vector<std::string>		param;
	std::vector<std::string>::iterator it = argument.begin();
	std::vector<char>           opt_vector;	
	int optCount = 0;
	std::string chaname = *argument.begin();
	// for(std::vector<std::string>::iterator ki = argument.begin(); ki != argument.end(); ki++)
	// 	std::cout << RED << BOLD << "argument vector \"" << *ki << "\"" << std::endl << chaname << END_C << std::endl;
	std::string err = "localhost";
	if (cmd.size() == 0)
		return (sendRPL(ERR_NOTENOUGHPARAM(err), _client.GetSock()), 0);
	if(_client.GetSetup() != 2 && _client.GetSetup() != 4)
		return (sendRPL(ERR_NOTENOUGHPARAM(err), _client.GetSock()), 0);
	if(argument.size() < 1 || cmd == "")
		return (sendRPL(ERR_NOTENOUGHPARAM(err), _client.GetSock()), 0);
	it++;
	// std::cout << GREEN << BOLD << *it << END_C << std::endl;
	for(;it != argument.end() ; it++)
	{
		std::string opt = *it;
		if(opt[0] == '-' || opt[0] == '+')
		{
			optCount++;
			for(size_t i = 0; i < opt.size(); i++)
				opt_vector.push_back(opt[i]);
		}
		else
			param.push_back(opt);
	}
	if(optCount == 0)
		return (0);
	// for(std::vector<std::string>::iterator i = param.begin() ; i != param.end() ;  i ++)
	// 	std::cout << GREEN << BOLD << *i << END_C << std::endl;
	if(*argument.begin() == _client.GetNick())
		return (true);
	else
		handle_mode(_client, opt_vector, chaname, param);
	return(true);
}

void IRC::handle_mode(client &_client, std::vector<char> &opt_vector, std::string channelName, std::vector<std::string> &param)
{
	// pit++;
	std::vector<int> admin;
	std::string tmp;
	int sign = -1;
	std::string rplList;
	size_t	idxChan = 0;

	while (idxChan < this->channels.size())
	{
		if (channels[idxChan].getName() == channelName)
		{
			if (channels[idxChan].isOperator(_client) == false)
				return(sendRPL(ERR_NOTOPERATOR(channelName), _client.GetSock()));
			break;
		}
		idxChan++;
	}
	for(std::vector<char>::iterator op = opt_vector.begin(); op < opt_vector.end() ; op++){
		// std::vector<std::string>::iterator pit = param.begin();
		switch(*op)
		{

			case '+' :
				sign = 1;
				break;
			case '-':
				sign = 0;
				break;
			case 'i':
				add_options('i',sign,channelName);
				if (sign == 1)
					tmp = "+";
				else if (sign == 0)
					tmp = "-";
				tmp += *op;
				sendRPL(RPL_MODE(userID(_client.GetNick(), _client.GetNick()), channelName, tmp, ""), _client.GetSock());
			//	if (sign == 1)
			//		sendRPL(RPL_INVEXLIST1(_client.GetNick(), channelName), _client.GetSock());
			//	else if (sign == 0)
			//		sendRPL(RPL_INVEXLIST2(_client.GetNick(), channelName), _client.GetSock());
				break;
			case 't':
				add_options('t',sign,channelName);
				if (sign == 1)
					tmp = "+";
				else if (sign == 0)
					tmp = "-";
				tmp += *op;
				sendRPL(RPL_MODE(userID(_client.GetNick(), _client.GetNick()), channelName, tmp, ""), _client.GetSock());
				break;
			case 'k':
				if(sign == 1 && param.empty())
				{
					sendRPL(ERR_NOTENOUGHPARAM(_client.GetNick()), _client.GetSock());
					break ;
				}
				
				if (sign == 1)
				{
					// std::cout << "holy moly "<< std::endl;
					mode_opt(idxChan, sign, *param.begin(), _client, *op);
					param.erase(param.begin());
					tmp = "+";
				}

				else if (sign == 0){
					// std::cout << "holy 1moly "<< std::endl;
					mode_opt(idxChan, sign, "", _client, *op);
					tmp = "-";
				}

				add_options('k',sign,channelName);
				tmp += *op;
				sendRPL(RPL_MODE(userID(_client.GetNick(), _client.GetNick()), channelName, tmp,  ""), _client.GetSock());
				// sendRPL(RPL_MODE(userID(_client.GetNick(), _client.GetNick()), channelName, tmp,  ""), _client.GetSock());
				break;
			case 'o':
				if(sign == 1 && param.empty())
				{
					sendRPL(ERR_NOTENOUGHPARAM(_client.GetNick()), _client.GetSock());
					break ;
				}
				if (sign == 1)
				{
					mode_opt(idxChan, sign, *param.begin(), _client, *op);
					param.erase(param.begin());
					tmp = "+";
				}
				else if (sign == 0){
					mode_opt(idxChan, sign, "", _client, *op);
					tmp = "-";
				}
				tmp += *op;
				sendRPL(RPL_MODE(userID(_client.GetNick(), _client.GetNick()), channelName, tmp,  ""), _client.GetSock());
				break;
			case 'l':
				if(sign == 1 && param.empty())
				{
					sendRPL(ERR_NOTENOUGHPARAM(_client.GetNick()), _client.GetSock());
					break ;
				}
				if (sign == 1)
				{
					mode_opt(idxChan, sign, *param.begin(), _client, *op);
					param.erase(param.begin());
					tmp = "+";
				}
				else if (sign == 0){
					mode_opt(idxChan, sign, "", _client, *op);
					tmp = "-";
				}
				add_options('l',sign,channelName);
				tmp += *op;
				sendRPL(RPL_MODE(userID(_client.GetNick(), _client.GetNick()), channelName, tmp,  ""), _client.GetSock());
				// param.erase(param.begin());
				break;
		}
	}
}

bool						IRC::mode_opt(size_t idxChan, int sign , std::string pit , client &_client, char op){
	bool found = false;
	std::cout << BOLD << "\tIN MODE OPT" <<  END_C <<std::endl;
	if (op == 'o'){
		for(std::map<int, client>::iterator iter = users.begin(); iter != users.end(); iter++)
			if(pit == iter->second.GetNick() && channels[idxChan].isClient(iter->first))
				found = true;
		if(found)
		{
			std::string hostname = _client.GetNick() + "!" + _client.GetUser();
			// std::cout << RED << ;
			if(sign == 1)
				return(this->channels[idxChan].setOperators(this->getSockFromName(pit)), true);
			else if(sign == 0)
				return(this->channels[idxChan].delModes(this->getSockFromName(pit)), true);
		}
		else
			return(sendRPL(ERR_NOSUCHNICK(this->channels[idxChan].getName(), pit), _client.GetSock()), false);
	}
	if(op == 'k'){
		if(sign == 1)
			this->channels[idxChan].setPassword(pit);
		else
			this->channels[idxChan].setPassword("");
	}
	if(op == 'l'){
		if(sign == 1)
		{
			if(pit.empty())
				return(false);
			this->channels[idxChan].setLimitClients(atoi(pit.c_str()));
		}
		else
			this->channels[idxChan].setLimitClients(10);
	}
	return(true);
}


int	IRC::getSockFromName(std::string name)
{
	for(std::map<int, client>::iterator it = users.begin(); it != users.end(); it++)
	{
		if(it->second.GetNick() == name)
			return(it->first);
	}
	return(-1);
}

std::string	IRC::getNameFromSock(int fd)
{
	for(std::map<int, client>::iterator it = users.begin(); it != users.end(); it++)
	{
		if(it->first == fd)
			return(it->second.GetNick());
	}
	return("");
}
