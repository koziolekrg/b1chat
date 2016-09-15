#include "client.h"
Client::Client(std::string a_hostAddress, int a_port)
{

    sock = socket(AF_INET , SOCK_STREAM , 0);
    if (sock == -1)
    {
        printf("Could not create socket");
    }

    server.sin_addr.s_addr = inet_addr(a_hostAddress.c_str());
    server.sin_family = AF_INET;
    server.sin_port = htons(a_port);

    if (connect(sock , (struct sockaddr *)&server , sizeof(server)) < 0){
        perror("connect failed. Error");
        exit(1);
    }

    puts("Connected\n");

    fd_set all_set, r_set;
    int maxfd = sock + 1;
    FD_ZERO(&all_set);
    FD_SET(STDIN_FILENO, &all_set); FD_SET(sock, &all_set);
    r_set = all_set;
    struct timeval tv; tv.tv_sec = 2; tv.tv_usec = 0;

    //set the initial position of after
    after = message;

    puts("Enter message: ");
    while(1){

        r_set = all_set;
        //check to see if we can read from STDIN or sock
        select(maxfd, &r_set, NULL, NULL, &tv);

        if(FD_ISSET(STDIN_FILENO, &r_set)){

            if(buffer_message(message) == COMPLETE){
                if(send(sock, message, strlen(message) + 1, 0) < 0)
                {
                    std::cout<<"Sending error";
                    exit(1);
                }

                std::cout<<("Enter message:");
            }
        }

        if(FD_ISSET(sock, &r_set)){
            //Receive a reply from the server
            if( recv(sock , server_reply , 256 , 0) < 0)
            {
                std::cout<<"Recv failed";
                break;
            }

            std::cout<<"\nServer Reply:"<<server_reply<<std::endl;
        }
    }

    close(sock);
}

Client::~Client(){

}

int Client::buffer_message(char * message){

    int bytes_read = read(STDIN_FILENO, after, 256 - inbuf);
    short flag = -1; // indicates if returned_data has been set
    inbuf += bytes_read;
    int where; // location of network newline

    // call findeol, store result in where
    where = find_network_newline(message, inbuf);
    if (where >= 0) {

        // place a null terminator at the end of the string
        char * null_c = {'\0'};
        memcpy(message + where, &null_c, 1);

        // update inbuf and remove the full line from the clients's buffer
        memmove(message, message + where + 1, inbuf - (where + 1));
        inbuf -= (where+1);
        flag = 0;
    }

    //update room and after, in preparation for the next read
    room = sizeof(message) - inbuf;
    after = message + inbuf;

    return flag;
}

int Client::find_network_newline(char * message, int bytes_inbuf){
    int i;
    for(i = 0; i<inbuf; i++){
        if( *(message + i) == '\n')
        return i;
    }
    return -1;
}
