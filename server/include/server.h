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

#include "iserver.h"
#include "priv.h"
#include "user.h"
#include "login.h"
#include <string.h>
#include <iostream>
#include <fstream>
#include <algorithm>
#include <vector>
#include <list>
#include <netinet/in.h>
#include <sys/socket.h>
#include <error.h>
#include <stdio.h>
#include <unistd.h>
#include <sys/time.h>
#include <boost/algorithm/string.hpp>

class Server : public IServer
{
public:
    /**
     * @brief Server create an Server with selected port number
     * @param a_port define port number
     */
    Server(int16_t a_port);
    ~Server();
    /**
     * @brief IStartListening starting listetning on port for clients messages
     * @param a_port int port number
     * @return true or false
     */
    bool IStartListening(int16_t a_port) override;
    /**
    * @brief ISendMessage allows to sending messages
    * @param a_message message to send as string
    * @param a_client socket descriptor as int
    * @return true or false
    */
    bool ISendMessage(std::string a_message, int16_t a_client) override;
    /**
     * @brief IIncommingConnection loop handling incomming events from socket
     */
    void IIncommingConnection() override;
    /**
     * @brief ISetSocket responsible for setting port number
     * @param a_port int port number
     * @return true or false
     */
    bool ISetSocket(int16_t a_port);
    /**
     * @brief IBindPort binding addres and port if it's available
     * @return true or false
     */
    bool IBindPort();
    /**
     * @brief IReadFile read data of existing clients from file
     * @return true of false
     */
    bool IReadFile(); 
    /**
     * @brief IDescriptorToLogin convert client descriptor to his login
     * @param a_client socket descriptor of client as int
     * @return client login as string
     */
    std::string IDescriptorToLogin(int a_client);
    /**
     * @brief ILoginToDescriptor covert client login to his descriptor
     * @param a_client client login as string
     * @return socket descriptor of client as int
     */
    int ILoginToDescriptor(std::string a_client);

private:
    int16_t m_port; ///< port number
    char m_buffer[100]; ///< buffer for messages
    struct sockaddr_in m_serverSocket, m_clientSocket;
    fd_set m_readfds,m_actfds; ///< set of connected descriptors
    int16_t m_sd; ///< server descriptor
    int16_t m_nfds; ///< number of file descriptors
    int16_t m_client; ///< client descriptor
    socklen_t m_len; 
    struct timeval m_tv;
    std::vector <int16_t> m_setClients; ///< vector of clients descriptors
    std::vector <User*> m_setUsers; ///< vector of logins and password
    std::fstream m_dataFile;
    Priv m_private; ///< object responsible for keeping groups vector
    std::list <Login*> m_setLogins; ///< list of online clients
    bool m_isAvailable; ///< flag 

};
// end of class Server
#endif // SERVER_H
