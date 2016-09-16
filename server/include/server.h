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
    Server(int16_t a_port);
    ~Server();
    bool IStartListening(int16_t a_port) override;
    bool ISendMessage(std::string a_message, int16_t a_client) override;
    void IIncommingConnection() override;
    bool ISetSocket(int16_t a_port);
    bool IBindPort();
    bool IReadFile();
    std::string IDescriptorToLogin(int a_client);
    int ILoginToDescriptor(std::string a_client);

private:
    int16_t m_port;
    char m_buffer[100];
    struct sockaddr_in m_serverSocket, m_clientSocket;
    fd_set m_readfds,m_actfds;
    int16_t m_sd; //server descriptor
    int16_t m_nfds; // number of file descriptors
    int16_t m_client;
    socklen_t m_len;
    struct timeval m_tv;
    std::vector <int16_t> m_setClients; // set of clients descriptors
    std::vector <User*> m_setUsers; // set of logins data
    std::fstream m_dataFile;
    Priv m_private;
    std::list <Login*> m_setLogins;
    bool m_isAvailable;

};

#endif // SERVER_H
