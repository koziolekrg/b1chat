#ifndef IPRIV_H
#define IPRIV_H

#include <string>
#include <vector>

class IPriv
{
public:
    virtual bool IAddNewGroup(std::string title, int16_t client){}
    virtual bool IAddNewClientToGroup(std::string title, int16_t client){}
    virtual std::vector <int16_t> IGetClients(std::string a_title){}

};

#endif // IPRIV_H
