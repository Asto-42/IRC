/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   IRC.cpp                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jquil <jquil@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/27 18:07:38 by jquil             #+#    #+#             */
/*   Updated: 2024/03/28 14:21:00 by jquil            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "IRC.hpp"

IRC::IRC(int port, std::string mdp)
{
	std::cout << "Default IRC constructor" << std::endl;
	this->sock = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
	try
	{
		if (this->sock == -1)
			throw IRC::SocketFailedException();
	}
	catch(const IRC::SocketFailedException & e)
	{
		std::cerr << e.what() << std::endl;
		std::cout << "Socket() failed" << std::endl;
	}
	this->server.sin_family = AF_INET;
	this->server.sin_addr.s_addr = htonl(INADDR_LOOPBACK);// 127.0.0.1, localhost
	this->server.sin_port = htons(6666);
	memset(&this->server, 0, sizeof(this->server));
	this->bind_sock = bind(this->sock, (struct sockaddr *)&this->server, sizeof(this->server)); // invalid argument -> errno 99
	try
	{
		if (this->bind_sock < 0)
			throw IRC::BindFailedException();
	}
	catch(const IRC::BindFailedException & e)
	{
		std::cerr << e.what() << std::endl;
		std::cout << "Bind() failed" << std::endl;
	}
	this->lstn = listen(this->sock, 10);
	try
	{
		if (this->lstn < 0)
			throw IRC::ListenFailedException();
	}
	catch(const IRC::ListenFailedException & e)
	{
		std::cerr << e.what() << std::endl;
		std::cout << "Listen() failed" << std::endl;
	}
	this->peer_addr_size = sizeof(struct sockaddr_in);
	this->port = port;
	this->mdp = mdp;
};

IRC::~IRC()
{
	close(this->sock);
	std::cout << "Default destructor called" << std::endl;
};

void IRC::launch_serv(void)
{
	while (42)
	{
		std::cout << "Server launched, listening on port : " << this->port << std::endl;
		this->acc = accept(this->sock, (struct sockaddr *)&this->server, &this->peer_addr_size);
		try
		{
			if (this->acc < 0)
				throw IRC::AcceptFailedException();
		}
		catch(const IRC::AcceptFailedException & e)
		{
			std::cerr << e.what() << '\n';
			std::cout << "Accept() failed" << std::endl;
		}
	}
}

const char *IRC::SocketFailedException::what() const throw()
{
	return ("Socket() failed\n");
}

const char *IRC::BindFailedException::what() const throw()
{
	return ("Bind() failed\n");
}

const char *IRC::ListenFailedException::what() const throw()
{
	return ("Listen() failed\n");
}

const char *IRC::AcceptFailedException::what() const throw()
{
	return ("Accept() failed\n");
}
