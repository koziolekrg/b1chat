#include "priv.h"

Priv::Priv(){

}

Priv::~Priv(){

}

bool Priv::addNewGroup(std::string a_title, int16_t a_client){
    bool retVal = true;
    for(auto group : m_groupClients){
        if(group != NULL && a_title.compare(group->getTitle()) == 0) ///< check if group already exist
            retVal = false;
    }
    m_groupClients.push_back(new Group(a_title, a_client));///, if not, create
    return retVal;
}

bool Priv::addNewClientToGroup(std::string a_title, int16_t a_client){
    bool retVal = false;
    for(auto group : m_groupClients){
        if(group != NULL && a_title.compare(group->getTitle()) == 0){ /// check if group exist
            retVal = group->addClient(a_client);
        }
    }
    return retVal;
}

std::vector <int16_t> Priv::getClients(std::string a_title){
    std::vector <int16_t> retVal;
    for(auto group : m_groupClients){
        if(group != NULL && a_title.compare(group->getTitle()) == 0){ /// if title is correct, return vector of clients
            retVal = group->getClientsList();
        }
    }
    return retVal;
}


