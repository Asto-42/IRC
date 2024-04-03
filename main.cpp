/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jquil <jquil@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/28 15:41:53 by jquil             #+#    #+#             */
/*   Updated: 2024/04/03 16:58:41 by jquil            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "IRC.hpp"
/*
int socket(int domain, int type, int protocol) -> renvoi un descripteur
->Un socket, qu’il soit TCP ou UDP, sera défini par un simple entier qui devra être
passé aux fonctions qui l’utilisent.
Sur plateformes UNIX il s’agira d’un descripteur de fichier.

Un socket TCP représente un lien direct avec une machine distante et est une route d’échange de données bilatérale avec celle-ci.

Un socket TCP sera utilisé pour envoyer des données à la machine distante qu’il représente,
mais également pour en recevoir de cette dernière.

le code erreur est dispo sur errno (include errno.h)

hton / ntoh
hton converti la data en big-endian (afin de pouvoir etre envoye) soit Host/Home vers reseau
noth converti -> reseau vers Host/Home

short htons(short value);
long htonl(long value);

short htons(short value);
long htonl(long value);



creer une socket :

int socket(int family, int type, int protocol);
family ->AF_INET pour IPv4
       ->AF_INET6 pour IPv6
type -> SOCK_STREAM pour TCP
     -> SOCK_DGRAM pour UDP
protocol -> IPPROTO_TCP dans notre cas ?

socket return -1 en cas d'erreur (penser a secure)

int close(int socket) -> Ferme le socket

Pour créer le paramètre server , on utilise une structure sockaddr_in à initialiser ainsi :
sockaddr_in server;
server.sin_addr.s_addr = inet_addr(const char* ipaddress);
server.sin_family = AF_INET;
server.sin_port = htons(int port);



Choice
int poll(struct pollfd *fds, nfds_t nfds, int délai) ->
OR
int select(int nfds, fd_set *readfds, fd_set *writefds, fd_set *exceptfds, struct timeval *timeout) ->

Fait la meme mais Poll est mieux, select c'est dla merde mais c'est ce qui est utilise sur l'exam



Connecter un client au serveur :
dans un terminal :

irssi
/connect localhost XXXX mdp
/rawlog open ~/IRC_githubed/logs

XXXX = numero de port (premier argument du serveur)
mdp = reflechi serieux (deuxieme argument du serveur)
*/

/*
Doc interessante :
https://webusers.i3s.unice.fr/~tettaman/Classes/L2I/ProgSys/11_IntroSockets.pdf
https://www.codequoi.com/programmation-reseau-via-socket-en-c/#surveiller_les_sockets_avec_select
*/



int	main(int argc, char **argv)
{
	if (argc != 3)
	{
		std::cout << "Invalid argument(s)" << std::endl;
		return (0);
	}
	IRC serv(atoi(argv[1]), argv[2]);
	serv.launch_serv();
	return (0);
}
