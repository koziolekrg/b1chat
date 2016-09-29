#include "client.h"

enum menuState {LOGIN, CREATE_ACCOUNT, BROADCAST, CREATE_GROUP, ADD_TO_GROUP, LIST_USERS, LOGOUT};

Client::Client()
{
    m_isLoggedIn = false;
    m_sock = -1;

}

Client::~Client(){

}

void Client::IConnect(std::string a_address, int a_port)
{
    if(m_sock == -1)
    {
        ///Create socket
        m_sock = socket(AF_INET , SOCK_STREAM , 0);
        if (m_sock == -1)
        {
            perror("Could not create socket");
        }
        std::cout<<"Socket created\n";
    }
    else    {   /* OK , nothing */  }

    ///setup address structure
    if(inet_addr(a_address.c_str()) == -1)
    {
        hostent *he;
        in_addr **addr_list;

        ///resolve the hostname, its not an ip address
        if ( (he = gethostbyname( a_address.c_str() ) ) == NULL)
        {
            herror("gethostbyname");
            std::cout<<"Failed to resolve hostname\n";
        }

        ///Cast the h_addr_list to in_addr , since h_addr_list also has the ip address in long format only
        addr_list = (in_addr **) he->h_addr_list;

        for(int i = 0; addr_list[i] != NULL; i++)
        {
            m_server.sin_addr = *addr_list[i];

            std::cout<<a_address<<" resolved to "<<inet_ntoa(*addr_list[i])<<std::endl;

            break;
        }
    }

    ///plain ip address
    else
    {
        m_server.sin_addr.s_addr = inet_addr( a_address.c_str() );
    }

    m_server.sin_family = AF_INET;
    m_server.sin_port = htons(a_port);

    ///Connect to remote server
    if (connect(m_sock , (sockaddr *)&m_server , sizeof(m_server)) < 0)
    {
        perror("connect failed. Error");
    }

    std::cout<<"Connected\n";

}

bool Client::ISend(std::string a_msg){
    bool retVal = true;
    if( send(m_sock , a_msg.c_str() , strlen( a_msg.c_str() ) , 0) < 0)
    {
        perror("Send failed : ");
        retVal = false;
    }
    return retVal;
}

void Client::ILogin()
{
    std::string data;
    std::string menu;
    int state;
    while(1){
        data = "";

        if(false == m_isLoggedIn){
            std::cout<<"0 - LOGIN\n1 - CREATE ACCOUNT :";
            std::cin>>menu; data = menu+"~";

            std::cout<<"Login:";
            std::cin>>menu; data = data + menu+"~";

            std::cout<<"Password:";
            std::cin>>menu; data = data + menu+"~";


            std::cout<<"LOG: "<< data;
            if( send(m_sock , data.c_str() , strlen( data.c_str() ) , 0) < 0)
            {
                perror("Send failed : ");
            }
            sleep(1);
        }
        else{

            std::cout<<"\n1 - Send broadcast\n2 - Create group\n3 - Add client to group\n4 - Send MSG to group\n5 - Get online clients\n6 - Logout\n";

            std::cin>>state;
            IMainMenu(state);
        }
    }
}

void Client::IReceive()
{
    int size=512;
    char buffer[size];
    std::string reply;
    std::vector <std::string> v_msg;

    ///Receive a reply from the server
    while(1){

        fflush (stdout);

        if( recv(m_sock , buffer , sizeof(buffer) , 0) < 0)
        {
            puts("recv failed");
        }

        reply = buffer;

        boost::split(v_msg, reply, boost::is_any_of("~"));

        if(v_msg[0] == "0" || v_msg[0] == "1"){
            if(v_msg[1].compare("accept") == 0){
                mutexLog.lock(); m_isLoggedIn = true; mutexLog.unlock();
                std::cout<<"[Server] Connected to the server success"<<std::endl;
            }
            if(v_msg[1].compare("refuse") == 0){
                mutexLog.lock(); m_isLoggedIn = false; mutexLog.unlock();
                std::cout<<"[Server] Connection refused"<<std::endl;
            }
        }
        if(v_msg[0] == "2"){
            std::cout<<"["<<v_msg[1]<<"]"<<v_msg[2]<<std::endl;
        }

        if(v_msg[0] == "3"){
            if(v_msg[1].compare("accept") == 0){
                std::cout<<"[Server] Group created"<<std::endl;
            }
            if(v_msg[1].compare("refuse") == 0){
                std::cout<<"[Server] Group didn't' create"<<std::endl;
            }
        }
        if(v_msg[0] == "4"){
            if(v_msg[1].compare("accept") == 0){
                std::cout<<"[Server] Client added"<<std::endl;
            }
            if(v_msg[1].compare("refuse") == 0){
                std::cout<<"[Server] Client didn't add"<<std::endl;
            }
        }
        if(v_msg[0] == "5"){
            boost::split(v_msg, reply, boost::is_punct());
            std::cout<<"["<<v_msg[1]<<"]"<<v_msg[2]<<std::endl;
        }
        if(v_msg[0] == "6"){
            boost::split(v_msg, reply, boost::is_punct());
            for(int i=1; i<v_msg.size()-1; i++){
                if(v_msg[i].length() > 1)
                    std::cout<<"- "<<v_msg[i]<<std::endl;
            }
        }
        if(v_msg[0] == "7"){
            if(v_msg[1].compare("accept") == 0){
                std::cout<<"Good bye";
                close(m_sock);
                exit(1);
            }
            else
            std::cout<<"Incorrect password";
        }

        v_msg.clear();
        reply = "";
        memset(buffer, 0, sizeof(buffer));

    }
}

void Client::IMainMenu(int a_state){
    std::string menu="";
    std::string data="";

    std::cin.ignore();
    ///handle menu input
    switch(a_state){
    case 1:
        std::cout<<"Type message to send:";
        std::getline(std::cin,menu);
        data = "2~"+menu+"~";
        ISend(data);
        break;

    case 2:
        std::cout<<"Type group name:";
        std::cin>>menu;
        data = "3~"+menu+"~";
        ISend(data);
        break;

    case 3:
        std::cout<<"Type group name:";
        std::cin>>menu;
        data = "4~"+menu+".";
        std::cout<<"Type user name you want to add:";
        std::cin>>menu;
        data = data + menu+"~";
        ISend(data);
        break;

    case 4:
        std::cout<<"Type group name:";
        std::cin>>menu;
        data = "5~"+menu+".";
        std::cout<<"Type message to send:";
        std::cin.ignore();
        std::getline(std::cin,menu);
        data = data + menu+".";
        ISend(data);
        break;

    case 5:
        fflush(stdin);
        std::cout<<"all - list all users\ngroup name - list of group users:";
        std::getline(std::cin,menu);
        data = "6~"+menu+"~";
        ISend(data);

        std::cout<<"MSG: "<<data<<std::endl;
        break;

    case 6:
        data = "7~";
        ISend(data);
        std::cout<<"Good bye";
        exit(1);

        break;
    case 8:
        std::cout<<"EXIT";
        ISend("8~");
        break;
    default:
        std::cout<<"Wrong choose"<<std::endl;

     std::cin.ignore();
    }
}

