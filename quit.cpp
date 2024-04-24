/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quit.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jquil <jquil@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/22 18:16:16 by jquil             #+#    #+#             */
/*   Updated: 2024/04/24 15:04:02 by jquil            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "IRC.hpp"

bool	IRC::quit(client &client, std::string cmd)
{
	std::string::size_type x;
	if ((x = cmd.find(" ", 0)) == std::string::npos)
		return (0);
	cmd = cmd.substr(0, x);
	if (cmd == "QUIT")
	{
		delete(&client);
		return (1);
	}
	return (0);
}
