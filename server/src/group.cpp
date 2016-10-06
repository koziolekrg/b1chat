#include "group.h"

Group::Group(std::string a_title, int16_t a_client)
    :m_title(a_title)
{
    m_clients.push_back(a_client); ///< push first client(who create) to group
}

Group::~Group(){

}

std::string Group::getTitle(){
    return m_title;
}

bool Group::addClient(int16_t a_client){
    bool retVal = true;
    for(auto client : m_clients){  ///< check if client is already in group
        if(client == a_client){
            retVal = false;
        }
    }
    if(retVal){
        m_clients.push_back(a_client); ///< if dont , push

    }
    return retVal;
}

std::vector <int16_t> Group::getClientsList(){
    return m_clients;
}
