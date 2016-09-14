#ifndef IGROUP_H
#define IGROUP_H

#include <string>
#include <vector>

class IGroup
{
public:
    virtual std::string IGetTitle(){}
    virtual bool IAddClient(int16_t a_client){}
    virtual std::vector <int16_t> IGetClientsList(){}
};

#endif // IGROUP_H
