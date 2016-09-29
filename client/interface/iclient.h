#ifndef IGROUP_H
#define IGROUP_H

#include <string>
#include <vector>

class IClient
{
public:
    virtual void IConnect(std::string a_addres, int a_port) = 0 ;
    virtual void ILogin() = 0 ;
    virtual void IReceive() = 0 ;
    virtual void IMainMenu(int a_state) = 0 ;
    virtual bool ISend(std::string a_msg) = 0 ;
};

#endif // IGROUP_H
