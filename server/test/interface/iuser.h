#ifndef IUSER_H
#define IUSER_H

#include <string>
#include <vector>

class IUser
{
public:
    virtual ~IUser();
    virtual bool ICheckLog(std::string a_login, std::string a_password) = 0 ;
    virtual std::string IGetLogin() = 0 ;
    virtual std::string ISaveToFile() = 0 ;
};

#endif // IUSER_H
