#ifndef CLIENT_H
#define CLIENT_H

#include <stdlib.h>
#include <netinet/in.h>
#include <string.h>
#include <iostream>
#include <sys/socket.h>
#include <error.h>
#include <stdio.h>
#include <unistd.h>
#include <sys/time.h>
#include <vector>
#include <netdb.h>
#include <thread>
#include <arpa/inet.h> //inet_addr

#define COMPLETE 0
#define BUF_SIZE 256

class Client
{
public:
    Client();
    ~Client();
    void test(){std::cout<<"Client"<<std::endl;}

};



#endif // CLIENT_H
