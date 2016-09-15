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
    Client(std::string a_hostAddress, int a_port);
    ~Client();
    int buffer_message(char * message);
    int find_network_newline(char * message, int inbuf);

private:
    int sock;
    struct sockaddr_in server;
    char message[256] , server_reply[256];
    int inbuf;
    int room;
    char *after;
};

#endif // CLIENT_H
