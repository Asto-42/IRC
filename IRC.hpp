/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   IRC.hpp                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jquil <jquil@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/27 14:32:05 by jquil             #+#    #+#             */
/*   Updated: 2024/04/23 19:02:28 by jquil            ###   ########.fr       */
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
#include "rpl.hpp"

class Channel;

class IRC
{
	class client
	{
		private :
			std::string 	pass;
			std::string 	nick;
			std::string 	user;
			std::string		buffer;
			int			 	setup;
			int				sock;

		public :

			bool			pass_check;
							client();
							client(int sock);
			int				GetSock();
			int				GetSetup() const;
			std::string 	GetPass();
			std::string 	GetNick();
			std::string 	GetUser();
			std::string		GetBuffer() const;
			void			SetBuffer(std::string buf);
			void		SetPass(std::string pas);
			void 		SetNick(std::string nic);
			void 		SetUser(std::string use);
			void		SetSetup(int x);


	};

	class Channel
	{
		private:
			bool					isProtected;
			std::string				topic;
			std::string				name;
			std::vector<int>		operators;
			std::vector<int>		white_list;
			std::vector<client>		clients;
			int						limitClients;
			bool					privacy;
			Channel(void);

		public:
			std::string				getName(void);
			std::string				getTopic(void);
			std::vector<int>		getOperators(void);
			std::vector<client>		getClients(void);
			int						getLimitClients(void);
			bool					getIsProtected(void);
			void					setLimitClients(int limit);
			void					setName(std::string& name);
			void					setTopic(std::string& topic);
			void					setOperators(int& operateur);
			void					setClients(client& client);
			bool					isClient(std::string user);
			bool					isOperator(client &client);
			bool					add_client(client &new_client);
			bool					remove_client(std::string user);
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
		void 						sendRPL(std::string rpl, int fd);
		int							cmd_used_name(std::string &name, int mode);
		bool						capLs(client &client, std::string cmd);
		bool						pass(client &client, std::string cmd);
		bool						nick(client &client, std::string cmd);
		bool						user(client &client, std::string cmd);
		bool						privmsg(client &client, std::string cmd);
		// bool						privmsg_user(client &client, std::string cmd);
		bool						topic(client &client, std::string cmd);
		//bool						mode(client &client, std::string cmd);
		bool						ping(client &client, std::string cmd); // fait
		// bool						join(client &client, std::string cmd); // LUCAS
		// bool						part(client &client, std::string cmd); // LUCAS
		// bool						whois(client &client, std::string cmd); // Pas obligatoire, on verra plus tard
		bool						kick(client &client, std::string cmd); // fait MAIS a verifier + RPL a ajouter
		// bool						quit(client &client, std::string cmd); // LUCAS
		bool						invite(client &clients, std::string cmd); // RPL a ajouter
		// void 					Kick(void);
		// void 					Invite(void);
		// void 					Topic(void);
		// void 					Mode(void);
		bool						ChannelExist(std::string name);
									IRC(int port, std::string mdp);
									~IRC();

	bool check_pass(client cl);
};
#endif
