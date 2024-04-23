/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   topic.cpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbouguet <lbouguet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/22 18:15:23 by jquil             #+#    #+#             */
/*   Updated: 2024/04/23 10:22:11 by lbouguet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "IRC.hpp"

bool						IRC::topic(client &client, std::string cmd)
{
	for (std::vector<Channel>::iterator it = this->channels.begin();
		it != this->channels.end(); it++)
	{
		for (size_t i = 0; i != it->getTopicOperators().size() ; i++)
		{
			if (it->getTopicOperators()[i] == client.GetSock())
				it->setTopic(cmd);
		}
	}
}	