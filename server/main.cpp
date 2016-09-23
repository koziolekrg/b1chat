/**
 @mainpage

Chat application brighONE


@author Pawel
@date 24/09/2016
@version 1.0
 */


#include <iostream>
#include "server.h"

using namespace std;

int main(int argc, char *argv[])
{
    Server * server = new Server(atoi(argv[1])); /// Create and call Server consturctor 

    return 0;
}

