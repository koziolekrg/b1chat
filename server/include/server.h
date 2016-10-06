/**
 * \class Server
 *
 * This class is responsible for handling all connection events. 
 *
 *
 */

#ifndef SERVER_H
#define SERVER_H

#define MAX_CLIENTS 10

#include <string.h>
#include <iostream>
#include <fstream>
#include <vector>
#include <list>
#include <netinet/in.h>
#include <sys/socket.h>
#include <error.h>
#include <stdio.h>
#include <unistd.h>
#include <sys/time.h>
#include <boost/algorithm/string.hpp>

#include "iserver.h"
#include "priv.h"
#include "user.h"
#include "login.h"
#include "socket.h"

class Server : public IServer
{
public:
    /**
     * @brief Server create an Server with selected port number
     * @param a_port define port number
     */
    Server(ISocket &aSocket);
    virtual ~Server();
    /**
     * @brief IInitConnection
     * @param a_port
     * @return
     */
    bool initConnection(int16_t a_port);
    /**
     * @brief IStartListening starting listetning on port for clients messages
     * @param a_port int port number
     * @return true or false
     */
    void startListening(int16_t a_port) override;
    /**
    * @brief ISendMessage allows to sending messages
    * @param a_message message to send as string
    * @param a_client socket descriptor as int
    * @return true or false
    */
    bool sendMessage(std::string a_message, int16_t a_client) override;
    /**
     * @brief IIncommingConnection get incomming connection
     */
    void incommingConnection() override;
    /**
     * @brief IHandleMessage handle received message
     * @param a_buffer income message
     * @param a_client socket of client who sent message
     */
    void handleMessage(std::string a_buffer, int16_t &a_client);
    /**
     * @brief ISetSocket responsible for setting port number
     * @param a_port int port number
     * @return true or false
     */
    bool setSocket(int16_t a_port);
    /**
     * @brief IBindPort binding addres and port if it's available
     * @return true or false
     */
    bool bindPort();
    /**
     * @brief IReadFile read data of existing clients from file
     * @return true of false
     */
    void readFile();
    /**
     * @brief ISaveFile save all data to file
     * @return true of false
     */
    bool saveFile();
    /**    //EXPECT_CALL(mocksocket, SetSocket(_,_,_,_)).WillOnce(Return(true));

     * @brief IDescriptorToLogin convert client descriptor to his login
     * @param a_client socket descriptor of client as int
     * @return client login as string
     */
    std::string descriptorToLogin(int a_client);
    /**
     * @brief ILoginToDescriptor covert client login to his descriptor
     * @param a_client client login as string
     * @return socket descriptor of client as int
     */
    int loginToDescriptor(std::string a_client);

    /**
     * @brief LoginToServer handling request for login
     * @param a_login login as string
     * @param a_password password as string
     * @param a_client socket from connection comming
     * @return message to client as string - accept/refuse
     */
    std::string loginToServer(std::string a_login, std::string a_password, int a_client);

    /**
     * @brief CreateAccount handling request for create account
     * @param a_login login as string
     * @param a_password password as string
     * @param a_client socket from connection comming
     * @return message to client as string - accept/refuse
     */
    std::string createAccount(std::string a_login, std::string a_password, int a_client);

    /**
     * @brief Logout handling logout signal (disconnec or request from client)
     * @param a_client socket descriptor number
     */
    void logout(int16_t &a_client);

    /**
     * @brief Exit exit signal handle
     * @param signum number of interuption
     */

    void Exit(int signum);

private:
    char m_buffer[100]; ///< buffer for messages
    sockaddr_in m_serverSocket, m_clientSocket;
    fd_set m_readfds,m_actfds; ///< set of connected descriptors
    int16_t m_sd; ///< server descriptor
    int16_t m_nfds; ///< number of file descriptors
    int16_t m_client; ///< client descriptor
    socklen_t m_len; 
    timeval m_tv;
    std::vector <int16_t> m_setClients; ///< vector of clients descriptors
    std::vector <IUser*> m_setUsers; ///< vector of logins and password //////<
    std::fstream m_dataFile;
    Priv m_private; ///< object responsible for keeping groups vector
    std::vector <ILogin*> m_setLogins; ///< list of online clients
    bool m_isAvailable; ///< flag
    ISocket &m_socket;

};
// end of class Server
#endif // SERVER_H
