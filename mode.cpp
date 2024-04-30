/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mode.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jquil <jquil@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/22 18:15:39 by jquil             #+#    #+#             */
/*   Updated: 2024/04/26 15:28:29 by jquil            ###   ########.fr       */
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

	std::cout << "mode param "<<cmd << std::endl;
	std::vector<std::string> argument = split(cmd ," \r\n");
	std::vector<std::string>		param;
	std::vector<char>           opt_vector;	
	int optCount = 0;

	std::string err = "localhost";
	if (cmd.size() == 0)
		return (sendRPL(ERR_NOTENOUGHPARAM(err), _client.GetSock()), 0);
	if(_client.GetSetup() != 2 && _client.GetSetup() != 4)
		return (sendRPL(ERR_NOTENOUGHPARAM(err), _client.GetSock()), 0);
	if(argument.size() < 1 || cmd == "")
		return (sendRPL(ERR_NOTENOUGHPARAM(err), _client.GetSock()), 0);
	for(std::vector<std::string>::iterator it = argument.begin() ;it != argument.end() ; it++)
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
		return (sendRPL(ERR_NOTENOUGHPARAM(err), _client.GetSock()), 0);
	
	if(*argument.begin() == _client.GetNick())
		return (true);
	else
		handle_mode(_client, opt_vector, *argument.begin(), param);
	return(true);
}

void IRC::handle_mode(client &_client, std::vector<char> opt_vector, std::string channelName, std::vector<std::string> param)
{
	std::vector<std::string>::iterator pit = param.begin();
	std::vector<int> admin;
	int sign = -1;
	for (std::vector<Channel>::iterator ite = channels.begin(); ite != channels.end(); ite++)
	{
		if(ite->getName() == channelName)
			admin = ite->getOperators();
	}
	if (std::find(admin.begin(), admin.end(), _client.GetSock()) == admin.end())
		return(sendRPL(ERR_NOTOPERATOR(channelName), _client.GetSock()));
	param.erase(param.begin());
	// PRINTER
	for(std::vector<std::string>::iterator pi = param.begin(); pi != param.end(); pi++)
		std::cout<< "PIT = " << *pi << std::endl;
	for(std::vector<char>::iterator op = opt_vector.begin(); op < opt_vector.end() ; op++)
		std::cout << "OP = " << *op << std::endl;
	//boucle 
	for(std::vector<char>::iterator op = opt_vector.begin(); op < opt_vector.end() ; op++)
	{
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
					sendRPL(RPL_INVEXLIST1(_client.GetNick(), channelName), _client.GetSock());
				else if (sign == 0)
					sendRPL(RPL_INVEXLIST2(_client.GetNick(), channelName), _client.GetSock());
				break;
			case 't':
				add_options('t',sign,channelName);
				break;
			case 'k':
				add_options('k',sign,channelName);
				if(*pit == "" || pit->empty()){
					sendRPL(ERR_NOTENOUGHPARAM(_client.GetNick()), _client.GetSock());
					param.erase(param.begin());
					break ;
				}
				mode_opt(channelName, sign, *pit, _client, *op);
				break;
			case 'o':
				if(*pit == "" || pit->empty()){
					sendRPL(ERR_NOTENOUGHPARAM(_client.GetNick()), _client.GetSock());
					param.erase(param.begin());
					break ;
				}
				mode_opt(channelName, sign, *pit, _client, *op);
				param.erase(param.begin());
				break;
			case 'l':
				add_options('l',sign,channelName);
				if(*pit == "" || pit->empty()){
					sendRPL(ERR_NOTENOUGHPARAM(_client.GetNick()), _client.GetSock());
					param.erase(param.begin());
					break ;
				}
				mode_opt(channelName, sign, *pit, _client, *op);
				param.erase(param.begin());
				break;
		}
	}
}

bool						IRC::mode_opt(std::string channelName, int sign , std::string pit , client &_client, char op){
	std::cout << " LA " << channelName << " " << sign  << " "  << pit   << " " << op   << " " << std::endl;
	for (std::vector<Channel>::iterator ite = channels.begin(); ite != channels.end(); ite++)
	{
		if(ite->getName() == channelName){
			if(op == 'o'){
					for(std::map<int, client>::iterator it = users.begin(); it != users.end(); it++)
					{
						if(it->second.GetNick() == pit)
						{
							std::string hostname = _client.GetNick() + "!" + _client.GetUser();
							if(sign == 1)
								return(ite->setOperators(it->first), true);
							else
								return(ite->delModes(it->first), true);
						}
						else
							return(sendRPL(ERR_NOSUCHNICK(channelName, pit), _client.GetSock()), false);
					}
			}
			if(op == 'k'){
				if(sign == 1)
					ite->setPassword(pit);
				else
					ite->setPassword("");
			}
			if(op == 'k'){
				if(sign == 1)
					ite->setLimitClients(atoi(pit.c_str()));
				else
					ite->setLimitClients(10);
			}
		}
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
