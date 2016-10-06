#ifndef ISOCKET_H
#define ISOCKET_H

#include <string>
#include <vector>

class ISocket
{
public:
    virtual ~ISocket(){}
    virtual int16_t Connect(int16_t a_sock, sockaddr_in &a_server) = 0;
    virtual int16_t SetSocket() = 0;
    virtual int16_t Send(int16_t m_sock, std::string a_message) = 0;
    virtual int16_t Receive(int16_t a_sock, std::string &a_buff) = 0;
};

#endif // ISOCKET_H
