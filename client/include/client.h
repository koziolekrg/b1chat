#ifndef CLIENT_H
#define CLIENT_H

#include <stdlib.h>
#include <netinet/in.h>
#include <string.h>
#include <iostream>
#include <sys/socket.h>
#include <error.h>
#include <stdio.h>
#include <unistd.h>
#include <sys/time.h>
#include <vector>
#include <netdb.h>
#include <thread>
#include <arpa/inet.h> //inet_addr

#define COMPLETE 0
#define BUF_SIZE 256

class Client
{
public:
    Client(std::string a_hostAddress, int a_port);
    ~Client();
    int buffer_message(char * message);
    int find_network_newline(char * message, int inbuf);
    bool logIn(fd_set a_r_set);
    bool receiving(fd_set a_r_set);

private:
    int m_sock;
    struct sockaddr_in m_server;
    char m_message[256] , m_server_reply[256];
    int m_inbuf;
    int m_room;
    char *m_after;
    bool m_isLogIn;
    int m_menu;
};

#endif // CLIENT_H
