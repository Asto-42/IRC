/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   IRC.cpp                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rencarna <rencarna@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/27 18:07:38 by jquil             #+#    #+#             */
/*   Updated: 2024/04/24 13:56:00 by rencarna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "IRC.hpp"

IRC::IRC(int port, std::string mdp)
{
	std::cout << "Default IRC constructor" << std::endl;
	memset(&this->server, 0, sizeof(this->server));
	this->server.sin_addr.s_addr = htonl(INADDR_LOOPBACK); // 127.0.0.1, localhost
	this->server.sin_port = htons(port);
	this->poll_count = 1;
	this->poll_size = 2;
	this->secure = 0;
	this->poll_fds = NULL;
	this->server.sin_family = AF_INET;
	this->sock = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
	int optval = 1;
	setsockopt(this->sock, SOL_SOCKET, SO_REUSEADDR, &optval , sizeof(int));
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
	this->peer_addr_size = sizeof(struct sockaddr_in);
	this->port = port;
	this->mdp = mdp;
	initCommand();
};

int IRC::calloc_pollfd(int size)
{
	if (!this->poll_fds)
	{
		this->poll_fds = (struct pollfd *)calloc(size + 1, sizeof *this->poll_fds);
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

void IRC::launch_serv(void)
{
	if (this->secure == 1)
	{
		std::cout << "Initialisation failure, exit the program" << std::endl;
		return;
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
			return;
		}
		for (int x = 0; x < 10; x++)
		{
			if ((poll_fds[x].revents & POLLIN) != 1)
				continue;
			if (this->poll_fds[x].fd == this->sock)
			{
				int client = accept(this->sock, (struct sockaddr *)&this->peer_addr, &this->peer_addr_size);
				if (client > 0)
				{
					if (this->add_poll_fds(client) == 0)
						return;
					class client cl(client);
					this->users[client] = cl;
				}
			}
			else
				manage_input(x);
		}
	}
}

void IRC::manage_input(int x)
{
	char server_recv[512];
	int fd = this->poll_fds[x].fd;
	memset(&server_recv, '\0', sizeof(server_recv));
	if (recv(fd, server_recv, sizeof(server_recv), 0) <= 0)
	{
		std::cout << server_recv << std::endl;
		sleep(1);
		// del user
		// close le fd
		// delete du poll de fd
	}
	else
	{
		std::string line = users.find(fd)->second.GetBuffer() + server_recv;
		this->users.find(fd)->second.SetBuffer("");
		std::string input;
		std::string tmp;
		std::string::size_type end;
		std::string::size_type space;
		while ((end = line.find("\r\n", 0)) != std::string::npos)
		{
			input = line.substr(0, end);
			line.erase(0 ,end + 2);
			if ((space = input.find(" ", 0)) != std::string::npos)
			{
				tmp = input.substr(0, space);
				input.erase(0, space + 1);
				if (this->cmd.find(tmp) != this->cmd.end())
					(this->*cmd[tmp])(this->users.find(fd)->second, input);
			}
		}
	}
}

//void IRC::Kick(void)
// {
// 	std::cout << "Enter Kick function" << std::endl;
// }

// void IRC::Invite(void)
// {
// 	std::cout << "Enter Invite function" << std::endl;
// }

// void IRC::Topic(void)
// {
// 	std::cout << "Enter Topic function" << std::endl;
// }

// void IRC::Mode(void)
// {
// 	std::cout << "Enter Mode function" << std::endl;
// }

void IRC::sendRPL(std::string rpl, int fd)
{
	std::cout << "Response sent to " << fd << ": " << rpl << std::endl;
	send(fd, rpl.c_str(), rpl.size(), 0);
}

void IRC::initCommand(void)
{
	this->cmd["CAP"] = &IRC::capLs;
	this->cmd["NICK"] = &IRC::nick;
	this->cmd["USER"] = &IRC::user;
	this->cmd["PASS"] = &IRC::pass;
	this->cmd["PING"]    = &IRC::ping;
	// this->cmd["QUIT"]    = &IRC::quit;
	// this->cmd["JOIN"]    = &IRC::join;
	this->cmd["PRIVMSG"] = &IRC::privmsg;
	// this->cmd["KICK"]    = &IRC::kick;
	//this->cmd["TOPIC"]   	= &IRC::topic;
	this->cmd["MODE"]    = &IRC::mode;
	// this->cmd["INVITE"]  = &IRC::invite;
	// this->cmd["PART"]    = &IRC::part;
	// this->cmd["OPER"]    = &Server::oper;
}


int IRC::add_poll_fds(int new_fd)
{
	if (this->poll_count == this->poll_size)
	{
		this->poll_fds = (struct pollfd *)realloc(this->poll_fds, sizeof(*(this->poll_fds)) * (this->poll_size));
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

bool						IRC::ChannelExist(std::string name){
	for (std::vector<Channel>::iterator it = channels.begin(); it != channels.end(); ++it){
		if (it->getName() == name)
			return (true);
	}
	return (false);
}
