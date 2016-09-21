#ifndef IGROUP_H
#define IGROUP_H

#include <string>
#include <vector>

class IClient
{
public:
    virtual void IConnect(std::string a_addres, int a_port){}
    virtual void ISend_data(){}
    virtual void IReceive_data(){}
};

#endif // IGROUP_H
