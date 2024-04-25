/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mode.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rencarna <rencarna@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/22 18:15:39 by jquil             #+#    #+#             */
/*   Updated: 2024/04/24 18:07:44 by rencarna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "IRC.hpp"


// Sign 0 = - || 1 = +

typedef struct t_option {
    int		sign;
    char	opt;
} s_option;

std::vector<std::string> split(const std::string& s, const std::string& delimiters) {
    std::vector<std::string> tokens;
    size_t start = 0, end = 0;

    while ((start = s.find_first_not_of(delimiters, end)) != std::string::npos) {
        end = s.find_first_of(delimiters, start);
        if (end == std::string::npos) {
            tokens.push_back(s.substr(start));
        } else {
            tokens.push_back(s.substr(start, end - start));
        }
    }
    return tokens;
}
bool IRC::mode(client &client, std::string cmd){

	std::cout << "mode param "<<cmd << std::endl;
	std::vector<std::string> argument = split(cmd ," \r\n");
	std::vector<std::string>		param;
	std::vector<char>           opt_vector;
	std::vector<std::string>::iterator it = argument.begin();
	std::string channelName;

	int sign = -1;
	int optCount = 0;
	for(std::vector<std::string>::iterator me = argument.begin(); me != argument.end(); me++)
		std::cout << "ARGUMENT VAR = " <<*me << std::endl;
	std::string err = "localhost";

	if (cmd.size() == 0){
		std::string tmp = "USER";
		sendRPL(ERR_NOTENOUGHPARAM(err), client.GetSock());
		return (0);
	}
	if(client.GetSetup() != 2 && client.GetSetup() != 4)
		sendRPL(ERR_NOTREGISTERED(err), client.GetSock());
	if(argument.size() < 2 || cmd == "")
		sendRPL(ERR_NOTENOUGHPARAM(err), client.GetSock());
	// if(optCount == 0)
	// 	return (0);
	channelName = *it;
	if(it[0] == "#"){
		channelName = *it;
		it++;
	}
	for(;it != argument.end() ; it++)
	{
		
		std::string opt = *it;
		if(opt[0] == '-' || opt[0] == '+')
		{
			std::cout << " mode fct" << std::endl;
			optCount++;

			for(size_t i = 0; i < opt.size(); i++)
			{
				opt_vector.push_back(opt[i]);
			}
		}
		else
			param.push_back(opt);
	}
	
	if(optCount == 0)
		return(0);
	std::cout << "channelname " <<channelName << std::endl;
	for(std::vector<char>::iterator op = opt_vector.begin(); op < opt_vector.end() ; op++)
	{
		std::cout << " OP = "<<*op << std::endl;
		switch(*op)
		{

			case '+' :
				// std::cout << " OPw = "<<*op e<< sendl;
				sign = 1;
				break;
			case '-':
				sign = 0;
				break;
			case 'i':
					for(std::vector<Channel>::iterator ite = channels.begin(); ite != channels.end(); ite++)
						if(ite->getName() == channelName){
							if(sign == 1)
								ite->setModes('i');
							if(sign == 0)
								ite->delModes('i');
						}
					return(true);
				
		}
	}
	return(true);
}