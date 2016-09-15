#include <iostream>
#include <stdlib.h>
#include "client.h"


using namespace std;

int main(int argc, char *argv[])
{
    Client * client = new Client(argv[1], atoi(argv[2]));

    return 0;
}

