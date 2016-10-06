#include "login.h"

Login::Login(int16_t a_fd, std::string a_login)
    :fd(a_fd), login(a_login)
{

}

Login::~Login(){

}

std::string Login::getLogin(){
    return login;
}

int16_t Login::getFd(){
    return fd;
}


