#ifndef ILOGIN_H
#define ILOGIN_H

#include <string>
#include <vector>

class ILogin
{
public:
    virtual ~ILogin(){};
    virtual int16_t getFd() = 0 ;
    virtual std::string getLogin() = 0 ;
};

#endif // ILOGIN_H
