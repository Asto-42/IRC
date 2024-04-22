/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   IRC.hpp                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbouguet <lbouguet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/27 14:32:05 by jquil             #+#    #+#             */
/*   Updated: 2024/04/22 18:10:50 by lbouguet         ###   ########.fr       */
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
			std::string		buffer;
			int sock;

		public :

			int			 	set;
			bool			pass_check;
							client();
							client(int sock);
			int				GetSock();
			std::string 	GetPass();
			std::string 	GetNick();
			std::string 	GetUser();
			std::string		GetBuffer();
			void		SetBuffer(std::string buf);
			void		SetPass(std::string pas);
			void 		SetNick(std::string nic);


	};

	class Channel
	{
		private:
			std::string				topic;
			std::string				name;
			std::vector<int>		operators;
			int						topicOperators[10];
			std::vector<client>		clients;
			int						LimitClients;
			Channel(void);

		public:
			std::string				getName(void);
			std::string				getTopic(void);
			std::vector<int>		getOperators(void);
			int						*getTopicOperators(void);
			std::vector<client>		getClients(void);
			int						getLimitClients(void);
			int						setLimitClients(int limit);
			void					setName(std::string& name);
			void					setTopic(std::string& topic);
			void					setOperators(int& operateur);
			void					setTopicOperators(client &client);
			void					setClients(client& client);
			Channel(std::string name, client &creator);
			~Channel();
	};

	private :

		std::string 				mdp;
		socklen_t					peer_addr_size;
		struct sockaddr_in 			server, peer_addr;
		struct pollfd 				*poll_fds;
		std::map<int, client>		users;
		std::map<std::string, bool (IRC::*)(client&, std::string)>	cmd;
		std::vector<Channel> 		channels;
		int							poll_count;
		int							poll_size;
		int							port;
		int							sock;
		int							bind_sock;
		int							lstn;
		bool							secure;

	public :

		int							calloc_pollfd(int size);
		int 						add_poll_fds(int fd);
		void 						launch_serv(void);
		void 						manage_input(int fd);
		void						initCommand(void);
		bool						capLs(client &client, std::string cmd);
		bool						pass(client &client, std::string cmd);
		bool						nick(client &client, std::string cmd);
		// bool						user(client &client, std::string cmd);
		// bool						ping(client &client, std::string cmd);
		// bool						join(client &client, std::string cmd);
		// bool						part(client &client, std::string cmd);
		// bool						privmsg(client &client, std::string cmd);
		// bool						privmsg_user(client &client, std::string cmd);
		bool						topic(client &client, std::string cmd);
		// bool						mode(client &client, std::string cmd);
		// bool						oper(client &client, std::string cmd);
		// bool						whois(client &client, std::string cmd);
		// bool						kick(client &client, std::string cmd);
		// bool						quit(client &client, std::string cmd);
		// bool						invite(client &client, std::string cmd);
		// void 						Kick(void);
		// void 						Invite(void);
		//void 						Topic(void);
		// void 						Mode(void);
									IRC(int port, std::string mdp);
									~IRC();

	bool check_pass(client cl);
};
#endif
