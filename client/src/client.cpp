#include "client.h"
Client::Client(std::string a_hostAddress, int a_port)
{
    m_counter =0;
    m_isLogIn = 0;
    m_sock = socket(AF_INET , SOCK_STREAM , 0);
    if (m_sock == -1)
    {
        printf("Could not create socket");
    }

    m_server.sin_addr.s_addr = inet_addr(a_hostAddress.c_str());
    m_server.sin_family = AF_INET;
    m_server.sin_port = htons(a_port);

    if (connect(m_sock , (struct sockaddr *)&m_server , sizeof(m_server)) < 0){
        perror("connect failed. Error");
        exit(1);
    }

    puts("Connected\n");

    fd_set all_set, r_set;
    int maxfd = m_sock + 1;
    FD_ZERO(&all_set);
    FD_SET(STDIN_FILENO, &all_set); FD_SET(m_sock, &all_set);
    r_set = all_set;
    struct timeval tv; tv.tv_sec = 2; tv.tv_usec = 0;

    //set the initial position of after
    m_after = m_message;

    puts("Connecting to server..");

    for(;;){

        r_set = all_set;
        //check to see if we can read from STDIN or sock
        select(maxfd, &r_set, NULL, NULL, &tv);

        while(!m_isLogIn)
            m_isLogIn = logIn(r_set);

        receiving(r_set);

    }

    close(m_sock);
}

Client::~Client(){

}

bool Client::logIn(fd_set a_r_set){

    std::string login, password, state;

    std::cout<<"0 - LOGIN\n1 - CREATE ACCOUNT: ";
    std::cin>>state;

    std::cout<<"Enter login: ";
    std::cin>>login;

    std::cout<<"Enter login: ";
    std::cin>>password;

    login = state+"."+login+"."+password+".";

    send(m_sock, login.c_str(), strlen(login.c_str()) + 1, 0);

    recv(m_sock , m_server_reply , 256 , 0);


    if(strcmp(m_server_reply,"0.accept") == 0 || strcmp(m_server_reply,"1.accept") == 0){
        std::cout<<"Login success";
        return true;
    }
    else{
        std::cout<<"\nWrong login or password\n";
        return false;
    }

}

bool Client::receiving(fd_set a_r_set){

    if(FD_ISSET(STDIN_FILENO, &a_r_set)){

        if(buffer_message(m_message) == COMPLETE){
            //Send some data
            if(send(m_sock, m_message, strlen(m_message) + 1, 0) < 0)//NOTE: we have to do strlen(message) + 1 because we MUST include '\0'
            {
                puts("Send failed");
                return true;
            }

            std::cout<<"\n1 - Send broadcast\n2 - Create group\n3 - Add client to group\n4 - Send MSG to group\n5 - Get online clients\n6 - Logout\n";
        }
    }

    if(FD_ISSET(m_sock, &a_r_set)){
        //Receive a reply from the server
        if( recv(m_sock , m_server_reply , 256 , 0) < 0)
        {
            puts("recv failed");
            return true;
        }

        printf("\nServer Reply: %s\n", m_server_reply);
        m_server_reply[0]='\0';

    }

}

int Client::buffer_message(char * a_message){


    short flag = -1; // indicates if returned_data has been set
    int where; // location of network newline
    char * null_c = {'\0'};


    int bytes_read = read(STDIN_FILENO, m_after, 256 - m_inbuf);

    m_inbuf += bytes_read;

    // call findeol, store result in where
    where = find_network_newline(a_message, m_inbuf);
    if (where >= 0) {

        // place a null terminator at the end of the string
        memcpy(a_message + where, &null_c, 1);

        // update inbuf and remove the full line from the clients's buffer
        memmove(a_message, a_message + where + 1, m_inbuf - (where + 1));
        m_inbuf -= (where+1);
        flag = 0;
    }

    //update room and after, in preparation for the next read
    m_room = sizeof(m_message) - m_inbuf;
    m_after = m_message + m_inbuf;

    return flag;


}

int Client::find_network_newline(char * a_message, int a_bytes_inbuf){
    int i;
    for(i = 0; i<m_inbuf; i++){
        if( *(a_message + i) == '\n')
            return i;
    }
    return -1;
}
