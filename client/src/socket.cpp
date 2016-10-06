#include "socket.h"

Socket::Socket()
{

}

Socket::~Socket(){

}


int16_t Socket::Connect(int16_t a_sock, sockaddr_in &a_server){
    return connect(a_sock , (sockaddr *)&a_server , sizeof(a_server));
}

int16_t Socket::SetSocket(){
    return socket(AF_INET , SOCK_STREAM , 0);
}

int16_t Socket::Send(int16_t a_sock, std::string a_message){
    return send(a_sock , a_message.c_str() , strlen( a_message.c_str() ) , 0);
}

int16_t Socket::Receive(int16_t a_sock, std::string &a_buff){
    char buffer[512];
    int retVal = read(a_sock , buffer , 512);
    a_buff = buffer;
    return retVal;

}


