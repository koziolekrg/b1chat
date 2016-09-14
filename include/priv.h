#ifndef PRIV_H
#define PRIV_H

#include "ipriv.h"
#include "group.h"
#include <string.h>
#include <iostream>
#include <sys/socket.h>
#include <error.h>
#include <stdio.h>
#include <unistd.h>
#include <sys/time.h>
#include <vector>

class Priv: public IPriv
{
public:
    Priv();
    ~Priv();
    bool IAddNewGroup(std::string a_title, int16_t a_client) override;
    bool IAddNewClientToGroup(std::string a_title, int16_t a_client) override;
    std::vector <int16_t> IGetClients(std::string a_title) override;

private:
    std::vector <Group*> m_groupClients;

};

#endif // PRIV_H
