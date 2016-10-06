
#include <stdio.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <netdb.h>
#include <iostream>
#include <gtest/gtest.h>
#include <gmock/gmock.h>
#define private public
#include "client.h"
#include "mocksocket.h"

#define PORT 8888
using namespace testing;

TEST(connection, connectionFalse){
    MockSocket socket;
    ON_CALL(socket, SetSocket()).WillByDefault(Return(-1));
    ON_CALL(socket, Connect(_,_)).WillByDefault(Return(-1));

    Client *client = new Client(socket);
    ASSERT_FALSE(client->connectToServer("127.0.0.1", 8888));
    delete client;
}

TEST(connection, setSocketFalse){
    MockSocket socket;
    ON_CALL(socket, SetSocket()).WillByDefault(Return(-1));
    ON_CALL(socket, Connect(_,_)).WillByDefault(Return(1));

    Client *client = new Client(socket);
    ASSERT_FALSE(client->connectToServer("127.0.0.1", 8888));
    delete client;
}

TEST(connection, connectFalse){
    MockSocket socket;
    ON_CALL(socket, SetSocket()).WillByDefault(Return(1));
    ON_CALL(socket, Connect(_,_)).WillByDefault(Return(-1));

    Client *client = new Client(socket);
    ASSERT_FALSE(client->connectToServer("127.0.0.1", 8888));
    delete client;
}

TEST(connection, correctConnection){
    MockSocket socket;
    ON_CALL(socket, SetSocket()).WillByDefault(Return(1));
    ON_CALL(socket, Connect(_,_)).WillByDefault(Return(1));

    Client *client = new Client(socket);
    ASSERT_TRUE(client->connectToServer("127.0.0.1", 8888));
    delete client;
}

TEST(message, sendMessageCorrect){
    MockSocket socket;
    ON_CALL(socket, Send(_,_)).WillByDefault(Return(1));

    Client *client = new Client(socket);
    ASSERT_TRUE(client->sendMessage("127.0.0.1"));
    delete client;
}

TEST(message, sendMessageIncorrect){
    MockSocket socket;
    ON_CALL(socket, Send(_,_)).WillByDefault(Return(-1));

    Client *client = new Client(socket);
    ASSERT_FALSE(client->sendMessage("127.0.0.1"));
    delete client;
}

TEST(message, receiveCorrect){
    MockSocket socket;
    ON_CALL(socket, Receive(_,_)).WillByDefault(Return(1));

    string temp = "";
    Client *client = new Client(socket);
    ASSERT_TRUE(client->receiveMessage(temp));

    delete client;
}

TEST(message, receiveIncorrect){
    MockSocket socket;
    ON_CALL(socket, Receive(_,_)).WillByDefault(Return(-1));

    string temp = "";
    Client *client = new Client(socket);
    ASSERT_FALSE(client->receiveMessage(temp));

    delete client;
}

int main(int argc, char *argv[])
{

    testing::InitGoogleTest(&argc, argv);
    testing::InitGoogleMock(&argc, argv);
    return RUN_ALL_TESTS();

}


