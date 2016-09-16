
#include "server.h"
#define MAX_CLIENTS 10

Server::Server(int16_t a_port)
    :m_port(a_port){

    m_dataFile.open("users.data");
    if(m_dataFile.is_open()){
        std::cout<<"Found file with data"<<std::endl;
        if(IReadFile())
            std::cout<<"Data has been loaded to the server"<<std::endl;
    }
    else
        std::cout<<"No file found, creating new one"<<std::endl;

    m_tv.tv_sec = 5;
    m_tv.tv_usec = 0;

    if(!ISetSocket(a_port)) // Socket reserving
        exit(1);

    if(IBindPort()) // binding port
        IStartListening(a_port);
    else
        exit(1);
}

Server::~Server(){
    std::string save;
    for(auto user : m_setUsers){
        save = save + user->ISaveToFile();
    }
    m_dataFile<<save;

    m_dataFile.close(); // close file and the end

    std::cout<<"Exit";
}

std::string Server::IDescriptorToLogin(int a_client){ // get login from number
    for(auto login : m_setLogins){
        if(login->IGetFd() == a_client)
            return login->IGetLogin();
    }
    return "empty";
}

int Server::ILoginToDescriptor(std::string a_client){ // get number from login
    for(auto login : m_setLogins){
        if(a_client.compare(login->IGetLogin()) == 0)
            return login->IGetFd();
    }
    return 0;
}

bool Server::IReadFile(){  // read users from file
    int16_t i = 0; std::string temp;
    std::string login, password;

    while(std::getline(m_dataFile,temp,'-')){
        i++;
        if(i==1)
            login = temp;
        if(i==2){
            password = temp;
            m_setUsers.push_back(new User(login, password));
            i=0;
        }
    }
    return true;
}

bool Server::ISetSocket(int16_t a_port){
    if ((m_sd = socket (AF_INET, SOCK_STREAM, 0)) == -1)
    {
        perror ("[server] socket() Error.\n");
        return false;
    }
    else
    {
        setsockopt(m_sd, SOL_SOCKET, SO_REUSEADDR,&m_tv,sizeof(struct timeval));

        bzero (&m_serverSocket, sizeof (m_serverSocket));

        m_serverSocket.sin_family = AF_INET;
        m_serverSocket.sin_addr.s_addr = htonl (INADDR_ANY);
        m_serverSocket.sin_port = htons (a_port);
        return true;
    }
}

bool Server::IBindPort(){
    if (bind (m_sd, (struct sockaddr *) &m_serverSocket, sizeof (struct sockaddr)) == -1)
    {
        perror ("[server] bind() Error.\n");
        return false;
    }
    else
        return true;
}

bool Server::IStartListening(int16_t a_port){

    if (listen (m_sd, 5) == -1)
    {
        perror ("[server] listen() Error.\n");
        exit(1);
    }

    FD_ZERO (&m_actfds);
    FD_SET (m_sd, &m_actfds);

    m_nfds = m_sd;

    std::cout<<"[server] Wait at port["<<m_port<<"]"<<std::endl;
    fflush (stdout);

    while (1)
    {
        bcopy ((char *) &m_actfds, (char *) &m_readfds, sizeof (m_readfds));

        if (select (m_nfds+1, &m_readfds, NULL, NULL, &m_tv) < 0)
        {
            perror ("[server] select() Error.\n");
            exit(1);
        }
        if (FD_ISSET (m_sd, &m_readfds))
        {
            m_len = sizeof (m_clientSocket);
            bzero (&m_clientSocket, sizeof (m_clientSocket));

            m_client = accept (m_sd, (struct sockaddr *) &m_clientSocket, &m_len);

            if (m_client < 0)
            {
                perror ("[server] accept() Error.\n");
                continue;
            }

            if (m_nfds < m_client)
                m_nfds = m_client;

            FD_SET (m_client, &m_actfds);

            std::cout<<"[server] Client with descriptor "<< m_client <<" connected."<<std::endl;

            m_setClients.push_back(m_client);

            fflush (stdout);
        }

        IIncommingConnection();
    }
}

bool Server::ISendMessage(std::string a_message, int16_t a_client){
    if(a_client == 0){
        for(auto fd: m_setClients){
            write (fd, a_message.c_str(), sizeof(a_message.c_str()));
        }
    } else {
        write (a_client, a_message.c_str(), sizeof(a_message.c_str()));
    }

}

void Server::IIncommingConnection(){

    for(auto fd: m_setClients)
    {
        fflush (stdout);

        if (FD_ISSET (fd, &m_readfds))
        {
            std::cout<<read (fd, m_buffer, sizeof (m_buffer))<<std::endl;
            std::cout<<"[client-"<<fd<<"]: "<< m_buffer<<std::endl;

            std::string msg = m_buffer;
            std::vector <std::string> v_msg;

            switch(m_buffer[0])
            {
            case '0': // log in to exist account
                std::cout<<"Case - 0"<<std::endl;
                boost::split(v_msg, msg, boost::is_punct());
                for(auto user : m_setUsers){
                    if(user->ICheckLog(v_msg[1],v_msg[2])){
                        msg = "0.accept";
                        m_setLogins.push_back(new Login(fd,v_msg[1]));
                        break;
                    }
                    else
                        msg = "0.refuse";
                }
                ISendMessage(msg,fd);
                break;

            case '1': // create new account request
                std::cout<<"Case - 1"<<std::endl;

                m_isAvailable = true;
                boost::split(v_msg, msg, boost::is_punct());
                for(auto user : m_setUsers){
                    if(v_msg[1].compare(user->IGetLogin())==0){
                        msg = "1.refuse";
                        ISendMessage(msg, fd);
                        m_isAvailable = false;
                    }
                }
                if(m_isAvailable){
                    msg = "1.accept";
                    ISendMessage(msg, fd);
                    m_setUsers.push_back(new User(v_msg[1],v_msg[2]));
                    m_setLogins.push_back(new Login(fd,v_msg[1]));
                }
                break;

            case '2': // broadcast message
                boost::split(v_msg, msg, boost::is_punct());
                msg = v_msg[1];
                ISendMessage(msg, 0);
                break;

            case '3': // add new group
                boost::split(v_msg, msg, boost::is_punct());
                for(auto t_fd: m_setClients){
                    if(t_fd == stoi(v_msg[2])){
                        if(m_private.IAddNewGroup(v_msg[1],std::stoi(v_msg[2]))){
                            msg = "3.accept";
                            ISendMessage(msg, fd);
                        }
                        else{
                            msg = "3.refuse";
                            ISendMessage(msg, fd);
                        }
                    }
                    else{
                        msg = "3.refuse";
                        ISendMessage(msg, fd);
                    }
                }

                break;

            case '4': // add new client to group
                boost::split(v_msg, msg, boost::is_punct());
                for(auto t_fd: m_setClients){
                    if(t_fd == stoi(v_msg[2])){
                        if(m_private.IAddNewClientToGroup(v_msg[1],std::stoi(v_msg[2]))){
                            msg = "4.accept";
                            ISendMessage(msg, fd);
                        }
                        else{
                            msg = "4.refuse";
                            ISendMessage(msg, fd);
                        }
                    }
                }
                break;

            case '5': // send message to group
                boost::split(v_msg, msg, boost::is_punct());
                for(auto fd : m_private.IGetClients(v_msg[1]))
                    ISendMessage(v_msg[2], fd);
                break;

            case '6': // send client list
                boost::split(v_msg, msg, boost::is_punct());
                msg="";
                for(auto t_fd : m_private.IGetClients(v_msg[1]))
                    msg = msg + IDescriptorToLogin(t_fd) + ".";
                ISendMessage(msg, fd);
                break;

            case '7': // logout
                msg="";
                for(auto login : m_setLogins){
                    if(fd == login->IGetFd()){
                        std::cout<<"Login:"<<login->IGetLogin()<<" Fd:"<<login->IGetFd()<<std::endl;
                        //m_setLogins.remove(login);
                        msg="7.accept";
                    }
                }
                ISendMessage(msg, fd);
                //close(fd);
                break;

            case '9': // send client list
                exit(1);
                break;
            }
        }
    }
}


