
/**
 * \class Sockeet
 *
 * This class is responsible for handling all connection variables. 
 *
 *
 */

#ifndef SOCKET_H
#define SOCKET_H

#include <string.h>
#include <iostream>
#include <netinet/in.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <sys/ioctl.h>
#include <arpa/inet.h>
#include <net/if.h>
#include <unistd.h>
#include "isocket.h"

using namespace std;

class Socket : public ISocket
{
public:

    Socket();
    virtual ~Socket();
    /**
     * @brief Bind binding addres and port if it's available
     * @return true or false
     */
    bool Bind(int16_t &a_sd, sockaddr_in &a_serverSocket);
    /**
     * @brief Connect init all variables
     * @param a_port
     * @return
     */
    bool Connect(int16_t &a_sd);
    /**
     * @brief SetSocket responsible for setting port number
     * @param a_port int port number
     * @return true or false
     */
    void SetSocket(int16_t &a_sd, timeval &a_tv,sockaddr_in &a_serverSocket, int16_t a_port);
    /**
     * @brief Listen starting listetning on port for clients messages
     * @param a_port int port number
     * @return true or false
     */
    void Listen(int16_t a_sd);
    /**
    * @brief Send allows to sending messages
    * @param a_message message to send as string
    * @param a_client socket descriptor as int
    * @return true or false
    */
    bool Send(int16_t fd, string a_message);
    /**
    * @brief Receive allows to receive messages
    * @param a_setClient set of clients
    * @param a_buffer variable with message
    * @return true or false
    */
    bool Receive(int16_t a_setClient,char *a_buffer);
    /**
    * @brief getAddress
    * @param a_sd get socket of server
    * @return sstring with address
    */
    std::string getAddress(int16_t a_sd);
};

// end of class Socket
#endif // SOCKET_H
