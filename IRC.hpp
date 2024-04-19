/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   IRC.hpp                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jquil <jquil@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/27 14:32:05 by jquil             #+#    #+#             */
/*   Updated: 2024/04/19 18:01:26 by jquil            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef IRC_HPP
# define IRC_HPP

#include <iostream>
#include <cstdio>
#include <iomanip>
#include <iostream>
#include <fstream>
#include <stdlib.h>
#include <ios>
#include <algorithm>
#include <signal.h>
#include <vector>
#include <math.h>
#include <cmath>
#include <time.h>
#include <string.h>
#include <limits.h>
#include <cctype>
#include <cstdlib>
#include <stdint.h>
#include <vector>
#include <map>
#include <sstream>
#include <ctime>
#include <stack>
#include <cstring>
#include <errno.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h> // sockaddr_in, IPPROTO_TCP
#include <arpa/inet.h> // hton*, ntoh*, inet_addr
#include <unistd.h>  // close
#include <cerrno>
#include <poll.h>
#include <sys/epoll.h>

class IRC
{
	class client
	{
		private :

			std::string 	pass;
			std::string 	nick;
			std::string 	user;
			int sock;

		public :

			bool 			pass_check;
							client();
							client(int sock, char *serv_rec, std::string mdp);
			int				GetSock();
			std::string 	GetPass();
			std::string 	GetNick();
			std::string 	GetUser();
	};

	class Channel
	{
		private:
			std::string				topic;
			std::string				name;
			std::vector<int>		operators;
			std::vector<client>		clients;
			Channel(void);

		public:
			std::string				getName(void);
			std::string				getTopic(void);
			std::vector<int>		getOperators(void);
			std::vector<client>		getClients(void);
			void					setName(std::string& name);
			void					setTopic(std::string& topic);
			void					setOperators(int& operateur);
			void					setClients(client& client);
			Channel(std::string name, client &creator);
			~Channel();
	};

	private :

	std::string mdp;
	socklen_t peer_addr_size;
	struct sockaddr_in server, peer_addr;
	struct pollfd *poll_fds;
	std::map<int, client>	users;
	int poll_count;
	int poll_size;
	int port;
	int sock;
	int bind_sock;
	int lstn;
	bool secure;

	public :

	IRC(int port, std::string mdp);
	~IRC();
	int calloc_pollfd(int size);
	int add_poll_fds(int fd);
	void launch_serv(void);
	void manage_input(int x);
	void Kick(void);
	void Invite(void);
	void Topic(void);
	void Mode(void);

	bool check_pass(client cl);
};
#endif
