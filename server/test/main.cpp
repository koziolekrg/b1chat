#include <stdio.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <netdb.h>
#include <iostream>
#include "server.h"
#include <gtest/gtest.h>
#define PORT 8888

TEST(group, groupTitle){
    Group *group = new Group("Test", 1);
    ASSERT_EQ("Test", group->IGetTitle());
}

TEST(group, correctAddClient){
    Group *group = new Group("Test", 1);
    ASSERT_EQ(true, group->IAddClient(2));
}

TEST(group, incorrectAddClient){
    Group *group = new Group("Test", 1);
    ASSERT_EQ(false, group->IAddClient(1));
}

TEST(group, listClient){
    Group *group = new Group("Test", 1);
    group->IAddClient(2);
    int temp = (group->IGetClientsList())[1];
    ASSERT_EQ(2, temp);
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
}

TEST(account, failureCreate){
    Server *server = new Server();
    server->CreateAccount("pawel","haslo",1);
    ASSERT_EQ("1~refuse~ ",server->CreateAccount("pawel","haslo",1));
}

TEST(account, logoutAndSuccesfulLogin){
    int16_t temp =1;
    Server *server = new Server();
    server->CreateAccount("pawel","haslo",1);
    server->Logout(temp);
    ASSERT_EQ("0~accept~ ", server->LoginToServer("pawel","haslo",1));
}

TEST(account, failureLogin){
    Server *server = new Server();
    ASSERT_EQ("0~refuse~ ", server->LoginToServer("pawel","haslo",1));
}

TEST(file, savefile){
    Server *server = new Server();
    server->CreateAccount("pawel","haslo",1);
    ASSERT_EQ(true,server->ISaveFile());
}

TEST(file, readfile){
    Server *server = new Server();
    server->IReadFile();
    ASSERT_EQ("0~accept~ ", server->LoginToServer("pawel","haslo",1));
}


int main(int argc, char *argv[])
{

    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();

}


