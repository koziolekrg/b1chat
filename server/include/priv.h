#ifndef PRIV_H
#define PRIV_H

/**
 * \class Priv
 *
 * This class keeps the vector with all groups 
 *
 *
 */

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
    /**
     * @brief Priv
     */
    Priv();
    ~Priv();
    /**
     * @brief IAddNewGroup create new group with title and fecriptor and add it to the vector
     * @param a_title string with group title
     * @param a_client client socket descriptor who create group
     * @return true or false
     */
    bool IAddNewGroup(std::string a_title, int16_t a_client) override;
    /**
     * @brief IAddNewClientToGroup allows to add new client to group
     * @param a_title string with group title
     * @param a_client client socket descriptor who wants to add
     * @return true or false
     */
    bool IAddNewClientToGroup(std::string a_title, int16_t a_client) override;
    /// Method return
    /**
     * @brief IGetClients return all clients in this group
     * @param a_title title group as string
     * @return vector with descriptors of clients in group
     */
    std::vector <int16_t> IGetClients(std::string a_title) override;

private:
    std::vector <Group*> m_groupClients; ///< vector with Group objects

};
// end of class Priv
#endif // PRIV_H
