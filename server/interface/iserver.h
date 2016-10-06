#ifndef ISERVER_H
#define ISERVER_H

#include <string>

class IServer
{
public:
    virtual ~IServer(){};
    virtual void startListening(int16_t port) = 0 ;
    virtual void incommingConnection() = 0 ;
    virtual bool sendMessage(std::string message, int16_t client) = 0 ;
    virtual void readFile() = 0 ;
    virtual std::string descriptorToLogin(int a_client) = 0 ;
    virtual int loginToDescriptor(std::string a_client) = 0 ;
};

#endif // SERVER_H
