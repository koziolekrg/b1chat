#ifndef USER_H
#define USER_H

/**
 * \class User
 *
 * This class keeps client login and password and handling request
 * for login (checking is login and password correct).
 *
 *
 */

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
    /// Create new User with login and password
    User(std::string a_login, std::string a_password);
    ~User();
    /// Method checking is login and password correct
    bool ICheckLog(std::string a_login, std::string a_password);
    /// Method return login
    std::string IGetLogin();
    /// Method returnin login and password for saving it to file
    std::string ISaveToFile();
private:
    std::string m_login; ///< login
    std::string m_password; ///< password
};

// end of class User
#endif // USER_H
