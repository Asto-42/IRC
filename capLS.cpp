/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   capLS.cpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jquil <jquil@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/22 18:11:56 by jquil             #+#    #+#             */
/*   Updated: 2024/09/10 12:35:40 by jquil            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "include/IRC.hpp"

bool	IRC::capLs(client &client, std::string cmd)
{
	if (cmd != "LS")
		return (0);
	if (client.GetSetup() == 0)
		client.SetSetup(1);
	return (1);
}
