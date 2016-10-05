
#include <stdio.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <netdb.h>
#include <iostream>
#include <gtest/gtest.h>
#include <gmock/gmock.h>
#define private public
#include "server.h"
#include "mocksocket.h"

#define PORT 8888
using namespace testing;

TEST(group, groupTitle){
    Group *group = new Group("Test", 1);
    ASSERT_EQ("Test", group->IGetTitle());
    delete group;
}

TEST(group, correctAddClient){
    Group *group = new Group("Test", 1);
    ASSERT_EQ(true, group->IAddClient(2));
    delete group;
}

TEST(group, incorrectAddClient){
    Group *group = new Group("Test", 1);
    ASSERT_EQ(false, group->IAddClient(1));
    delete group;
}

TEST(group, listClient){
    Group *group = new Group("Test", 1);
    group->IAddClient(2);
    int temp = (group->IGetClientsList())[1];
    ASSERT_EQ(2, temp);
    delete group;
}

TEST(privGroup, correctAddNewGroup){
    Priv priv;
    ASSERT_EQ(true, priv.IAddNewGroup("G1",4));
}

TEST(privGroup, correctAddNewGroup_1){
    Priv priv;
    priv.IAddNewGroup("G1",2);
    ASSERT_EQ(true, priv.IAddNewGroup("G2",4));
}

TEST(privGroup, incorrectAddNewGroup){
    Priv priv;
    priv.IAddNewGroup("G1",2);
    ASSERT_EQ(false, priv.IAddNewGroup("G1",4));
}

TEST(privGroup, correctAddNewClientGroup_1){
    Priv priv;
    priv.IAddNewGroup("G1",2);
    ASSERT_EQ(true, priv.IAddNewClientToGroup("G1", 3));
}

TEST(privGroup, correctAddNewClientGroup_2){
    Priv priv;
    priv.IAddNewGroup("G1",2);
    priv.IAddNewClientToGroup("G1", 4);
    ASSERT_EQ(true, priv.IAddNewClientToGroup("G1", 3));
}

TEST(privGroup, incorrectAddNewClientGroup){
    Priv priv;
    priv.IAddNewGroup("G1",2);
    ASSERT_EQ(false, priv.IAddNewClientToGroup("G2", 3));
}

TEST(account, succesfulCreate){
    Server *server = new Server();
    ASSERT_EQ("1~accept~ ",server->CreateAccount("pawel","haslo",1));
    delete server;
}

TEST(account, failureCreate){
    Server *server = new Server();
    server->CreateAccount("pawel","haslo",1);
    ASSERT_EQ("1~refuse~ ",server->CreateAccount("pawel","haslo",1));
    delete server;
}

TEST(account, logoutAndSuccesfulLogin){
    int16_t temp =1;
    Server *server = new Server();
    server->CreateAccount("pawel","haslo",1);
    server->Logout(temp);
    ASSERT_EQ("0~accept~ ", server->LoginToServer("pawel","haslo",1));
    delete server;
}

TEST(account, failureLogin){
    Server *server = new Server();
    ASSERT_EQ("0~refuse~ ", server->LoginToServer("pawel","haslo",1));
    delete server;
}

TEST(file, savefile){
    Server *server = new Server();
    server->CreateAccount("pawel","haslo",1);
    ASSERT_EQ(true,server->ISaveFile());
    delete server;
}

TEST(file, readfile){
    Server *server = new Server();
    server->IReadFile();
    ASSERT_EQ("0~accept~ ", server->LoginToServer("pawel","haslo",1));
    delete server;
}


TEST(socket, availableSocket){
    MockSocket mocksocket;
    EXPECT_CALL(mocksocket, Connect(_)).WillOnce(Return(true));

    Server *server = new Server();
    server->testMock(&mocksocket);

    ASSERT_TRUE(server->ISetSocket(88));
    delete server;
}

TEST(socket, unavailableSocket){
    MockSocket mocksocket;
    EXPECT_CALL(mocksocket, Connect(_)).WillOnce(Return(false));

    Server *server = new Server();
    server->testMock(&mocksocket);

    ASSERT_FALSE(server->ISetSocket(88));
    delete server;
}

TEST(socket, availablePort){
    MockSocket mocksocket;
    EXPECT_CALL(mocksocket, Bind(_,_)).WillOnce(Return(true));

    Server *server = new Server();
    server->testMock(&mocksocket);

    ASSERT_TRUE(server->IBindPort());
    delete server;
}

TEST(socket, unavailablePort){
    MockSocket mocksocket;
    ON_CALL(mocksocket, Bind(_,_)).WillByDefault(Return(false));

    Server *server = new Server();
    server->testMock(&mocksocket);

    ASSERT_FALSE(server->IBindPort());
    delete server;
}

TEST(connection, correctInit){
    MockSocket mocksocket;
    ON_CALL(mocksocket, Connect(_)).WillByDefault(Return(true));
    ON_CALL(mocksocket, Bind(_,_)).WillByDefault(Return(true));

    Server *server = new Server();
    server->testMock(&mocksocket);

    ASSERT_TRUE(server->IInitConnection(88));
    delete server;
}

TEST(connection, incorrectInitBindFalse){
    MockSocket mocksocket;
    ON_CALL(mocksocket, Connect(_)).WillByDefault(Return(true));
    ON_CALL(mocksocket, Bind(_,_)).WillByDefault(Return(false));

    Server *server = new Server();
    server->testMock(&mocksocket);

    ASSERT_FALSE(server->IInitConnection(88));
    delete server;
}

TEST(connection, incorrectInitSetSocketFalse){
    MockSocket mocksocket;
    ON_CALL(mocksocket, Connect(_)).WillByDefault(Return(false));
    ON_CALL(mocksocket, Bind(_,_)).WillByDefault(Return(true));


    Server *server = new Server();
    server->testMock(&mocksocket);

    ASSERT_FALSE(server->IInitConnection(88));
    delete server;
}

TEST(connection, incorrectInitSetBothFalse){
    MockSocket mocksocket;
    ON_CALL(mocksocket, Connect(_)).WillByDefault(Return(false));
    ON_CALL(mocksocket, Bind(_,_)).WillByDefault(Return(false));


    Server *server = new Server();
    server->testMock(&mocksocket);

    ASSERT_FALSE(server->IInitConnection(88));
    delete server;
}

int main(int argc, char *argv[])
{

    testing::InitGoogleTest(&argc, argv);
    testing::InitGoogleMock(&argc, argv);
    return RUN_ALL_TESTS();

}


