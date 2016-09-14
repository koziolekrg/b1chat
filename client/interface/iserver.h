#ifndef ISERVER_H
#define ISERVER_H

#include <string>

class IServer
{
public:
    virtual bool IStartListening(int16_t port){}
    virtual void IIncommingConnection(){}
    virtual bool ISendMessage(std::string message, int16_t client){}
};

#endif // SERVER_H
