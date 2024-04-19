/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   IRC.hpp                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbouguet <lbouguet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/27 14:32:05 by jquil             #+#    #+#             */
/*   Updated: 2024/04/19 15:26:09 by lbouguet         ###   ########.fr       */
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
	private :

		struct sockaddr_in	server, peer_addr;
		struct pollfd 		*poll_fds;
		socklen_t 			peer_addr_size;
		std::string 		mdp;
		bool 				secure;
		int 				port;
		int 				sock;
		int 				bind_sock;
		int 				lstn;
		int 				poll_count;

	public :
							IRC(int port, std::string mdp);
							~IRC();
		int					calloc_pollfd(int size);
		void				launch_serv(void);
		void 				Kick(void);
		void 				Invite(void);
		void 				Topic(void);
		void 				Mode(void);

	class client
	{
		private :

			std::string 	pass;
			std::string 	nick;
			std::string 	user;
			int sock;

		public :

			client(int sock, char *serv_rec, std::string mdp);
			std::string		GetPass();
			std::string 	GetNick();
			std::string 	GetUser();
			bool 			pass_check;// ?? 
			int 			GetSock();
	};

	bool check_pass(client cl);// ?? 
	class chanel
	{
		

	};

	class SocketFailedException:public std::exception
	{
		public :

		virtual const char *what() const throw();
	};

	class BindFailedException:public std::exception
	{
		public :

		virtual const char *what() const throw();
	};

	class ListenFailedException:public std::exception
	{
		public :

		virtual const char *what() const throw();
	};

	class AcceptFailedException:public std::exception
	{
		public :

		virtual const char *what() const throw();
	};
};
#endif
