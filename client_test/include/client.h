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
#include <mutex>
#include "iclient.h"

#define COMPLETE 0
#define BUF_SIZE 256

class Client : public IClient
{
public:
    Client();
    ~Client();
    void IConnect(std::string, int);
    void ISend_data();
    void IReceive_data();
    void IMainMenu(int a_state);

private:
    int sock;
    std::string address;
    int port;
    struct sockaddr_in server;
    bool isLoggedIn;
};



#endif // CLIENT_H
