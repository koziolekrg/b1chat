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
    Server();
    ~Server();
    /**
     * @brief IInitConnection
     * @param a_port
     * @return
     */
    bool IInitConnection(int16_t a_port);
    /**
     * @brief IStartListening starting listetning on port for clients messages
     * @param a_port int port number
     * @return true or false
     */
    void IStartListening(int16_t a_port) override;
    /**
    * @brief ISendMessage allows to sending messages
    * @param a_message message to send as string
    * @param a_client socket descriptor as int
    * @return true or false
    */
    bool ISendMessage(std::string a_message, int16_t a_client) override;
    /**
     * @brief IIncommingConnection get incomming connection
     */
    void IIncommingConnection() override;
    /**
     * @brief IHandleMessage handle received message
     * @param a_buffer income message
     * @param a_client socket of client who sent message
     */
    void IHandleMessage(std::string a_buffer, int16_t &a_client);
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
    void IReadFile();
    /**
     * @brief ISaveFile save all data to file
     * @return true of false
     */
    bool ISaveFile();
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

    std::string LoginToServer(std::string a_login, std::string a_password, int ac_client);

    std::string CreateAccount(std::string a_login, std::string a_password, int ac_client);

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

};
// end of class Server
#endif // SERVER_H
