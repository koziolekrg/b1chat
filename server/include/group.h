/**
 * \class Group
 *
 * This class keeps name of group as string and vector of socket descriptors
 * as ints. Constructor gets title of group and descriptor of user who   
 * is requesting for create. Class allows to return title, add another
 * client to vector and return vector with all descriptors.
 *
 *
 */

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
    /// Create an Group with title and client descriptor
    Group(std::string a_title, int16_t a_client);
    ~Group();
    /// Method return name of group
    std::string IGetTitle() override;
    /// Method allows to add new client to vector
    bool IAddClient(int16_t a_client) override;
    /// Method return vector with descriptors
    std::vector <int16_t> IGetClientsList() override;

private:
    std::string m_title; ///< group title
    std::vector <int16_t> m_clients; ///< vector with descriptors
};

// end of class Group

#endif // GROUP_H
