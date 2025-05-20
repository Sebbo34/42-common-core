#ifndef SERVER_HPP
# define SERVER_HPP

# include <iostream>
# include <string>
# include <sys/types.h>
# include <sys/socket.h>
# include <exception>
# include <netinet/in.h>
# include <arpa/inet.h>
# include <unistd.h>
# include <cstdlib>
# include <cstring>
# include <fcntl.h>
# include <csignal>
# include <poll.h>
# include <sys/types.h>
# include <vector>
# include <map>
# include <sstream>
# include <cstring>
# include <cerrno>
# include <sstream>
#include <algorithm>

# include "channel.hpp"

#define CRLF "\r\n"
#define ERR_NOTEXTTOSEND(nickname) ("412 " + nickname + " :No text to send" + CRLF)
#define ERR_NEEDMOREPARAMS(client, cmd)(":localhost 461 " + client + " " + cmd + " :Not enough parameters" + CRLF)
#define ERR_UNKNOWNMODE(client, cmd)(":localhost 472 " + client + " " + cmd + " :is unknown mode" + CRLF)
#define ERR_CHANOPRIVSNEEDED(client, cmd)(":localhost 482 " + client + " " + cmd + " :You're not channel operator" + CRLF)
#define RPL_CHANNELMODEIS_NOARG(chanelName, mode, option)(":localhost " + std::string(mode) + " " + chanelName + " " + option + " " + CRLF)
#define RPL_CHANNELMODEIS_ARG(chanelName, mode, option, arg)(":localhost " + std::string(mode) + " " + chanelName + " " + option + " " + arg + CRLF)
#define ERR_INVALIDLIMIT(client, chanelName)(": 461 " + client + " " + chanelName + " :Invalid user limit" + CRLF)
#define ERR_INVITEONLYCHAN(client, channelName)(":server 473 " + client + " " + channelName + " :Cannot join channel" + CRLF)
#define ERR_CHANNELISFULL(client, channelName)(":server 471 " + client + " " + channelName + " :Cannot join channel (Channel is full)" + CRLF)
#define ERR_BADCHANNELKEY(client, cmd)(": 475 " + client + " " + cmd + " :Not enough parameters" + CRLF)
#define RPL_JOIN(prefix, chan) ( prefix + "JOIN " + chan + CRLF)
#define RPL_ENDOFNAMES(hostName,nickName,chan) ( ":" + hostName + " 366 " + nickName + " " + chan + " :End of NAMES list" + CRLF)
#define RPL_NAMREPLY(hostName,nickName,chan, names) ( ":" + hostName + " 353 " + nickName + chan + names + CRLF)
#define RPL_TOPIC_SET(topicSetter, chan, topic) ("332 " +  topicSetter + " "+ chan + " " + topic + CRLF)
#define RPL_TOPICWHOTIME(topicSetter, chan, timestamp) ("333 " +  topicSetter + " "+ chan + " " + topicSetter + " " + timestamp + CRLF)
#define RPL_INV(prefix, guest, chan) ( prefix + "INVITE " + guest + " " + chan + CRLF)
#define RPL_PING_INV(chan, sender, guest) ( ": NOTICE " + chan + " :" + sender + " invited " + guest + " into channel " + chan + CRLF)
#define RPL_USERONCHANNEL(sender, guest, chan) ( "442 "+ sender + " " + guest + " " + chan + " :is already on channel" + CRLF)
#define RPL_TOPIC(prefix, chan, topic) ( prefix + "TOPIC " + chan + " " + topic + CRLF)
#define RPL_KICK(prefix, chan, UTK, msg) ( prefix + "KICK " + chan + " " + UTK + msg + CRLF)
#define ERR_USERNOTINCHANNEL(sender, UTK, chan) ("441 " + sender + " " + UTK + " " + chan + " :They aren't on that channel" + CRLF)
#define RPL_NEWNICK(chan ,oldNick, newNick) (": NOTICE " + chan + " :" + oldNick + " change to " + newNick + CRLF)
#define RPL_NICK(oldNick, newNick) (":" + oldNick + " NICK " + newNick + CRLF)
#define RPL_ERR_NICKNAMEINUSE(nickName) ("433 * " + nickName + " :" + nickName + " is already in use" + CRLF)
#define RPL_ERRONEUSNICKNAME(nickName, invalidNN) ("432 " + nickName + " " + invalidNN + " :Erroneus nickname" + CRLF)
#define RPL_PART(prefix, chan, msg) ( prefix + "PART " + chan + " " + msg + CRLF)
#define RPL_PRIVMSG(prefix, chan, msg) ( prefix + "PRIVMSG " + chan + " " + msg + CRLF)
#define RPL_USER_NOT_FOUND(nickName, target) ("NOTICE " + nickName + " :" + target + " is not available" + CRLF)
#define RPL_NEEDMOREPARAMS(nickName, cmd) ("461 " + nickName + " " + cmd + " :Not enough parameters" + CRLF)
#define RPL_ALREADYREGISTERED(nickName) ("462 " + nickName + " :You may not reregister" + CRLF)
#define RPL_UNKNOWCOMMAND(nickName, cmd) ("421 " + nickName + " " + cmd + " UNKNOWCOMMAND" + CRLF)
#define RPL_QUIT(prefix, chan, msg) ( prefix + "QUIT " + chan + " :" + msg + CRLF)
#define RPL_PONG(prefix, word) ( prefix + "PONG " + word + CRLF)


class Server
{
	public:

		Server(int port, std::string pswd);
		~Server();
		void    	start_server();
		static void SignalHandler(int signum);

	private:
        int             				_port;
		std::string						_pwd;
		sockaddr_in						_serverAddress;
		int								_serverSocket;
		int								_clientSocket;
		struct pollfd					_pollServerFd;
		int								_ret;
		int								_bytesRead;
		socklen_t						_len;
		char							_buf[1024];
		std::vector<pollfd>				_pollFds;
		std::vector<std::string>		_cmd;
		std::map<std::string,channel>	_channels;
		std::vector<user>				_users;


		void			error(int serverSocket, int clientSocket, std::string msg);
		void			handle_client();
		void			client_connection();
		bool			AddClient(int ClientSocket);
		int				client_message(int i);
        void			response(std::string str, int fd);

		void			handleClientMessage(int i);
		void			join(int i, protocol *prot);
		void			nick(int i, std::string nickname);
		void			sendToUser(int i, protocol *prot);
		void			sendToChannel(int i, protocol *prot);
		void			part(int i, protocol *prot);
		void			kick(int i, protocol *prot);
		void			topic(int i, protocol *prot);
		void			invite(int i, protocol *prot);
		void			quit(user user1);
		void			userhost(int i, protocol *prot);
		void			setUser(int i, protocol *prot);
		void			pass(int i, protocol *prot);
		void			privMsg(int i, protocol *prot);
		void			CapLs(int i, protocol *prot);
		void			connectUser(int i);
		void			empty_chanel(std::string chanel);


		void    					handleMode(int fd, const std::string & buf);
		std::vector<std::string>	split_cmd(const std::string& buf);
		void    					option_i(int fd, std::vector<std::string> cmd_list, int sign, std::string chanelName);
		void    					option_tt(int fd, std::vector<std::string> cmd_list, int sign, std::string chanelName);
		void    					option_k(int fd, std::vector<std::string> cmd_list, int sign, std::string chanelName);
		void    					option_o(int fd, std::vector<std::string> cmd_list, int sign, std::string chanelName);
		void    					option_l(int fd, std::vector<std::string> cmd_list, int sign, std::string chanelName);
		int     					check_canal_access(protocol *prot, std::string channelName, int i);
		void						sendRPL(channel chan, std::string RPL);
		void						setTopicForNewUser(int socket, std::vector<std::string> topic, std::string ChannelName);
		bool						checkBuffer(int i);

};

int							getSocketByNN(std::vector<user> users, std::string nickName);
int							getIndUserByNN(std::vector<user> users, std::string nickName);
bool						isNickIn(std::vector<user> users, std::string newNickName);
bool						isStrInVect(std::vector<std::string> vect, std::string str);
std::vector<std::string>	parseChannelRecv(std::string channels);
std::string					getWord(std::string str, int ind);
std::string					extractName(channel chan);
std::string					to_str(time_t value);

void						send_newNick(std::map<std::string,channel> &channels,user user1, std::string newNick);
void						sendError(user target, std::string number, std::string channel, std::string msg);
void						ft_send(int socket, std::string msg);
std::string					addPrefix(user userNames);
std::string					PrefixOp(user userNames, int i);

#endif