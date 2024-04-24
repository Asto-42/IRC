/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mode.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jquil <jquil@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/22 18:15:39 by jquil             #+#    #+#             */
/*   Updated: 2024/04/24 17:36:26 by jquil            ###   ########.fr       */
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

	while ((start = s.find_first_not_of(delimiters, end)) != std::string::npos) {
		end = s.find_first_of(delimiters, start);
		tokens.push_back(s.substr(start, end - start));
	}
	return tokens;
}

bool IRC::mode(client &client, std::string cmd)
{
	//std::vector<std::string> options = split(cmd ," ");
	std::string input;
	std::string channelName;
	std::string flag;
	std::string arg;
	std::string	cmd_multi;
	std::vector<std::string>		param;
	std::vector<s_option>           opt_vector;
	std::string err = "localhost";
	std::string::size_type x;
	std::string::size_type space;
	std::string::size_type flag_pos;
	std::string::size_type arg_pos;
	//s_option stuc_opt = {-1, '\0'};
	if (cmd.size() == 0)
	{
		std::string tmp = "USER";
		sendRPL(ERR_NOTENOUGHPARAM(err), client.GetSock());
		return (0);
	}
	// if(client.GetSetup() != 2 && client.GetSetup() != 4)
	// 	sendRPL(ERR_NOTREGISTERED(err), client.GetSock());
	// if(options.size() < 2 || cmd == "")
	// 	sendRPL(ERR_NOTENOUGHPARAM(err), client.GetSock());
	// if(!client.isOperator(client.GetSock()))
	// 	sendRPL(ERR_NOTOPERATOR(client.GetNick()), client.GetSock());
	if ((x = cmd.find("#", 0)) != std::string::npos)
	{
		input = cmd.substr(0, x);
		if ((space = cmd.find(" "), x) != std::string::npos)
		{
			channelName = cmd.substr(x + 1, space);
			if (cmd.find("-", 0) > cmd.find("+", 0))
				x = cmd.find("+", 0);
			else
				x = cmd.find("-", 0);
			cmd = cmd.substr(x, cmd.size());
			if (cmd.find("+", 0) < 0 && cmd.find("-", 0) < 0)
				return (0);
			while (cmd.size() > 0)
			{
				if ((space = cmd.find(" ", 0)) != std::string::npos)
				{
					flag = cmd.substr(x, space);
					cmd.erase(0, space);
					std::map<int, char*> flag;
					std::vector<std::string> arg;
					for (std::string::iterator it = cmd.begin(); it != cmd.end(); ++it)
					{
						if (*it == '+' || *it == '-')
						{
							flag->first.push_back(*it);
							std::string::iterator it2;
							for (it2 = it; *it2 != ' '; ++it2)
							{
								flag[]push_back(*it2);
							}
							it = it2;
						}
						if (*it != ' ')
						{
							std::string::size_type tmp = cmd.find(*it);
							while (*it != ' ')
								++it;
							std::string::size_type tmp2 = cmd.find(*it);
							std::string arg_tmp = cmd.substr(tmp, tmp2);
							arg.push_back(arg_tmp);
						}
					}
					this->exec_mode(flag, arg);
				}
			}
		}
	}
}

void	IRC::exec_mode(std::map<int,char*>flag, std::vector<std::string>arg)
{

}

// {
// 	std::vector<std::string> options = split(cmd ," ");
// 	std::string channelName;
// 	std::vector<std::string>		param;
// 	std::vector<s_option>           opt_vector;
// 	std::vector<std::string>::iterator it = options.begin();
// 	int optCount = 0;
// 	std::string err = "localhost";
// 	s_option stuc_opt = {-1, '\0'};



// 	for(; it != options.end(); it++)
// 	{
// 		std::string opt = *it;
// 		if (opt[0] == '+')
// 		{
// 			stuc_opt.sign = 1;
// 			stuc_opt.opt = opt[1];
// 			optCount++;
// 			opt_vector.push_back(stuc_opt);
// 		}
// 		else if (opt[0] == '-')
// 		{
// 			stuc_opt.sign = 0;
// 			stuc_opt.opt = opt[1];
// 			optCount++;
// 			opt_vector.push_back(stuc_opt);
// 		}
// 		else
// 			param.push_back(*it);
// 	}
// 	return(true);
// }
