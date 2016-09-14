#include <iostream>
#include "server.h"

using namespace std;

int main(int argc, char *argv[])
{
    Server * server = new Server(atoi(argv[1]));

    return 0;
}

