/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mode.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: russelenc <russelenc@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/22 18:15:39 by jquil             #+#    #+#             */
/*   Updated: 2024/04/23 15:34:19 by russelenc        ###   ########.fr       */
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
        tokens.push_back(s.substr(start, end - start));
    }
    return tokens;
}

bool IRC::mode(client &client, std::string cmd){
	std::vector<std::string> options = split(cmd ," ");
	std::string channelName;
	std::vector<std::string>		param;
	std::vector<s_option>           opt_vector;
	std::vector<std::string>::iterator it = options.begin()
	int optCount = 0;
	
	if (cmd.size() == 0){
		std::string tmp = "USER";
		sendRPL(ERR_NOTENOUGHPARAM(err), client.GetSock());
		return (0);
	}
	if(client.GetSetup() != 2 && client.GetSetup() != 4)
		sendRPL(ERR_NOTREGISTERED(err), client.GetSock());
	if(options.size() < 2 || cmd == "")
		sendRPL(ERR_NOTENOUGHPARAM(err), client.GetSock());

	if(Channel::isOperator(client.GetSock()))
		sendRPL(ERR_NOTOPERATOR(client.GetNick()));
	for(; it != options.end; it++)
    {
		s_option stuc_opt = {-1, NULL};
        std::string opt = *it;
        if (opt[0] == '+')
        {
			struc_opt.sign = 1;
			struc_opt.opt = opt[1];
            optCount++;
            opt_vector.push_back(opt[i]);
        }
		else if (opt[0] == '-')
        {
			struc_opt.sign = 1;
			struc_opt.opt = opt[1];
            optCount++;
            opt_vector.push_back(struc_opt);
        }
        else
            param.push_back(*it);
    }
	
}