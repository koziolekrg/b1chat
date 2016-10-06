/**
 * \class Login
 *
 * This class keeps in one object login and socket descriptor
 *
 *
 */

#ifndef LOGIN_H
#define LOGIN_H

#include "ilogin.h"
#include <string.h>
#include <iostream>
#include <sys/socket.h>
#include <error.h>
#include <stdio.h>
#include <unistd.h>
#include <sys/time.h>

class Login : public ILogin
{
public:
    /**
     * @brief Login create Login with descriptor and login
     * @param a_fd socket descriptor as int
     * @param a_login login of client as string
     */
    Login(int16_t a_fd, std::string a_login);
    virtual ~Login();
    /**
     * @brief IGetLogin return login of client
     * @return login as string
     */
    std::string getLogin() override;
    /**
     * @brief IGetFd return socket descriptor of client
     * @return descriptor as int
     */
    int16_t getFd()override;

private:
    int16_t fd; ///< socket descriptor
    std::string login; ///< login 
};

#endif // LOGIN_H
