#include "priv.h"

Priv::Priv(){

}

Priv::~Priv(){

}

bool Priv::IAddNewGroup(std::string a_title, int16_t a_client){
    bool retVal = true;
    for(auto group : m_groupClients){
        if(a_title.compare(group->IGetTitle()) == 0)
            retVal = false;
    }
    m_groupClients.push_back(new Group(a_title, a_client));
    return retVal;
}

bool Priv::IAddNewClientToGroup(std::string a_title, int16_t a_client){
    bool retVal = false;
    for(auto group : m_groupClients){
        if(a_title.compare(group->IGetTitle()) == 0){
            retVal = group->IAddClient(a_client);
        }
    }
    return retVal;
}

std::vector <int16_t> Priv::IGetClients(std::string a_title){
    std::vector <int16_t> retVal;
    for(auto group : m_groupClients){
        if(a_title.compare(group->IGetTitle()) == 0){
            retVal = group->IGetClientsList();
        }
    }
    return retVal;
}


