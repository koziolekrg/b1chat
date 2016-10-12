#ifndef SOCKET_H
#define SOCKET_H

#include <string.h>
#include <iostream>
#include <netinet/in.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <sys/ioctl.h>
#include <arpa/inet.h>
#include <net/if.h>
#include <unistd.h>
#include "isocket.h"

using namespace std;

class Socket : public ISocket
{
public:

    Socket();
    virtual ~Socket();
    bool Bind(int16_t &a_sd, sockaddr_in &a_serverSocket);
    bool Connect(int16_t &a_sd);
    void SetSocket(int16_t &a_sd, timeval &a_tv,sockaddr_in &a_serverSocket, int16_t a_port);
    void Listen(int16_t a_sd);
    bool Send(int16_t fd, string a_message);
    bool Receive(int16_t a_setClient,char *a_buffer);
    std::string getAddress(int16_t a_sd);
};

// end of class Socket
#endif // SOCKET_H
