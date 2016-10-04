#include "socket.h"
#define BUFF_SIZE 256
using namespace std;

Socket::Socket(){

}

Socket::~Socket(){

}

bool Socket::Bind(int16_t &a_sd, sockaddr_in &a_serverSocket){
    bool retVal = false;
    if (bind (a_sd, (sockaddr *) &a_serverSocket, sizeof (sockaddr)) == -1)
    {
        retVal = false;
    }
    else{
        retVal = true;
    }
    return retVal;
}

bool Socket::Connect(int16_t &a_sd){
    bool retVal = true;
    if ((a_sd = socket (AF_INET, SOCK_STREAM, 0)) == -1)
    {
        perror ("[server] socket() Error.\n");
        retVal = false;
    }
    return retVal;
}

void Socket::SetSocket(int16_t &a_sd, timeval &a_tv,sockaddr_in &a_serverSocket, int16_t a_port){

    setsockopt(a_sd, SOL_SOCKET, SO_REUSEADDR,&a_tv,sizeof(timeval));

    bzero (&a_serverSocket, sizeof (a_serverSocket));

    a_serverSocket.sin_family = AF_INET;
    a_serverSocket.sin_addr.s_addr = htonl (INADDR_ANY);
    a_serverSocket.sin_port = htons (a_port);
}

void Socket::Listen(int16_t a_sd){
    if (listen (a_sd, 5) == -1)
    {
        perror ("[server] listen() Error.\n");
        exit(1);
    }
}
bool Socket::Send(int16_t fd, string a_message){
    bool retVal = false;

    if(write(fd, a_message.c_str(), strlen(a_message.c_str()))<0){
        retVal = false;
    }
    else{
       retVal = true;
    }
    return retVal;
}
bool Socket::Receive(int16_t a_setClient,char *a_buffer){
    bool status = 0;
    cout<<"MSG SIZE: "<<sizeof (a_buffer);
    status = read(a_setClient, a_buffer, BUFF_SIZE);

    return status;
}


