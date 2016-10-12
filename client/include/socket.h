/**
 * \class Client
 *
 * This class is responsible for keeping and handling all connection events.
 * In first thread is loop with receiving messages and printing on screen.
 * Second thread is getting input from user and sending it to the server.
 *
 *
 */

#ifndef SOCKET_H
#define SOCKET_H

#include <stdlib.h>
#include <netinet/in.h>
#include <string.h>
#include <iostream>
#include <sys/socket.h>
#include <stdio.h>
#include <unistd.h>
#include "isocket.h"

using namespace std;

class Socket : public ISocket
{
public:
    Socket();
    virtual ~Socket();
    /**
     * @brief Connect init all variables
     * @param a_port 
     * @return
     */
    int16_t Connect(int16_t a_sock, sockaddr_in &a_server);
    /**
     * @brief SetSocket responsible for setting port number
     * @param a_port int port number
     * @return true or false
     */
    int16_t SetSocket();
    /**
    * @brief Send allows to sending messages
    * @param a_message message to send as string
    * @param a_client socket descriptor as int
    * @return true or false
    */
    int16_t Send(int16_t m_sock, string a_message);
    /**
    * @brief Receive allows to receive messages
    * @param a_setClient set of clients
    * @param a_buffer variable with message
    * @return true or false
    */
    int16_t Receive(int16_t a_sock, std::string &a_buff);
};



#endif // SOCKET_H
