/**
 * \class Server
 *
 * This class is responsible for handling all connection events. 
 *
 *
 */

#ifndef SERVER_H
#define SERVER_H

#define MAX_CLIENTS 10

#include "iserver.h"
#include "priv.h"
#include "user.h"
#include "login.h"
#include <string.h>
#include <iostream>
#include <fstream>
#include <algorithm>
#include <vector>
#include <list>
#include <netinet/in.h>
#include <sys/socket.h>
#include <error.h>
#include <stdio.h>
#include <unistd.h>
#include <sys/time.h>
#include <boost/algorithm/string.hpp>

class Server : public IServer
{
public:
    /// Create an Server with selected port number
    Server(int16_t a_port);
    ~Server();
    /// Method starting listetning on port for clients messages
    bool IStartListening(int16_t a_port) override;
    /// Methods allows to sending messages
    bool ISendMessage(std::string a_message, int16_t a_client) override;
    /// Method with loop in wich messages are handling
    void IIncommingConnection() override;
    /// Method responsible for setting port number
    bool ISetSocket(int16_t a_port);
    /// Method binding addres and port if it's allow
    bool IBindPort();
    /// Method read data of existing clients from file
    bool IReadFile();
    /// Method convert client descriptor to his login
    std::string IDescriptorToLogin(int a_client);
    /// Method covert client login to his descriptor
    int ILoginToDescriptor(std::string a_client);

private:
    int16_t m_port; ///< port number
    char m_buffer[100]; ///< buffer for messages
    struct sockaddr_in m_serverSocket, m_clientSocket;
    fd_set m_readfds,m_actfds; ///< set of connected descriptors
    int16_t m_sd; ///< server descriptor
    int16_t m_nfds; ///< number of file descriptors
    int16_t m_client; ///< client descriptor
    socklen_t m_len; 
    struct timeval m_tv;
    std::vector <int16_t> m_setClients; ///< vector of clients descriptors
    std::vector <User*> m_setUsers; ///< vector of logins and password
    std::fstream m_dataFile;
    Priv m_private; ///< object responsible for keeping groups vector
    std::list <Login*> m_setLogins; ///< list of online clients
    bool m_isAvailable; ///< flag 

};
// end of class Server
#endif // SERVER_H
