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

class User : public IUser
{
public:
    /**
     * @brief User
     * @param a_login string with login
     * @param a_password string with password
     */
    User(std::string a_login, std::string a_password);
    virtual ~User();
    /**
     * @brief ICheckLog Check if login and password are correct
     * @param a_login string with login
     * @param a_password string with password
     * @return true or false
     */
    bool ICheckLog(std::string a_login, std::string a_password);
    /**
     * @brief IGetLogin return login
     * @return login as string
     */
    std::string IGetLogin();
    /**
     * @brief ISaveToFile returning string with login and password for saving file
     * @return lagin and password as string
     */
    std::string ISaveToFile();
private:
    std::string m_login; ///< login
    std::string m_password; ///< password
};

// end of class User
#endif // USER_H
