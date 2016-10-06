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

    if(argc<2){
        cout<<"Type [port number] as parameter";
        exit(1);
    }

    bool retVal;
    Socket socket;
    Server server(socket);
    retVal = server.initConnection(atoi(argv[1]));

    if(retVal)
        server.startListening(atoi(argv[1]));

    return 0;
}

