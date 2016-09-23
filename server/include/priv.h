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
    /// Create Priv 
    Priv();
    ~Priv();
    /// Method create new group with title and fecriptor and add it to the vector
    bool IAddNewGroup(std::string a_title, int16_t a_client) override;
    /// Method allows to add new client to group
    bool IAddNewClientToGroup(std::string a_title, int16_t a_client) override;
    /// Method return vector with descriptors of clients in group
    std::vector <int16_t> IGetClients(std::string a_title) override;

private:
    std::vector <Group*> m_groupClients; ///< vector with Group objects

};
// end of class Priv
#endif // PRIV_H
