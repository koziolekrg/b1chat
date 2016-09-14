#include "user.h"

User::User(std::string a_login, std::string a_password)
    :m_login(a_login), m_password(a_password){

}

User::~User(){

}

bool User::checkLog(std::string a_login, std::string a_password){
    if(m_password.compare(a_password) == 0 && m_login.compare(a_login) == 0)
        return true;
    else{
        return false;
    }
}

std::string User::getLogin(){
    return m_login;
}

