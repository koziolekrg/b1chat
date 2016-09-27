#ifndef ILOGIN_H
#define ILOGIN_H

#include <string>
#include <vector>

class ILogin
{
public:
    virtual int16_t IGetFd() = 0 ;
    virtual std::string IGetLogin() = 0 ;
};

#endif // ILOGIN_H
