#include "../includes/Server.hpp"
#include "../includes/channel.hpp"

/* ======================================= Utils ======================================= */

std::vector<std::string> Server::split_cmd(const std::string& buf)
{
    std::vector<std::string> cmd_list;
    std::string line;
    std::istringstream data(buf);

    while (std::getline(data, line))
    {
        size_t pos = line.find_first_of("\r\n");
        if (pos != std::string::npos)
            line = line.substr(0, pos);
        if (!line.empty())
        {
            std::istringstream line_stream(line);
            std::string word;
            while (line_stream >> word)
                cmd_list.push_back(word);
        }
    }
    return (cmd_list);
}

/* ====================================================================================== */

void    Server::handleMode(int fd, const std::string & buf)
{
    int                                 sign = 0;
    std::string                         msg;
    std::vector<std::string>            cmd_list;
    std::vector<std::string>            vectChannel;
    std::vector<std::string>::iterator  it;

    cmd_list = split_cmd(buf);
    if (cmd_list.size() <= 2)
    {
        response(ERR_NEEDMOREPARAMS( _users[fd].getNickName(), cmd_list[0]), _users[fd].getSocket());
        return;
    }
    else if (cmd_list.size() >= 3)
    {
        vectChannel = parseChannelRecv(cmd_list[1]);
        const std::string& mode_change = cmd_list[2];
        if (mode_change[0] == '+')
            sign = 1;
        else if (mode_change[0] == '-')
            sign = 2;
        else // inutile en soit car buf recoit +i meme quand c'est juste i
        {
            response(ERR_UNKNOWNMODE( _users[fd].getNickName(), cmd_list[2]), _users[fd].getSocket());
            return;
        }
        for (it = vectChannel.begin(); it != vectChannel.end(); it++)
        {
            if (cmd_list[1] == _users[fd].getNickName() || cmd_list[1] == _users[fd].getNickName() + "-") // /mode nickname +i || /mode nickname- +i --> mode invisible : ignorer
                continue ;
            else if (_channels.find(*it) == _channels.end()) // Le canal n'existe pas
            {
                std::cout << *it <<  " No such channel" << std::endl;
                continue;
            }
            if (!isNickIn(_channels[*it].getOperators(), _users[fd].getNickName()))
            {
                response(ERR_CHANOPRIVSNEEDED( _users[fd].getNickName(), cmd_list[1]), _users[fd].getSocket());
                std::cout << (*it) << " You're not channel operator" << std::endl;
                continue;
            }
            if (mode_change.length() == 2 && (mode_change[0] == '+' || mode_change[0] == '-') && mode_change[1] == 'i')
                option_i(fd, cmd_list, sign, *it);
            else if (mode_change.length() == 2 && (mode_change[0] == '+' || mode_change[0] == '-') && mode_change[1] == 't')
                option_tt(fd, cmd_list, sign, *it);
            else if (mode_change.length() == 2 && (mode_change[0] == '+' || mode_change[0] == '-') && mode_change[1] == 'k')
                option_k(fd, cmd_list, sign, *it);
            else if (mode_change.length() == 2 && (mode_change[0] == '+' || mode_change[0] == '-') && mode_change[1] == 'o')
                option_o(fd, cmd_list, sign, *it);
            else if (mode_change.length() == 2 && (mode_change[0] == '+' || mode_change[0] == '-') && mode_change[1] == 'l')
                option_l(fd, cmd_list, sign, *it);
        }
    }
}

// Définir/supprimer le canal sur invitation uniquement
void    Server::option_i(int fd, std::vector<std::string> cmd_list, int sign, std::string chanelName)
{
    std::string msg;

    if (sign == 1)
    {
        _channels[chanelName].setInviteOnly(true);
        response(RPL_CHANNELMODEIS_NOARG(chanelName, "324", cmd_list[2]), _users[fd].getSocket());
        sendRPL(_channels[chanelName], RPL_CHANNELMODEIS_NOARG(chanelName, "MODE", cmd_list[2]));
    }
    else if (sign == 2)
    {
        _channels[chanelName].setInviteOnly(false);
        response(RPL_CHANNELMODEIS_NOARG(chanelName, "324", cmd_list[2]), _users[fd].getSocket());
        sendRPL(_channels[chanelName], RPL_CHANNELMODEIS_NOARG(chanelName, "MODE", cmd_list[2]));
    }
}
// /connect localhost 6667 pswd
// /NICK lele
// /JOIN chanel
// /MODE #chanel +i

// Définir/supprimer les restrictions de la commande TOPIC pour les op
void    Server::option_tt(int fd, std::vector<std::string> cmd_list, int sign, std::string chanelName)
{
    std::string msg;

    if (sign == 1)
    {
        _channels[chanelName].setOptionT(true);
        response(RPL_CHANNELMODEIS_NOARG(chanelName, "324", cmd_list[2]), _users[fd].getSocket());
        sendRPL(_channels[chanelName], RPL_CHANNELMODEIS_NOARG(chanelName, "MODE", cmd_list[2]));
    }
    else if (sign == 2)
    {
        if (!_channels[chanelName].getOperators().empty())
        {
            _channels[chanelName].setOptionT(false);
            response(RPL_CHANNELMODEIS_NOARG(chanelName, "324", cmd_list[2]), _users[fd].getSocket());
            sendRPL(_channels[chanelName], RPL_CHANNELMODEIS_NOARG(chanelName, "MODE", cmd_list[2]));
        }
    }
}
// /connect localhost 6667 pswd
// /NICK lele
// /JOIN chanel
// /MODE #chanel +t
// /TOPIC new

// Donner/retirer le privilège de l’opérateur de canal
void    Server::option_o(int fd, std::vector<std::string> cmd_list, int sign, std::string chanelName)
{
    std::string msg;

    if (sign == 1 && cmd_list.size() == 4)
    {
        int user_to_op = getIndUserByNN(_channels[chanelName].getUsers(), cmd_list[3]);
        if (user_to_op == -1)
        {
            msg = ":" + _users[fd].getNickName() + " 441 " + chanelName + " " + cmd_list[3] + ":isn't on that channel" + " +l\r\n";
            send(_users[fd].getSocket(), msg.c_str(), msg.length(), 0);
        }
        else
        {
            user promotedUser = _channels[chanelName].getUsers()[user_to_op];
            _channels[chanelName].getOperators().push_back(promotedUser); // rajouter dans op
            _channels[chanelName].getUsers().erase(_channels[chanelName].getUsers().begin() + user_to_op);
            response(RPL_CHANNELMODEIS_ARG(chanelName, "324", cmd_list[2], cmd_list[3]), _users[fd].getSocket());
            sendRPL(_channels[chanelName], RPL_CHANNELMODEIS_ARG(chanelName, "MODE", cmd_list[2], cmd_list[3]));
        }
    }
    else if (sign == 2 && cmd_list.size() == 4)
    {
        int op_to_user = getIndUserByNN(_channels[chanelName].getOperators(), cmd_list[3]);
        if (!_channels[chanelName].getOperators().empty() && op_to_user != -1)
        {
            user demoteUser = _channels[chanelName].getOperators()[op_to_user];
            _channels[chanelName].getUsers().push_back(demoteUser); // rajouter dans op
            _channels[chanelName].getOperators().erase(_channels[chanelName].getOperators().begin() + op_to_user);
            response(RPL_CHANNELMODEIS_ARG(chanelName, "324", cmd_list[2], cmd_list[3]), _users[fd].getSocket());
            sendRPL(_channels[chanelName], RPL_CHANNELMODEIS_ARG(chanelName, "MODE", cmd_list[2], cmd_list[3]));
        }
    }
}
// /connect localhost 6667 pswd
// /NICK lele
// /JOIN chanel
// /MODE #chanel +o lele

void    Server::option_k(int fd, std::vector<std::string> cmd_list, int sign, std::string chanelName)
{
    std::string msg;

    if (sign == 1 && cmd_list.size() == 4)
    {
        _channels[chanelName].setPass(cmd_list[3]);
        response(RPL_CHANNELMODEIS_ARG(chanelName, "324", cmd_list[2], cmd_list[3]), _users[fd].getSocket());
        sendRPL(_channels[chanelName], RPL_CHANNELMODEIS_ARG(chanelName, "MODE", cmd_list[2], cmd_list[3]));
    }
    else if (sign == 2)
    {
        _channels[chanelName].setPass("/0");
        response(RPL_CHANNELMODEIS_NOARG(chanelName, "324", cmd_list[2]), _users[fd].getSocket());
        sendRPL(_channels[chanelName], RPL_CHANNELMODEIS_NOARG(chanelName, "MODE", cmd_list[2]));
    }
}
// /connect localhost 6667 pswd
// /NICK lele
// /JOIN chanel
// /MODE #chanel +k pass

void Server::option_l(int fd, std::vector<std::string> cmd_list, int sign, std::string chanelName)
{
    std::string msg;

    if (sign == 1) // add limit
    {
        int limit = std::atoi(cmd_list[3].c_str());
        if (limit <= 0 || limit < _channels[chanelName].getuserNb())
        {
            response(ERR_INVALIDLIMIT(_users[fd].getNickName(), chanelName), _users[fd].getSocket());
            return;
        }
        _channels[chanelName].setLimit(limit);
        response(RPL_CHANNELMODEIS_ARG(chanelName, "324", cmd_list[2], cmd_list[3]), _users[fd].getSocket());
        sendRPL(_channels[chanelName], RPL_CHANNELMODEIS_ARG(chanelName, "MODE", cmd_list[2], cmd_list[3]));
    }
    else if (sign == 2) // del limit
    {
        _channels[chanelName].setLimit(0);
        response(RPL_CHANNELMODEIS_NOARG(chanelName, "324", cmd_list[2]), _users[fd].getSocket());
        sendRPL(_channels[chanelName], RPL_CHANNELMODEIS_NOARG(chanelName, "MODE", cmd_list[2]));
    }
}
// /connect localhost 6667 pswd
// /NICK lele
// /JOIN chanel
// /MODE #chanel +l 1
