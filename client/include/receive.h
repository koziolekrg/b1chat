#ifndef RECEIVE_H
#define RECEIVE_H

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

class Receive
{
public:
    Receive();
    ~Receive();

};

#endif // RECEIVE_H
