#ifndef SERVER_H
#define SERVER_H

#define MAX_CLIENTS 10

#include "iserver.h"
#include "priv.h"
#include "user.h"
#include <string.h>
#include <iostream>
#include <fstream>
#include <algorithm>
#include <vector>
#include <netinet/in.h>
#include <sys/socket.h>
#include <error.h>
#include <stdio.h>
#include <unistd.h>
#include <sys/time.h>
#include <boost/algorithm/string.hpp>

class Login
{
private:
    int16_t fd;
    std::string login;
public:
    Login(int16_t a_fd, std::string a_login):fd(a_fd), login(a_login){}
    int16_t getFd(){return fd;}
    std::string getLogin(){return login;}
};

class Server : public IServer
{
public:
    Server(int16_t a_port);
    ~Server();
    bool IStartListening(int16_t a_port) override;
    bool ISendMessage(std::string a_message, int16_t a_client) override;
    void IIncommingConnection() override;
    bool setSocket(int16_t a_port);
    bool bindPort(int16_t a_port);
    bool readFile();
    std::string descriptorToLogin(int a_client);
    int loginToDescriptor(std::string a_client);

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
    std::vector <Login*> m_setLogins;

};

#endif // SERVER_H
