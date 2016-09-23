/**
 * \class Login
 *
 * This class keeps in one object login and socket descriptor
 *
 *
 */

#ifndef LOGIN_H
#define LOGIN_H

#include <ilogin.h>
#include <string.h>
#include <iostream>
#include <sys/socket.h>
#include <error.h>
#include <stdio.h>
#include <unistd.h>
#include <sys/time.h>
#include <vector>

class Login : ILogin
{
public:
    /// Create Login with descriptor and login
    Login(int16_t a_fd, std::string a_login):fd(a_fd), login(a_login){}
    ~Login();
    /// Methor return login
    std::string IGetLogin(){return login;}
    /// Method return descriptor
    int16_t IGetFd(){return fd;}

private:
    int16_t fd; ///< socket descriptor
    std::string login; ///< login 
};

#endif // LOGIN_H
