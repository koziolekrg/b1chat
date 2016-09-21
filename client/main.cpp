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
    Client *client = new Client();

    client->IConnect("localhost" , 8888);

    std::thread s(&Client::ISend_data, client);
    std::thread r(&Client::IReceive_data, client);

    s.join();
    r.join();


    return 0;
}
