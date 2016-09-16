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
    Login(int16_t a_fd, std::string a_login):fd(a_fd), login(a_login){}
    ~Login();
    std::string IGetLogin(){return login;}
    int16_t IGetFd(){return fd;}

private:
    int16_t fd;
    std::string login;
};

#endif // LOGIN_H
