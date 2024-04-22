/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   IRC.cpp                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jquil <jquil@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/27 18:07:38 by jquil             #+#    #+#             */
/*   Updated: 2024/04/22 13:52:28 by jquil            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "IRC.hpp"

IRC::IRC(int port, std::string mdp)
{
	std::cout << "Default IRC constructor" << std::endl;

	std::cout << "" << std::endl;


	// Init server name to 0000
	memset(&this->server, 0, sizeof(this->server));

	// Définit l'ecoute sur toutes les interfaces
	this->server.sin_addr.s_addr = htonl(INADDR_LOOPBACK);// 127.0.0.1, localhost

	// Port sur lequel doit écouter le serveur
	this->server.sin_port = htons(port);

	// Compteur de poll (nombre de socket à surveiller)
	this->poll_count = 1;

	// Boolen de secu pour poll
	this->poll_size = 2;
	this->secure = 0;

	// Init tab poll à NULL
	this->poll_fds = NULL;

	// Type de protocole d'écoute internet
	this->server.sin_family = AF_INET;

	// FAMILLE :AF_INET pour utiliser protocole TCP/IP avec adresse de plus de 4 octets
	// TYPE : SOCK_STREAM pour mode connecté (connexion permanente)
	// PROTOCOL : IPPROTO_TCP pour TCP
	this->sock = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);

	// Test de la socket
	if (this->calloc_pollfd(10) == 0)
		this->secure = 1;
	this->poll_fds[0].fd = this->sock;
	this->poll_fds[0].events = POLLIN;
	//std::signal(SIGINT, closeServer);
	//std::signal(SIGQUIT, closeServer);
	if (this->sock < 0)
		this->secure = 1;
	else
		this->bind_sock = bind(this->sock, (struct sockaddr *)&this->server, sizeof(this->server)); // invalid argument -> errno 99
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
	// Def du port
	this->port = port;

	// Def du mdp
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

// /rawlog open ~/IRC_githubed/logs.txt

//nc localhost 1114
//CAP LS ctrl+V ctrl+M

void	IRC::launch_serv(void)
{
	if (this->secure == 1)
	{
		//std::cout << "sock = " << this->sock << "	bind = " << this->bind_sock << "	lstn = " << this->lstn << std::endl;
		std::cout << "Initialisation failure, exit the program" << std::endl;
		return ;
	}
	char server_recv[200];
	memset(server_recv, 0, 200);
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
						std::string acc = ":localhost 001 " + cl.GetNick() + " :Welcome to SUUUServer " + cl.GetNick() + "!~" + cl.GetUser() + "@127.0.0.1\r\n";
						int snd = send(client, acc.c_str(), 512, 1);
						(void)snd;
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

void IRC::manage_input(int x)
{
	(void)x;
	// char server_recv[200];
	// recv(x, server_recv, 200, 0);
	// std::cout << server_recv << std::endl;
}

int IRC::add_poll_fds(int new_fd)
{
	if (this->poll_count == this->poll_size)
	{
		this->poll_size *= 2; // Double la taille
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


