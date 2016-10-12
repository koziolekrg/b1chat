#ifndef ISOCKET_H
#define ISOCKET_H

#include <string>
#include <vector>
#include <netinet/in.h>
#include <sys/socket.h>
#include <unistd.h>

class ISocket
{
public:
    virtual ~ISocket(){}
    virtual bool Bind(int16_t &a_sd, sockaddr_in &a_serverSocket)=0;
    virtual bool Connect(int16_t &a_sd)=0;
    virtual void SetSocket(int16_t &a_sd, timeval &a_tv,sockaddr_in &a_serverSocket, int16_t a_port)=0;
    virtual void Listen(int16_t a_sd)=0;
    virtual bool Send(int16_t fd, std::string a_message)= 0;
    virtual bool Receive(int16_t a_setClient,char *a_buffer)=0;
    virtual std::string getAddress(int16_t a_sd)=0;
};

#endif // ISOCKET_H
