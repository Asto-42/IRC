/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pass.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jquil <jquil@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/22 18:12:26 by jquil             #+#    #+#             */
/*   Updated: 2024/09/10 12:35:40 by jquil            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "include/IRC.hpp"

bool	IRC::pass(client &client, std::string cmd)
{
	if (cmd != this->mdp || client.GetSetup() != 1)
	{
		//close socket
		return (0);
	}
	client.SetPass(cmd);
	client.SetSetup(2);
	return (1);
}
