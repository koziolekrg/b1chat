#include "client.h"
Client::Client()
{
    sock = -1;
    port = 0;
    address = "";
    isLoggedIn = false;

}

Client::~Client(){

}

void Client::IConnect(std::string address , int port)
{
    if(sock == -1)
    {
        //Create socket
        sock = socket(AF_INET , SOCK_STREAM , 0);
        if (sock == -1)
        {
            perror("Could not create socket");
        }

        std::cout<<"Socket created\n";
    }
    else    {   /* OK , nothing */  }

    //setup address structure
    if(inet_addr(address.c_str()) == -1)
    {
        struct hostent *he;
        struct in_addr **addr_list;

        //resolve the hostname, its not an ip address
        if ( (he = gethostbyname( address.c_str() ) ) == NULL)
        {
            //gethostbyname failed
            herror("gethostbyname");
            std::cout<<"Failed to resolve hostname\n";
        }

        //Cast the h_addr_list to in_addr , since h_addr_list also has the ip address in long format only
        addr_list = (struct in_addr **) he->h_addr_list;

        for(int i = 0; addr_list[i] != NULL; i++)
        {
            //strcpy(ip , inet_ntoa(*addr_list[i]) );
            server.sin_addr = *addr_list[i];

            std::cout<<address<<" resolved to "<<inet_ntoa(*addr_list[i])<<std::endl;

            break;
        }
    }

    //plain ip address
    else
    {
        server.sin_addr.s_addr = inet_addr( address.c_str() );
    }

    server.sin_family = AF_INET;
    server.sin_port = htons( port );

    //Connect to remote server
    if (connect(sock , (struct sockaddr *)&server , sizeof(server)) < 0)
    {
        perror("connect failed. Error");
    }

    std::cout<<"Connected\n";

}

void Client::ISend_data()
{
    std::string data;
    std::string menu;
    int state;
    while(1){
        data = "";

        std::cout<<"LOG:"<<isLoggedIn;

        if(isLoggedIn == false){
            std::cout<<"0 - LOGIN\n1 - CREATE ACCOUNT :";
            std::cin>>menu; data = menu+".";

            std::cout<<"Login:";
            std::cin>>menu; data = data + menu+".";

            std::cout<<"Password:";
            std::cin>>menu; data = data + menu+".";

            if( send(sock , data.c_str() , strlen( data.c_str() ) , 0) < 0)
            {
                perror("Send failed : ");
            }
            sleep(3);
        }
        else{

            std::cout<<"\n1 - Send broadcast\n2 - Create group\n3 - Add client to group\n4 - Send MSG to group\n5 - Get online clients\n6 - Logout\n";
            std::cin>>state;
            IMainMenu(state);
        }
    }
}

void Client::IReceive_data()
{
    int size=512;
    char buffer[size];
    std::string reply;

    //Receive a reply from the server
    while(1){
        if( recv(sock , buffer , sizeof(buffer) , 0) < 0)
        {
            puts("recv failed");
        }

        reply = buffer;
        if(reply.compare("0.accept")==0 || reply.compare("1.accept")==0){
            isLoggedIn = true;
            std::cout<<"Connected to the server success"<<std::endl;
        }
        if(reply.compare("0.refuse")==0 || reply.compare("1.refuse")==0){
            isLoggedIn = false;
            std::cout<<"Connection refuse"<<std::endl;
        }
    }
}

void Client::IMainMenu(int a_state){
    std::string menu="";
    std::string data="";

    switch(a_state){
    case 1:
        std::cout<<"Type message to send:";
        std::cin>>menu; data = "2."+menu+".";
        if( send(sock , data.c_str() , strlen( data.c_str() ) , 0) < 0)
        {
            perror("Send failed : ");
        }
        break;

    case 2:
        std::cout<<"Type group name:";
        std::cin>>menu; data = "3."+menu+".";
        if( send(sock , data.c_str() , strlen( data.c_str() ) , 0) < 0)
        {
            perror("Send failed : ");
        }
        break;

    case 3:
        std::cout<<"Type group name:";
        std::cin>>menu; data = "4."+menu+".";
        std::cout<<"Type user name you want to add:";
        std::cin>>menu; data = data + menu+".";
        if( send(sock , data.c_str() , strlen( data.c_str() ) , 0) < 0)
        {
            perror("Send failed : ");
        }
        break;

    case 4:
        std::cout<<"Type group name:";
        std::cin>>menu; data = "5."+menu+".";
        std::cout<<"Type message to send:";
        std::cin>>menu; data = data + menu+".";
        if( send(sock , data.c_str() , strlen( data.c_str() ) , 0) < 0)
        {
            perror("Send failed : ");
        }
        break;

    case 5:
        std::cout<<"all - list all users\ngroup name - list of group users:";
        std::cin>>menu; data = "6."+menu+".";
        std::cout<<"Type message to send:";
        std::cin>>menu; data = data + menu+".";
        if( send(sock , data.c_str() , strlen( data.c_str() ) , 0) < 0)
        {
            perror("Send failed : ");
        }
        break;

    case 6:
        std::cout<<"Confirm password to logout";
        std::cin>>menu; data = "7."+menu+".";
        if( send(sock , data.c_str() , strlen( data.c_str() ) , 0) < 0)
        {
            perror("Send failed : ");
        }
        break;
    }
}

