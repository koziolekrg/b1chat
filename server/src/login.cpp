#include "login.h"

Login::Login(int16_t a_fd, std::string a_login)
    :fd(a_fd), login(a_login)
{

}

Login::~Login(){

}

std::string Login::IGetLogin(){
    return login;
}

int16_t Login::IGetFd(){
    return fd;
}

