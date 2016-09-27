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
    Client client;//*client = new Client();

    client.IConnect("127.0.0.1" , 8888);

    std::thread s(&Client::ILogin, client);
    std::thread r(&Client::IReceive, client);

    s.join();
    r.join();


    return 0;
}
