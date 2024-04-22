/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   IRC.cpp                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jquil <jquil@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/27 18:07:38 by jquil             #+#    #+#             */
/*   Updated: 2024/04/22 14:19:14 by jquil            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "IRC.hpp"

IRC::IRC(int port, std::string mdp)
{
	std::cout << "Default IRC constructor" << std::endl;
	memset(&this->server, 0, sizeof(this->server));
	this->server.sin_addr.s_addr = htonl(INADDR_LOOPBACK);// 127.0.0.1, localhost
	this->server.sin_port = htons(port);
	this->poll_count = 1;
	this->poll_size = 2;
	this->secure = 0;
	this->poll_fds = NULL;
	this->server.sin_family = AF_INET;
	this->sock = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
	if (this->calloc_pollfd(10) == 0)
		this->secure = 1;
	this->poll_fds[0].fd = this->sock;
	this->poll_fds[0].events = POLLIN;
	if (this->sock < 0)
		this->secure = 1;
	else
		this->bind_sock = bind(this->sock, (struct sockaddr *)&this->server, sizeof(this->server));
	if (this->bind_sock < 0)
	{
		this->secure = 1;
		return;
	}
	else
		this->lstn = listen(this->sock, 10);
	if (this->lstn < 0)
		this->secure = 1;
	this->peer_addr_size = sizeof (struct sockaddr_in);
	this->port = port;
	this->mdp = mdp;
};

int IRC::calloc_pollfd(int size)
{
	if (!this->poll_fds)
	{
		this->poll_fds = (struct pollfd *) calloc(size + 1, sizeof *this->poll_fds);
		if (!this->poll_fds)
			return (0);
	}
	return (1);
}

IRC::~IRC()
{
	free(this->poll_fds);
	close(this->sock);
	std::cout << "Default destructor called" << std::endl;
};

void	IRC::Kick(void)
{
	std::cout << "Enter Kick function" << std::endl;
}

void	IRC::Invite(void)
{
	std::cout << "Enter Invite function" << std::endl;
}

void	IRC::Topic(void)
{
	std::cout << "Enter Topic function" << std::endl;
}

void	IRC::Mode(void)
{
	std::cout << "Enter Mode function" << std::endl;
}



void	IRC::launch_serv(void)
{
	if (this->secure == 1)
	{
		std::cout << "Initialisation failure, exit the program" << std::endl;
		return ;
	}
	char server_recv[200];
	memset(server_recv, '\0', 200);
	std::cout << "Server launched, listening on port : " << this->port << std::endl;
	while (42)
	{
		int status = poll(this->poll_fds, this->poll_count, 9000);
		if (status == -1)
		{
			std::cout << "Poll failure" << std::endl;
			return ;
		}
		for (int x = 0; x < 10; x++)
		{
			if ((poll_fds[x].revents & POLLIN) != 1)
				continue ;
 			if (this->poll_fds[x].fd == this->sock)
			{
				int client = accept(this->sock, (struct sockaddr *)&this->peer_addr, &this->peer_addr_size);
				if (client > 0)
				{
					if (this->add_poll_fds(client) == 0)
						return ;
					recv(client, server_recv, 200, 0);
					class client cl(client, server_recv, this->mdp);
					if (check_pass(cl) == 1)
					{
						this->users[client] = cl;
						connect(client, (struct sockaddr *)&this->peer_addr, this->peer_addr_size);
						std::string acc = ":localhost 001 " + cl.GetNick() + " :Welcome to bdtServer " + cl.GetNick() + "!~" + cl.GetUser() + "@127.0.0.1\r\n";
						std::cout << acc << std::endl;
						send(client, acc.c_str(), 512, 1);
					}
					else
					{
						std::cout << "Wrong password" << std::endl;
						return ;
					}
				}
			}
			else
				manage_input(this->poll_fds[x].fd);
		}
	}
}

void IRC::manage_input(int fd)
{
	char server_recv[200];
	int bytes_read = 0;
	memset(server_recv, '\0', 200);
	bytes_read = recv(fd, server_recv, 200, 0);
	if (bytes_read > 0)
	{
		std::cout << server_recv << std::endl;
		sleep(5);
	}
}

int IRC::add_poll_fds(int new_fd)
{
	if (this->poll_count == this->poll_size)
	{
		this->poll_fds = (struct pollfd *) realloc(this->poll_fds, sizeof(*(this->poll_fds)) * (this->poll_size));
		if (!this->poll_fds)
			return (0);
	}
	this->poll_fds[this->poll_count].fd = new_fd;
	this->poll_fds[this->poll_count].events = POLLIN;
	this->poll_count++;
	return (1);
}

bool IRC::check_pass(client cl)
{
	if (cl.pass_check == 1)
	{
		std::cout << "Password is correct" << std::endl;
		return (1);
	}
	else
	{
		std::cout << "Incorrect Password" << std::endl;
		return (0);
	}
}


