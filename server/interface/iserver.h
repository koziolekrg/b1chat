#ifndef ISERVER_H
#define ISERVER_H

#include <string>

class IServer
{
public:
    virtual bool IStartListening(int16_t port){}
    virtual void IIncommingConnection(){}
    virtual bool ISendMessage(std::string message, int16_t client){}
    virtual bool ISetSocket(int16_t a_port){}
    virtual bool IBindPort(){}
    virtual bool IReadFile(){}
    virtual std::string IDescriptorToLogin(int a_client){}
    virtual int ILoginToDescriptor(std::string a_client){}
};

#endif // SERVER_H
