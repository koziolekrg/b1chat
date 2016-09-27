#include "user.h"

User::User(std::string a_login, std::string a_password)
    :m_login(a_login), m_password(a_password){

}

User::~User(){

}

bool User::ICheckLog(std::string a_login, std::string a_password){
    if(m_password.compare(a_password) == 0 && m_login.compare(a_login) == 0){
        return true;
    }
    else{
        return false;
    }
}

std::string User::IGetLogin(){
    return m_login;
}

std::string User::ISaveToFile(){
    return m_login+"-"+m_password+"-";
}
