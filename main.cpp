/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbouguet <lbouguet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/28 15:41:53 by jquil             #+#    #+#             */
/*   Updated: 2024/05/02 18:04:28 by lbouguet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "IRC.hpp"

int	main(int argc, char **argv)
{
	if (argc != 3)
	{
		std::cout << "Invalid argument(s)" << std::endl;
		return (0);
	}
	if (std::atoi(argv[1]) < 1100 || std::atoi(argv[1]) > 65535)
	{
		std::cout << "Invalid port" << std::endl;
		return (0);
	}
	IRC serv(atoi(argv[1]), argv[2]);
	signal(SIGINT, IRC::SignalHandler); //-> catch the signal (ctrl + c)
  	signal(SIGQUIT, IRC::SignalHandler); //-> catch the signal (ctrl + \)
	serv.launch_serv();
	return (0);
}
