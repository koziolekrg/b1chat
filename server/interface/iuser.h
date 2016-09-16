#ifndef IUSER_H
#define IUSER_H

#include <string>
#include <vector>

class IUser
{
public:
    virtual bool ICheckLog(std::string a_login, std::string a_password){}
    virtual std::string IGetLogin(){}
    virtual std::string ISaveToFile(){}
};

#endif // IUSER_H
