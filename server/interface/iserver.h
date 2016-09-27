#ifndef ISERVER_H
#define ISERVER_H

#include <string>

class IServer
{
public:
    virtual bool IStartListening(int16_t port) = 0 ;
    virtual void IIncommingConnection() = 0 ;
    virtual bool ISendMessage(std::string message, int16_t client) = 0 ;
    virtual bool ISetSocket(int16_t a_port) = 0 ;
    virtual bool IBindPort() = 0 ;
    virtual bool IReadFile() = 0 ;
    virtual std::string IDescriptorToLogin(int a_client) = 0 ;
    virtual int ILoginToDescriptor(std::string a_client) = 0 ;
};

#endif // SERVER_H
