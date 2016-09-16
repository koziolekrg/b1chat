#ifndef USER_H
#define USER_H

#include "iuser.h"
#include <string.h>
#include <iostream>
#include <sys/socket.h>
#include <error.h>
#include <stdio.h>
#include <unistd.h>
#include <sys/time.h>
#include <vector>
class User : public IUser
{
public:
    User(std::string a_login, std::string a_password);
    ~User();
    bool ICheckLog(std::string a_login, std::string a_password);
    std::string IGetLogin();
    std::string ISaveToFile();
private:
    std::string m_login;
    std::string m_password;
};

#endif // USER_H
