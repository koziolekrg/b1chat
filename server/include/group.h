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
    /**
     * @brief Group create an Group with title and client descriptor
     * @param a_title group title as string
     * @param a_client descriptor as int
     */
    Group(std::string a_title, int16_t a_client);
    ~Group();
    /**
     * @brief IGetTitle return name of group
     * @return group name as string
     */
    std::string IGetTitle() override;
    /**
     * @brief IAddClient allows to add new client to vector
     * @param a_client client socket as int
     * @return true or false
     */
    bool IAddClient(int16_t a_client) override;
    /**
     * @brief IGetClientsList return vector with descriptors
     * @return vector of ints
     */
    std::vector <int16_t> IGetClientsList() override;

private:
    std::string m_title; ///< group title
    std::vector <int16_t> m_clients; ///< vector with descriptors
};

// end of class Group

#endif // GROUP_H
