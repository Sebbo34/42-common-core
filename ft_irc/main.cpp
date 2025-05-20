#include "includes/Server.hpp"


int main(int ac, char **av) 
{
	if (ac == 3)
	{
		Server  server(atoi(av[1]), av[2]);
		try
		{
			signal(SIGINT, Server::SignalHandler);
			signal(SIGQUIT, Server::SignalHandler);
			server.start_server();
		}
		catch(std::string & chaine)
		{
			std::cerr << chaine << '\n';
		}
		catch(std::exception const & e)
		{
			std::cerr << e.what() << '\n';
		}
		return (0);
	}
	return (1);
}