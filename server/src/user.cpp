#include "user.h"

User::User(std::string a_login, std::string a_password)
    :m_login(a_login), m_password(a_password){

}

User::~User(){

}

bool User::checkLog(std::string a_login, std::string a_password){
    bool retVal = true;
    if(m_password.compare(a_password) == 0 && m_login.compare(a_login) == 0){ ///< compare login and password with input
        retVal = true;
    }
    else{
        retVal = false;
    }
    return retVal;
}

std::string User::getLogin(){
    return m_login;
}

std::string User::saveToFile(){
    return m_login+"-"+m_password+"-";
}
