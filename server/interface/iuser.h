#ifndef IUSER_H
#define IUSER_H

#include <string>
#include <vector>

class IUser
{
public:
    virtual ~IUser() {};
    virtual bool checkLog(std::string a_login, std::string a_password) = 0 ;
    virtual std::string getLogin() = 0 ;
    virtual std::string saveToFile() = 0 ;
};

#endif // IUSER_H
