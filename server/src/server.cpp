#include "server.h"
#define MAX_CLIENTS 10

enum menuState { LOG_IN = 48 , CREATE_ACCOUNT, BROADCAST, CREATE_GROUP, ADD_USER_TO_GROUP,MESSAGE_TO_GROUP, USERS_LIST, LOGOUT, EXIT};
enum fileState { LOGIN = 1 , PASSWORD = 2 };

Server::Server(ISocket &aSocket)
    :m_socket(aSocket), m_sd(0), m_nfds(0), m_client(0), m_isAvailable(false)
{
    m_setLogins.push_back(new Login(99, " "));
    m_dataFile.open("users.data");
    m_tv.tv_sec = 5;
    m_tv.tv_usec = 0;
}

Server::~Server(){

}

void Server::Exit(int signum){
    std::cout<<"Exit";
    saveFile();

    for(auto object : m_setUsers)///< delete all dynamic alocated objects
        delete object;

    for(auto object : m_setLogins)
        delete object;

    exit(signum);
}

bool Server::initConnection(int16_t a_port){

    bool retVal = false;

    if(m_dataFile.is_open()){
        std::cout<<"Found file with data"<<std::endl;
        readFile();
    }
    else{
        std::cout<<"No file found, creating new one"<<std::endl;
    }

    m_dataFile.close();

    retVal = setSocket(a_port); /// Socket reserving

    if(retVal){
        retVal = bindPort(); // binding port
    }

    return retVal;
}

bool Server::setSocket(int16_t a_port){
    bool retVal = false;

    retVal = m_socket.Connect(m_sd);

    if(retVal){
        m_socket.SetSocket(m_sd,m_tv,m_serverSocket, a_port);
    }
    return retVal;
}

bool Server::bindPort(){
    bool retVal = m_socket.Bind(m_sd,m_serverSocket);
    if(!retVal){
    }
    return retVal;
}

std::string Server::descriptorToLogin(int a_client){
    std::string retVal = "unknown";
    for(auto login : m_setLogins){
        if(login != NULL && login->getFd() == a_client){ ///< if descriptor is the same
            retVal=login->getLogin();
        }
    }
    return retVal;
}

int Server::loginToDescriptor(std::string a_client){
    int retVal = 0;
    for(auto login : m_setLogins){
        if(login != NULL && a_client.compare(login->getLogin()) == 0){ ///< if login is the same
            retVal = login->getFd();
        }
    }
    return retVal;
}

void Server::readFile(){
    int16_t i = 0;
    std::string temp;
    std::string login, password;

    while(std::getline(m_dataFile,temp,'-')){
        i++;
        if(LOGIN == i){
            login = temp;
        }
        if(PASSWORD == i){
            password = temp;
            m_setUsers.push_back(new User(login, password)); ///< parsing, every 2 step push new user
            i=0;
        }
    }
}

bool Server::saveFile(){
    std::string save;
    bool retVal = false;
    m_dataFile.open("users.data", std::ios::out);
    if(m_dataFile.is_open()){
        for(auto user : m_setUsers){
            if(user != NULL){
                save = save + user->saveToFile();
            }
        }
        m_dataFile<<save;
        m_dataFile.close();
        retVal = true;
    }
    m_dataFile.close();
    return retVal;
}

void Server::startListening(int16_t a_port){

    m_socket.Listen(m_sd);

    FD_ZERO (&m_actfds); ///< fill set with zeros
    FD_SET (m_sd, &m_actfds); ///< set begin of set with selected socket

    m_nfds = m_sd;

    std::cout<<"[server] Wait at port["<<a_port<<"]"<<std::endl;


    std::cout<<"[server] Address ["<<m_socket.getAddress(m_sd)<<"]"<<std::endl;
    fflush (stdout);

    while (1)
    {
        bcopy ((char *) &m_actfds, (char *) &m_readfds, sizeof (m_readfds));

        if (select (m_nfds+1, &m_readfds, NULL, NULL, &m_tv) < 0)
        {
            perror ("[server] select() Error.\n");
            exit(1);
        }

        if (FD_ISSET (m_sd, &m_readfds)) ///< if socket from set id is readable
        {
            m_len = sizeof (m_clientSocket);
            bzero (&m_clientSocket, sizeof (m_clientSocket));

            m_client = accept (m_sd, (sockaddr *) &m_clientSocket, &m_len);

            if (m_client < 0)
            {
                perror ("[server] accept() Error.\n");
                continue;
            }

            if (m_nfds < m_client)
                m_nfds = m_client;

            FD_SET (m_client, &m_actfds);

            std::cout<<"[server] Client with descriptor "<< m_client <<" connected."<<std::endl;

            m_setClients.push_back(m_client); ///< if new client connected add descriptor to vector

            fflush (stdout);
        }

        incommingConnection();
    }
}

void Server::incommingConnection(){

    int16_t status=0;
    int16_t iterator =0;

    for(int16_t i=0; i< static_cast<int16_t>(m_setClients.size()); i++)
    {
        fflush (stdout);

        if (FD_ISSET (m_setClients[i], &m_readfds)) ///< check all socket if something to read
        {
            status = m_socket.Receive(m_setClients[i], m_buffer);

            if(status  == 0){ /// < if read return less than 0, that means client disconnect
                for(auto login : m_setLogins){
                    if(login != NULL && login->getFd() == m_setClients[i]){
                        m_setLogins.erase(m_setLogins.begin() + iterator); ///< delete clients from online clients list
                    }
                    iterator++;
                }
                m_setClients[i] = 0; ///< write to descriptor 0
            }
            handleMessage(m_buffer, m_setClients[i]); ///< if read return more than 0 lets try handle message
        }
    }
}

bool Server::sendMessage(std::string a_message, int16_t a_client){
    bool retVal = false;
    if(0 == a_client){
        for(auto fd: m_setClients){ ///< if variable 0, do send to all online clients
            m_socket.Send(fd, a_message);
        }
    } else {
        m_socket.Send(a_client, a_message);
    }
    return retVal;
}

void Server::handleMessage(std::string a_buffer, int16_t &a_client){

    std::string msg = a_buffer;
    std::vector <std::string> v_msg;
    int menu = a_buffer[0];
    int iterator = 0;

    switch(menu)
    {
    case LOG_IN: /// log in to exist account
        std::cout<<"Socket ["<<a_client<<"] trying to login"<<std::endl;
        boost::split(v_msg, msg, boost::is_any_of("~"));
        msg = loginToServer(v_msg[1],v_msg[2], a_client);
        sendMessage(msg,a_client);
        break;

    case CREATE_ACCOUNT: /// create new account request
        std::cout<<"Socket ["<<a_client<<"] trying to create account"<<std::endl;
        boost::split(v_msg, msg, boost::is_punct());
        msg = createAccount(v_msg[1],v_msg[2], a_client);
        sendMessage(msg,a_client);
        saveFile();
        break;

    case BROADCAST: /// broadcast message
        std::cout<<"Socket ["<<a_client<<"] send broadcast"<<std::endl;
        boost::split(v_msg, msg, boost::is_punct());
        msg = "2~"+descriptorToLogin(a_client)+"~"+v_msg[1]+" ~ ";
        sendMessage(msg, 0);
        break;

    case CREATE_GROUP: /// add new group
        boost::split(v_msg, msg, boost::is_punct());
        std::cout<<"Socket ["<<a_client<<"] trying to create group ["<<v_msg[1]<<"]"<<std::endl;
        if(m_private.addNewGroup(v_msg[1],a_client)){
            msg = "3~accept~ ";
            sendMessage(msg, a_client);
        }
        else{
            msg = "3~refuse~ ";
            sendMessage(msg, a_client);
        }
        break;

    case ADD_USER_TO_GROUP: /// add new client to group
        boost::split(v_msg, msg, boost::is_punct());
        std::cout<<"Socket ["<<a_client<<"] trying to add client ["<<v_msg[2]<<"] to group ["<<v_msg[1]<<"]"<<std::endl;
        msg = "4~refuse~";
        for(auto t_fd: m_setClients){
            if(loginToDescriptor(v_msg[2]) == t_fd){
                if(m_private.addNewClientToGroup(v_msg[1],loginToDescriptor(v_msg[2]))){ ///< try add to group descriptor and login (get from descriptor)
                    msg = "2~"+descriptorToLogin(a_client)+"~ added you to group ["+v_msg[1]+"] ~ ";
                    sendMessage(msg,loginToDescriptor(v_msg[2]));
                    msg = "4~accept~";
                }
                else{
                    msg = "4~refuse~";
                }
            }
        }
        sendMessage(msg, a_client);
        break;

    case MESSAGE_TO_GROUP: /// send message to group
        boost::split(v_msg, msg, boost::is_punct());
        std::cout<<"Socket ["<<a_client<<"] send message to group ["<<v_msg[1]<<"]"<<std::endl;
        for(auto t_fd : m_private.getClients(v_msg[1])){ ///< get clients from correct name of group and redirect message
            for(auto l_fd: m_setClients){
                if(l_fd == t_fd){
                    msg = "5~"+descriptorToLogin(a_client)+"~"+v_msg[2]+'~';
                    sendMessage(msg, t_fd);
                    std::cout<<"Message to group member"<<std::endl;
                }
            }
        }
        break;

    case USERS_LIST: /// send client list
        boost::split(v_msg, msg, boost::is_punct());
        msg="6~";
        if(v_msg[1].compare("all") == 0){
            std::cout<<"Socket ["<<a_client<<"] request for list of all"<<std::endl;
            for(auto t_fd : m_setLogins){
                if(t_fd != NULL){
                    msg = msg + t_fd->getLogin() + "~"; ///< increse string with another login get from online clients
                }
            }
            sendMessage(msg, a_client);
        }
        else{
            std::cout<<"Socket ["<<a_client<<"] request for list of group ["<<v_msg[1]<<"]"<<std::endl;
            for(auto t_fd : m_private.getClients(v_msg[1]))
                if(descriptorToLogin(t_fd).compare("unknown"))
                    msg = msg + descriptorToLogin(t_fd) + "~"; ///< increse string with another login get from group clients
            sendMessage(msg, a_client);
        }
        break;

    case LOGOUT: /// logout
        std::cout<<"Socket ["<<a_client<<"] logout"<<std::endl;
        for(auto login : m_setLogins){
            if(login != NULL && login->getFd() == a_client){
                msg = "2~server~"+descriptorToLogin(a_client)+" disconnect ~ "; ///< find in online clients set selected socket and delete it
                m_setLogins.erase(m_setLogins.begin() + iterator);
            }
            iterator++;
        }
        sendMessage("7~accept~", a_client); ///< send confirm to client
        sendMessage(msg, 0); ///< send broadcast
        a_client= 0;
        break;

    case EXIT: // exit
        std::cout<<"Socket ["<<a_client<<"] send close server request"<<std::endl;
        if((descriptorToLogin(a_client)).compare("admin") == 0){
            sendMessage("8~accept~", a_client);
            Exit(1);
        }else{
            sendMessage("8~refuse~", a_client);
        }
        break;
    }
}

std::string Server::loginToServer(std::string a_login, std::string a_password, int a_client){
    std::string msg = "0~refuse~ ";
    for(auto user : m_setUsers){
        if(user != NULL && user->checkLog(a_login,a_password)){ ///< is login and password correct
            msg = "0~accept~ ";
            for(auto login : m_setLogins){
                if(login != NULL && a_login.compare(login->getLogin()) == 0){ ///< is already logged in
                    msg = "0~refuse~ ";
                }
            }
        }
    }

    if(msg.compare("0~accept~ ") == 0){
        m_setLogins.push_back(new Login(a_client, a_login)); ///< if all correct push login to online clients
    }

    return msg;
}

std::string Server::createAccount(std::string a_login, std::string a_password, int a_client){
    std::string msg = "0~refuse~ ";
    m_isAvailable = true;

    for(auto user : m_setUsers){
        if(user != NULL && a_login.compare(user->getLogin())==0){ ///< is login already exist
            msg = "1~refuse~ ";
            m_isAvailable = false;
        }
    }
    if(m_isAvailable){
        msg = "1~accept~ ";
        m_setUsers.push_back(new User(a_login,a_password)); ///< create account and add to online clients
        m_setLogins.push_back(new Login(a_client,a_login));
    }
    return msg;
}

void Server::logout(int16_t &a_client){
    std::string msg = "";
    int16_t iterator = 0;
    for(auto login : m_setLogins){
        if(login != NULL && login->getFd() == a_client){ ///<< find login for descriptor
            msg = "2~server~"+descriptorToLogin(a_client)+" disconnect ~ ";  ///<send broadcast to all with disconnect info
            m_setLogins.erase(m_setLogins.begin() + iterator);  ///< delete from online clients
        }
        iterator++;
    }
    sendMessage(msg, 0);
    a_client= 0;
}

