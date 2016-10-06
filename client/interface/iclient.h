#ifndef IGROUP_H
#define IGROUP_H

#include <string>
#include <vector>

class IClient
{
public:
    virtual ~IClient(){}
    virtual bool connectToServer(std::string a_addres, int a_port) = 0 ;
    virtual void loginToServer() = 0 ;
    virtual void receiveFromServer() = 0 ;
    virtual void mainMenu(int a_state) = 0 ;
    virtual bool sendMessage(std::string a_msg) = 0 ;
    virtual bool receiveMessage(std::string &a_msg) = 0 ;

};

#endif // IGROUP_H
