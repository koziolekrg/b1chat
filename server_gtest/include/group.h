#ifndef GROUP_H
#define GROUP_H

#include "igroup.h"
#include <string.h>
#include <iostream>
#include <sys/socket.h>
#include <error.h>
#include <stdio.h>
#include <unistd.h>
#include <sys/time.h>
#include <vector>

class Group : public IGroup
{
public:
    Group(std::string a_title, int16_t a_client);
    ~Group();
    std::string IGetTitle() override;
    bool IAddClient(int16_t a_client) override;
    std::vector <int16_t> IGetClientsList() override;

private:
    std::string m_title;
    std::vector <int16_t> m_clients;

};

#endif // GROUP_H
