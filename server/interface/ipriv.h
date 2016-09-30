#ifndef IPRIV_H
#define IPRIV_H

#include <string>
#include <vector>

class IPriv
{
public:
    virtual ~IPriv(){};
    virtual bool IAddNewGroup(std::string title, int16_t client) = 0 ;
    virtual bool IAddNewClientToGroup(std::string title, int16_t client) = 0 ;
    virtual std::vector <int16_t> IGetClients(std::string a_title) = 0 ;

};

#endif // IPRIV_H
