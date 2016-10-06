
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
    ASSERT_EQ("Test", group->getTitle());
    delete group;
}

TEST(group, correctAddClient){
    Group *group = new Group("Test", 1);
    ASSERT_EQ(true, group->addClient(2));
    delete group;
}

TEST(group, incorrectAddClient){
    Group *group = new Group("Test", 1);
    ASSERT_EQ(false, group->addClient(1));
    delete group;
}

TEST(group, listClient){
    Group *group = new Group("Test", 1);
    group->addClient(2);
    int temp = (group->getClientsList())[1];
    ASSERT_EQ(2, temp);
    delete group;
}

TEST(privGroup, correctAddNewGroup){
    Priv priv;
    ASSERT_EQ(true, priv.addNewGroup("G1",4));
}

TEST(privGroup, correctAddNewGroup_1){
    Priv priv;
    priv.addNewGroup("G1",2);
    ASSERT_EQ(true, priv.addNewGroup("G2",4));
}

TEST(privGroup, incorrectAddNewGroup){
    Priv priv;
    priv.addNewGroup("G1",2);
    ASSERT_EQ(false, priv.addNewGroup("G1",4));
}

TEST(privGroup, correctAddNewClientGroup_1){
    Priv priv;
    priv.addNewGroup("G1",2);
    ASSERT_EQ(true, priv.addNewClientToGroup("G1", 3));
}

TEST(privGroup, correctAddNewClientGroup_2){
    Priv priv;
    priv.addNewGroup("G1",2);
    priv.addNewClientToGroup("G1", 4);
    ASSERT_EQ(true, priv.addNewClientToGroup("G1", 3));
}

TEST(privGroup, incorrectAddNewClientGroup){
    Priv priv;
    priv.addNewGroup("G1",2);
    ASSERT_EQ(false, priv.addNewClientToGroup("G2", 3));
}

TEST(account, succesfulCreate){
    MockSocket mocksocket;
    Server server(mocksocket);
    ASSERT_EQ("1~accept~ ",server.createAccount("pawel","haslo",1));
}

TEST(account, failureCreate){
    MockSocket mocksocket;
    Server server(mocksocket);
    server.createAccount("pawel","haslo",1);
    ASSERT_EQ("1~refuse~ ",server.createAccount("pawel","haslo",1));
}

TEST(account, logoutAndSuccesfulLogin){
    int16_t temp =1;
    MockSocket mocksocket;
    Server server(mocksocket);
    server.createAccount("pawel","haslo",1);
    server.logout(temp);
    ASSERT_EQ("0~accept~ ", server.loginToServer("pawel","haslo",1));
}

TEST(account, failureLogin){
    MockSocket mocksocket;
    Server server(mocksocket);
    ASSERT_EQ("0~refuse~ ", server.loginToServer("pawel","haslo",1));
}

TEST(file, savefile){
    MockSocket mocksocket;
    Server server(mocksocket);
    server.createAccount("pawel","haslo",1);
    ASSERT_EQ(true,server.saveFile());
}

TEST(file, readfile){
    MockSocket mocksocket;
    Server server(mocksocket);
    server.readFile();
    ASSERT_EQ("0~accept~ ", server.loginToServer("pawel","haslo",1));
}


TEST(socket, availableSocket){
    MockSocket mocksocket;
    EXPECT_CALL(mocksocket, Connect(_)).WillOnce(Return(true));

    Server server(mocksocket);
    ASSERT_TRUE(server.setSocket(88));
}

TEST(socket, unavailableSocket){
    MockSocket mocksocket;
    EXPECT_CALL(mocksocket, Connect(_)).WillOnce(Return(false));

    Server server(mocksocket);
    ASSERT_FALSE(server.setSocket(88));
}

TEST(socket, availablePort){
    MockSocket mocksocket;
    EXPECT_CALL(mocksocket, Bind(_,_)).WillOnce(Return(true));

    Server server(mocksocket);
    ASSERT_TRUE(server.bindPort());
}

TEST(socket, unavailablePort){
    MockSocket mocksocket;
    ON_CALL(mocksocket, Bind(_,_)).WillByDefault(Return(false));

    Server server(mocksocket);
    ASSERT_FALSE(server.bindPort());
}

TEST(connection, correctInit){
    MockSocket mocksocket;
    ON_CALL(mocksocket, Connect(_)).WillByDefault(Return(true));
    ON_CALL(mocksocket, Bind(_,_)).WillByDefault(Return(true));

    Server server(mocksocket);
    ASSERT_TRUE(server.initConnection(88));
}

TEST(connection, incorrectInitBindFalse){
    MockSocket mocksocket;
    ON_CALL(mocksocket, Connect(_)).WillByDefault(Return(true));
    ON_CALL(mocksocket, Bind(_,_)).WillByDefault(Return(false));

    Server server(mocksocket);
    ASSERT_FALSE(server.initConnection(88));
}

TEST(connection, incorrectInitSetSocketFalse){
    MockSocket mocksocket;
    ON_CALL(mocksocket, Connect(_)).WillByDefault(Return(false));
    ON_CALL(mocksocket, Bind(_,_)).WillByDefault(Return(true));

    Server server(mocksocket);
    ASSERT_FALSE(server.initConnection(88));
}

TEST(connection, incorrectInitSetBothFalse){
    MockSocket mocksocket;
    ON_CALL(mocksocket, Connect(_)).WillByDefault(Return(false));
    ON_CALL(mocksocket, Bind(_,_)).WillByDefault(Return(false));

    Server server(mocksocket);
    ASSERT_FALSE(server.initConnection(88));
}

int main(int argc, char *argv[])
{

    testing::InitGoogleTest(&argc, argv);
    testing::InitGoogleMock(&argc, argv);
    return RUN_ALL_TESTS();

}


