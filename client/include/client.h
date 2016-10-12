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
#include <ctype.h>
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
#include <mutex>
#include "iclient.h"
#include "socket.h"


#define COMPLETE 0
#define BUF_SIZE 256


class Client : public IClient
{
public:
    /**
     * @brief Client create Client object
     */
    Client(ISocket &aSocket);
    virtual ~Client();
    /**
     * @brief Connect method connecting to server via TCP/IP
     * @param a_hostAddr server IP address convert from string to address
     * @param a_port server port number as int
     */
    bool connectToServer(std::string a_hostAddr, int a_port) override;
    /**
     * @brief Login method responsible for authenticate user. This method is called
     * as separate thread. While server wont answer with true loop is closed for login.
     * When server return true method will be calling IMainMenu.
     */
    void loginToServer() override;
    /**
     * @brief Receive method called in separate thread, called recv in endless
     * loop and handling printing communicates
     */
    void receiveFromServer() override;
    /**
     * @brief MainMenu switch for handling inputs from user and calling ISend
     * @param a_state string with menu status get from user input
     */
    void mainMenu(int a_state) override;
    /**
     * @brief Send method allows to send message to server
     * @param a_msg message to send as string
     * @return true or false
     */
    bool sendMessage(std::string a_msg) override;
    /**
     * @brief receiveMessage method allows to receive message
     * @param a_msg message to send as string
     * @return true or false
     */
    bool receiveMessage(std::string &a_msg) override;


private:
    std::mutex mutexLog;
    int m_sock; ///< socket descriptor
    sockaddr_in m_server; ///<
    bool m_isLoggedIn; ///< variable checking is user already log in
    ISocket &m_socket;
};



#endif // CLIENT_H
