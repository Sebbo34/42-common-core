/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Server.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lchiu <lchiu@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/25 18:14:34 by sbo               #+#    #+#             */
/*   Updated: 2024/08/14 13:15:33 by lchiu            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/Server.hpp"
#include <netinet/in.h>

/* ======================================= Canonical form ======================================= */

Server::Server(int port, std::string pswd) : _port(port), _pwd(pswd)
{
	std::cout << "Server running" << std::endl;
}

Server::~Server()
{
	std::cout << "Server shutting down" << std::endl;
	for (unsigned int i = 0; i < _pollFds.size(); i++)
		close(_pollFds[i].fd);
	if (_pollFds.size() != 0)
		_pollFds.clear();
}

/* ============================================ Utils ============================================ */

int g_SIG;

void    Server::SignalHandler(int signum)
{
	(void)signum;
	g_SIG = 1;
}

void    Server::error(int serverSocket, int clientSocket, std::string msg)
{
	close(serverSocket);
	if (clientSocket != -1)
	{
		for (unsigned int i = 0; i < _pollFds.size(); i++)
		{
			if (_pollFds[i].fd != _serverSocket)
				close(_pollFds[i].fd);
		}
	}
	if (_pollFds.size() != 0)
		_pollFds.clear();
	throw std::string (msg);
}

void Server::response(std::string str, int fd)
{
	if (send(fd, str.c_str(), str.size(), MSG_NOSIGNAL) == -1)
		std::cerr << "Error: send() failed: " << strerror(errno) << std::endl;
}

void	Server::empty_chanel(std::string chanel)
{
	if (_channels[chanel].getUsers().size() == 0 && _channels[chanel].getOperators().size() == 0)
	{
        _channels[chanel].setInviteOnly(false);
        _channels[chanel].setOptionT(false);
        _channels[chanel].setPass("/0");
		_channels[chanel].setLimit(0);
		_channels[chanel].getInvitation().clear(); // remove invitation sent
		if (_channels[chanel].getTopic().size() != 0)
			_channels[chanel].clearTopic(); // remove topic
	}
}

/* ============================================= Server ================================================ */

int        Server::client_message(int i)
{
    std::vector<std::string> cmd;

    memset(_buf, 0, sizeof(_buf)); //-> clear the buffer in case any mem residue is left
    _bytesRead = recv(_pollFds[i].fd, _buf, sizeof(_buf), MSG_DONTWAIT); // utilise sur un socket connecte + MSG_DONTWAIT = appel non bloc
    if (_bytesRead == -1)
	{
        error(_serverSocket, _clientSocket, "Error: recv() failed");
	}
    if (_bytesRead == 0)
    {
        quit(_users[i - 1]);
		std::cout << "Client " << _pollFds[i].fd << " is disconnected" << std::endl;
        close(_pollFds[i].fd); // close the connection
        _pollFds.erase(_pollFds.begin() + i);
        return (-1);
    }
    else
        handleClientMessage(i - 1);
    return (0);
}

void    Server::client_connection()
{
   _clientSocket = accept(_serverSocket, (sockaddr *)&_serverAddress, &_len);
	if (_clientSocket == -1)
		error(_serverSocket, _clientSocket, "Error: accept() failed");
	if (fcntl(_clientSocket, F_SETFD, O_NONBLOCK) == -1)
		error(_clientSocket, _clientSocket, "failed to set option (O_NONBLOCK) on socket");
	AddClient(_clientSocket);
	struct pollfd Client_pollfd = {};
	Client_pollfd.fd = _clientSocket;
	Client_pollfd.events = POLLIN;
	Client_pollfd.revents = 0;
	_pollFds.push_back(Client_pollfd);
	std::cout << "Connection accepted for client " << _clientSocket << std::endl;

}

void    Server::handle_client()
{
    while (g_SIG == 0)
    {
        _ret = poll(_pollFds.data(), _pollFds.size(), -1); // detecter si un evenment se passe (-1 pour attente indefini d'event)
        if (g_SIG == 0)
        {
            if (_ret == -1)
                error(_serverSocket, _clientSocket, "Error: poll() failed");
            for (unsigned int i = 0; i < _pollFds.size(); i++)
            {
                // Vérifie si le bit correspondant à POLLIN est défini dans _pollFds[i].revents
                if (_pollFds[i].revents & POLLIN) // evenement detecter et donnees pretes a etre lues (operation de bits)
                {
                    if (_pollFds[i].fd == _serverSocket) // trouver une autre condition 
                    {
                        // si even happen on server socket alors il s'agit d'une co
                        client_connection();
                    }
                    else // not server socket, therefore an existing connection must be readable
                    {   
                        if (client_message(i) == -1)
                            continue;
                    }
                }
            }
        }
    }
}

void	Server::start_server()
{
	_serverAddress.sin_family = AF_INET; // ipv4
	_serverAddress.sin_port = htons(_port); // convert the port to network byte order
	_serverAddress.sin_addr.s_addr = INADDR_ANY; // set the address to any local machine address
	_serverSocket = socket(AF_INET, SOCK_STREAM, 0); // Identifiant de la socket (fd)
	if (_serverSocket < 0)
		throw std::string("Error: socket() failed");
	int en = 1;
	if (setsockopt(_serverSocket, SOL_SOCKET, SO_REUSEADDR, &en, sizeof(en)) == -1) //-> set the socket option (SO_REUSEADDR) to reuse the address + SOL_SOCKET = au niveau du  noyau + 1 = activer l'option SO_REUSEADDR
		throw(std::runtime_error("faild to set option (SO_REUSEADDR) on socket"));
	if (fcntl(_serverSocket, F_SETFD, O_NONBLOCK) == -1) // (O_NONBLOCK) non-blocking socket
		error(_serverSocket, -1, "server faild to set option (O_NONBLOCK) on socket");
	if (bind(_serverSocket, (struct sockaddr*)&_serverAddress, sizeof(_serverAddress)) != 0)
		error(_serverSocket, -1, "Error: bind() failed");
	if (listen(_serverSocket, 5) != 0)
		error(_serverSocket, -1, "Error: listen() failed");

	_len = sizeof(_serverAddress);

	struct pollfd Server_pollfd = {}; // initialisation val par defaut (tout a 0)
	Server_pollfd.fd = _serverSocket; // surveiller le descipteur du server
	Server_pollfd.events = POLLIN; // surveiller event: qd les donnees sont dispo en lecture sur le socket
	Server_pollfd.revents = 0;
	_pollFds.push_back(Server_pollfd);
	handle_client();
	close(_serverSocket);
}
