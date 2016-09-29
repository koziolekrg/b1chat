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

int main(int argc , char *argv[])
{
    if(argc<3){
        std::cout<<"Type [IP address] and [port number]  as parameters";
        exit(1);
    }

    //Client client;
    //client.IConnect(argv[1], atoi(argv[2]));

    Client *client = new Client();
    client->IConnect(argv[1], atoi(argv[2]));

    std::thread s(&Client::ILogin, client);
    std::thread r(&Client::IReceive, client);

    s.join();
    r.join();




    return 0;
}
