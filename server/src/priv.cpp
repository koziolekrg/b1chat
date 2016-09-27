#include "priv.h"

Priv::Priv(){

}

Priv::~Priv(){

}

bool Priv::IAddNewGroup(std::string a_title, int16_t a_client){
    for(auto group : m_groupClients){
        if(a_title.compare(group->IGetTitle()) == 0)
            return false;
    }
    m_groupClients.push_back(new Group(a_title, a_client));
    return true;
}

bool Priv::IAddNewClientToGroup(std::string a_title, int16_t a_client){
    for(auto group : m_groupClients){
        if(a_title.compare(group->IGetTitle()) == 0){
            return group->IAddClient(a_client);
        }
    }
    return false;
}

std::vector <int16_t> Priv::IGetClients(std::string a_title){
    for(auto group : m_groupClients){
        if(a_title.compare(group->IGetTitle()) == 0){
            return group->IGetClientsList();
        }
    }
    std::cout<<"Group incorrect"<<std::endl;

    std::vector <int16_t> temp;
    return temp;
}


