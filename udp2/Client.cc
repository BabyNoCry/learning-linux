#include<iostream>
#include<stdlib.h>
#include<unistd.h>
#include<string.h>
#include<sys/types.h>
#include<sys/socket.h>
#include<netinet/in.h>
#include<arpa/inet.h>
void Usage(char* s)
{

    std::cout<<"Usage:"<<s<<"Server_ IP Server_PORT"<<std::endl;
}
int main(int argc,char* argv[])
{
    //创建套接字
    int sock = socket(AF_INET,SOCK_DGRAM,0);
    if(sock != 3 )
    {
        Usage(argv[0]);
        return 1;
    }
    std::cout<<"sock:"<<sock<<std::endl;
    struct sockaddr_in server;
    server.sin_family = AF_INET;
    server.sin_port = htons( atoi(argv[2]));
    server.sin_addr.s_addr = inet_addr(argv[1]);
    char buf[1024];
    for(;;)
    {
        std::cout<<"please enter# ";
        std::cin>>buf;
        struct sockaddr_in peer;
        socklen_t len = sizeof(peer);
        sendto(sock,buf,strlen(buf),0,(struct sockaddr*)&server,sizeof(server));
        ssize_t s = recvfrom(sock,buf,sizeof(buf)-1,0,(struct sockaddr* )&peer,&len);
        if(s>0)
        {
            buf[s] = 0;
            std:: cout<<"Server echo# "<<buf<<std::endl;
        }
        
        
    }
    close(sock);
    return 0;
}
