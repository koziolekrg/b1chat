#ifndef ILOGIN_H
#define ILOGIN_H

#include <string>
#include <vector>

class ILogin
{
public:
    virtual int16_t IGetFd(){}
    virtual std::string IGetLogin(){}
};

#endif // ILOGIN_H
