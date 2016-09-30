#ifndef IGROUP_H
#define IGROUP_H

#include <string>
#include <vector>

class IGroup
{
public:
    virtual ~IGroup(){};
    virtual std::string IGetTitle() = 0 ;
    virtual bool IAddClient(int16_t a_client) = 0 ;
    virtual std::vector <int16_t> IGetClientsList() = 0 ;
};

#endif // IGROUP_H
