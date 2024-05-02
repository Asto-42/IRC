/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   IRC.cpp                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbouguet <lbouguet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/27 18:07:38 by jquil             #+#    #+#             */
/*   Updated: 2024/05/02 18:07:35 by lbouguet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "IRC.hpp"

bool IRC::_signal = false;

//------------------- Cons/Des -----------------------------------------------//
IRC::IRC(int port, std::string mdp)
{
	std::cout << "Default IRC constructor" << std::endl;
	memset(&this->server, 0, sizeof(this->server));
	this->server.sin_addr.s_addr = INADDR_ANY; // 127.0.0.1, localhost
	this->server.sin_port = htons(port);
	this->poll_count = 1;
	this->poll_size = 2;
	this->secure = 0;
	// this->poll_fds = NULL;
	this->server.sin_family = AF_INET;
	this->sock = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
	int optval = 1;
	setsockopt(this->sock, SOL_SOCKET, SO_REUSEADDR, &optval , sizeof(int));
	// if (this->calloc_pollfd(10) == 0)
	// 	this->secure = 1;
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
	struct pollfd	pollfds;
	pollfds.fd = sock;
	pollfds.events = POLLIN;
	pollfds.revents = 0;
	poll_fds.push_back(pollfds);
	this->peer_addr_size = sizeof(struct sockaddr_in);
	this->port = port;
	this->mdp = mdp;
	initCommand();
};

IRC::~IRC()
{
	// free(this->poll_fds);
	close(this->sock);
	std::cout << "Default destructor called" << std::endl;
};


//------------------- Funcs --------------------------------------------------//
void IRC::SignalHandler(int signum)
{
	(void)signum;
	std::cout << " Signal received" << std::endl;
	_signal = true;
}

void IRC::CloseFds()
{
	std::cout << GREEN << "FDS CORRECTLY CLOSED" << END_C << std::endl;
	if(users.size() >= 1)
	{
		for(size_t i = 0 ; i < users.size(); i++){
			if(users[i].GetSock() > 2){
				std::cout << users.size() << std::endl;
				std::cout << "Client " << users[i].GetSock() << " is disconnected" << std::endl;
				close(users[i].GetSock());
			}
		}
	}
	if (sock != -1){ //-> close the server socket
		std::cout << "Server " << sock << " is Disconnected" << std::endl;
		close(sock);
	}
}

void IRC::launch_serv(void)
{
	std::cout << BLUE << BOLD << "\tIn launch_serv(): " << END_C << std::endl;
	if (this->secure == 1)
	{
		std::cout << "Initialisation failure, exit the program" << std::endl;
		return;
	}
	char server_recv[200];
	memset(server_recv, '\0', 200);
	std::cout << "Server launched, listening on port : " << this->port << std::endl;
	while (IRC::_signal == false)
	{
		int status = poll(&poll_fds[0], poll_fds.size(), 900);
		if (status == -1 && IRC::_signal == false)
		{
			std::cout << "Poll failure" << std::endl;
			return;
		}
		for (size_t x = 0; x < poll_fds.size(); x++)
		{
			if ((poll_fds[x].revents & POLLIN) != 1)
				continue;
			if (this->poll_fds[x].fd == this->sock)
			{
				int client = accept(this->sock, (struct sockaddr *)&this->peer_addr, &this->peer_addr_size);
				if (client > 0)
				{
					struct pollfd pollStruct;
					pollStruct.fd = client;
					pollStruct.events = POLLIN;
					pollStruct.revents = 0;
					poll_fds.push_back(pollStruct);
					class client cl(client);
					this->users[client] = cl;
					std::cout << GREEN << "Client added to vector" << END_C << std::endl;
				}
			}
			else
				manage_input(x);
		}
	}
	CloseFds();
}
void IRC::ClearClients(int fd)
{
	for(size_t i = 0 ; i < poll_fds.size(); i++)
		if(poll_fds[i].fd == fd){
			close(poll_fds[i].fd);
			poll_fds.erase(poll_fds.begin() + i);
			break;
		}
	std::map<int, client>::iterator it = users.find(fd);
    if (it != users.end()) {
        users.erase(it);
    }
}

void IRC::manage_input(int x)
{
	std::cout << BLUE << BOLD <<  "\tIn manage_input(): " << END_C << std::endl;
	char server_recv[512];
	int fd = this->poll_fds[x].fd;
	memset(&server_recv, '\0', sizeof(server_recv));
	if (recv(fd, server_recv, sizeof(server_recv), 0) <= 0)
	{
		std::cout << server_recv << std::endl;
		std::cout << RED << "Client <" << fd << "> Disconnected" << END_C << std::endl;
		ClearClients(fd);
		close(fd);
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
			std::cout << YELLOW << "=========== CMD RECEIVE =========== " << std::endl;
			std::cout << "\""<< input << "\"" << std::endl;
			std::cout << "=================================== " << END_C << std::endl;
			if ((space = input.find(" ", 0)) != std::string::npos)
			{
				tmp = input.substr(0, space);
				input.erase(0, space + 1);
				if (this->cmd.find(tmp) != this->cmd.end())
					(this->*cmd[tmp])(this->users.find(fd)->second, input);
				tmp.clear();
			}
		}
	}
}

void IRC::sendRPL(std::string rpl, int fd)
{
	int bytes = 0;
	std::cout << "Response sent to " << fd << ": " << rpl << std::endl;
	send(fd, rpl.c_str(), rpl.size(), 0);
	if (bytes < 0)
		std::cout << "Error sending data to client." << std::endl;
}

void IRC::initCommand(void)
{
	this->cmd["CAP"] = &IRC::capLs;
	this->cmd["NICK"] = &IRC::nick;
	this->cmd["USER"] = &IRC::user;
	this->cmd["PASS"] = &IRC::pass;
	this->cmd["PING"]    = &IRC::ping;
	this->cmd["QUIT"]    = &IRC::quit;
	this->cmd["JOIN"]    = &IRC::join;
	this->cmd["PRIVMSG"] = &IRC::privmsg;
	this->cmd["KICK"]    = &IRC::kick;
	this->cmd["TOPIC"]   = &IRC::topic;
	this->cmd["MODE"]    = &IRC::mode;
	this->cmd["INVITE"]  = &IRC::invite;
	this->cmd["PART"]    = &IRC::part;
}

bool						IRC::ChannelExist(std::string name){
	for (std::vector<Channel>::iterator it = channels.begin(); it != channels.end(); ++it){
		if (it->getName() == name)
			return (true);
	}
	return (false);
}
//------------------- Setters ------------------------------------------------//
void					IRC::setChannels(Channel &newChannel)
{
	channels.push_back(newChannel);
}

//------------------- Getters ------------------------------------------------//
