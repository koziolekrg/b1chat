#pragma once
#include "isocket.h"
#include <gmock/gmock.h>

class MockSocket : public ISocket{
public:
MockSocket(){}
    MOCK_METHOD2(Bind, bool(int16_t &a_sd, sockaddr_in &a_serverSocket));
    MOCK_METHOD1(Connect, bool(int16_t &a_sd));
    MOCK_METHOD4(SetSocket, void(int16_t &a_sd, timeval &a_tv,sockaddr_in &a_serverSocket, int16_t a_port));
    MOCK_METHOD1(Listen, void(int16_t a_sd));
    MOCK_METHOD2(Send, bool(int16_t fd, string a_message));
    MOCK_METHOD2(Receive, bool(int16_t a_setClient,char *a_buffer));
    MOCK_METHOD1(getAddress, std::string(int16_t a_fd));
};
