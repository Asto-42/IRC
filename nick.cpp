/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   nick.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jquil <jquil@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/22 18:12:57 by jquil             #+#    #+#             */
/*   Updated: 2024/04/22 18:25:33 by jquil            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "IRC.hpp"

bool	IRC::nick(client &client, std::string cmd)
{
	if (cmd.size() == 0 || (client.GetSetup() != 2 && client.GetSetup() != 4))
		return (0);
	client.SetNick(cmd);
	if (client.GetSetup() != 4)
		client.SetSetup(3);
	return (1);
}
