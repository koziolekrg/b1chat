/**
 * \class Client
 *
 * This class is responsible for keeping and handling all connection events.
 * In first thread is loop with receiving messages and printing on screen.
 * Second thread is getting input from user and sending it to the server.
 *
 *
 */

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
#include <boost/algorithm/string.hpp>
#include "iclient.h"
#include <mutex>

#define COMPLETE 0
#define BUF_SIZE 256


class Client : public IClient
{
public:
    /**
     * @brief Client create Client object
     */
    Client();
    ~Client();
    /**
     * @brief IConnect method connecting to server via TCP/IP
     * @param a_hostAddr server IP address convert from string to address
     * @param a_port server port number as int
     */
    void IConnect(std::string a_hostAddr, int a_port) override;
    /**
     * @brief ILogin method responsible for authenticate user. This method is called
     * as separate thread. While server wont answer with true loop is closed for login.
     * When server return true method will be calling IMainMenu.
     */
    void ILogin() override;
    /**
     * @brief IReceive method called in separate thread, called recv in endless
     * loop and handling printing communicates
     */
    void IReceive() override;
    /**
     * @brief IMainMenu switch for handling inputs from user and calling ISend
     * @param a_state string with menu status get from user input
     */
    void IMainMenu(int a_state) override;
    /**
     * @brief ISend method allows to send message to server
     * @param a_msg message to send as string
     * @return true or false
     */
    bool ISend(std::string a_msg) override;



private:
    std::mutex mutexLog;
    int m_sock; ///< socket descriptor
    sockaddr_in m_server; ///<
    bool m_isLoggedIn; ///< variable checking is user already log in
};



#endif // CLIENT_H
