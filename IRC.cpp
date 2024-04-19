/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   IRC.cpp                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbouguet <lbouguet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/27 18:07:38 by jquil             #+#    #+#             */
/*   Updated: 2024/04/19 15:37:23 by lbouguet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "IRC.hpp"

IRC::IRC(int port, std::string mdp)
{
	std::cout << "Default IRC constructor" << std::endl;
	
	// Init server name to 0000
	memset(&this->server, 0, sizeof(this->server));
	
	// Définit l'ecoute sur toutes les interfaces
	this->server.sin_addr.s_addr = htonl(INADDR_LOOPBACK);// 127.0.0.1, localhost
	
	// Port sur lequel doit écouter le serveur
	this->server.sin_port = htons(port);
	
	// Compteur de poll (nombre de socket à surveiller)
	this->poll_count = 1;
	
	// Boolen de secu pour poll
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
	try
	{
		if (this->sock < 0)
			throw IRC::SocketFailedException();
	}
	catch(const IRC::SocketFailedException & e)
	{
		std::cerr << e.what() << std::endl;
		std::cout << "Socket() failed" << std::endl;
		this->secure = 1;
	}
	
	// (descripteur de fichier, struct de la socket, taille de la socket)
	this->bind_sock = bind(this->sock, (struct sockaddr *)&this->server, sizeof(this->server)); // invalid argument -> errno 99
	try
	{
		if (this->bind_sock < 0)
			throw IRC::BindFailedException();
	}
	catch(const IRC::BindFailedException & e)
	{
		std::cerr << e.what() << std::endl;
		this->secure = 1;
		return;
	}

	// Ouverture de la socket
	this->lstn = listen(this->sock, 10);
	try
	{
		if (this->lstn < 0)
			throw IRC::ListenFailedException();
	}
	catch(const IRC::ListenFailedException & e)
	{
		std::cerr << e.what() << std::endl;
		this->secure = 1;
		std::cout << "Listen() failed" << std::endl;
	}
	
	if (this->calloc_pollfd(10) == 0)
		this->secure = 1;
	
	// Taille de la socket
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

// /rawlog open ~/IRC_githubed/logs.txt
void	IRC::launch_serv(void)
{
	if (this->secure == 1)
	{
		std::cout << "sock = " << this->sock << "	bind = " << this->bind_sock << "	lstn = " << this->lstn << std::endl;
		std::cout << "Initialisation failure, exit the program" << std::endl;
		return ;
	}
	// std::cout << "port = " << this->port << "	mdp = " << this->mdp << "	sock = " << this->sock << "\n	bind_sock = " << this->bind_sock << "	lstn = " << this->lstn << "\n secure = " << this->secure << std::endl;
	char server_recv[200];
	std::cout << "Server launched, listening on port : " << this->port << std::endl;
	
	// Routine poll
	while (42)
	{
		// Lancement de poll ()
		int status = poll(this->poll_fds, this->poll_count, 9000);

		// Security check du lancement de poll
		if (status == -1)
		{
			std::cout << "Poll failure" << std::endl;
			return ;
		}
		
		// Routine 
		for (int x = 0; x < 10; x++)
		{
			if (this->poll_fds[x].fd == this->sock)
			{
				std::cout << "socket accept" << std::endl;
				// Accept/Parse de la connexion entrante (Socket ouverte, addr du nouveau client, taille de l'addr)
				int client = accept(this->sock, (struct sockaddr *)&this->peer_addr, &this->peer_addr_size);
				if (client > 0)
				{
					int recv_rec = 1;
					
					// Connect le nouveau client 
					connect(client, (struct sockaddr *)&this->peer_addr, this->peer_addr_size);
					
					// Lit dans la socket server (socket client, buff, nb octets à lire, flags)
					recv_rec = recv(client, server_recv, 200, 0);
					class client cl(client, server_recv, this->mdp);
					if (check_pass(cl) == 0)
						recv_rec = 0;
					else
					{
						std::string acc = ":Password accepted.\r\n:localhost 001 jquil :Welcome to bdtServer jquil !~ jquil @127.0.0.1\r\n"; // update apres avoir creer la classe client et integrer les getters
						//std::string acc = ":localhost 001 " + client.getNick() + " :Welcome to bdtServer " + client.getNick() + "!~" + client.getUsername() + "@127.0.0.1\r\n";
						send(client, acc.c_str(), 512, 1);
					}
				}
			}
		}
	}
}

IRC::~IRC()
{
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

const char *IRC::SocketFailedException::what() const throw()
{
	return ("Socket() failed\n");
}

const char *IRC::BindFailedException::what() const throw()
{
	std::cout << "Bind errno = " << errno << std::endl;
	// if (errno == 98)
	// {
	// 	getline();
	// }
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
