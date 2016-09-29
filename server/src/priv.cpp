#include "priv.h"

Priv::Priv(){

}

Priv::~Priv(){

}

bool Priv::IAddNewGroup(std::string a_title, int16_t a_client){
    bool retVal = true;
    for(auto group : m_groupClients){
        if(a_title.compare(group->IGetTitle()) == 0) ///< check if group already exist
            retVal = false;
    }
    m_groupClients.push_back(new Group(a_title, a_client));///, if not, create
    return retVal;
}

bool Priv::IAddNewClientToGroup(std::string a_title, int16_t a_client){
    bool retVal = false;
    for(auto group : m_groupClients){
        if(a_title.compare(group->IGetTitle()) == 0){ /// check if user is already in group
            retVal = group->IAddClient(a_client);
        }
    }
    return retVal;
}

std::vector <int16_t> Priv::IGetClients(std::string a_title){
    std::vector <int16_t> retVal;
    for(auto group : m_groupClients){
        if(a_title.compare(group->IGetTitle()) == 0){ /// if title is correct, return vector of clients
            retVal = group->IGetClientsList();
        }
    }
    return retVal;
}


