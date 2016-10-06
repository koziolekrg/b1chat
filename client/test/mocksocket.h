#pragma once
#include "isocket.h"
#include <gmock/gmock.h>
#include <string>

using namespace std;

class MockSocket : public ISocket{
public:
    MockSocket(){}
    MOCK_METHOD2(Connect, int16_t(int16_t a_sock, sockaddr_in &a_server));
    MOCK_METHOD0(SetSocket, int16_t());
    MOCK_METHOD2(Send, int16_t(int16_t m_sock, string a_message));
    MOCK_METHOD2(Receive, int16_t(int16_t a_sock, string &a_buff));

};
