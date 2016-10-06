#include<iostream>    //cout
#include<stdio.h> //printf
#include<string.h>    //strlen
#include<string>  //string
#include<sys/socket.h>    //socket
#include<arpa/inet.h> //inet_addr
#include<netdb.h> //hostent
#include <thread>
#include <unistd.h>
#include "client.h"
using namespace std;

int main(int argc , char *argv[])
{
    if(argc<3){
        std::cout<<"Type [IP address] and [port number]  as parameters";
        exit(1);
    }
    Socket socket;


    Client *client = new Client(socket);

    bool retVal = client->connectToServer(argv[1], atoi(argv[2]));

    if(retVal){
        std::thread s(&Client::loginToServer, client);
        std::thread r(&Client::receiveFromServer, client);

        r.join();
        s.join();
    }

    return 0;
}
