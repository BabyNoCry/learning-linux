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

    std::cout<<"Usage:"<<s<<" IP PORT"<<std::endl;
}
int main(int argc,char* argv[])
{
    //创建套接字
    int sock = socket(AF_INET,SOCK_DGRAM,0);
    if(argc != 3 )
    {
        Usage(argv[0]);
        return 1;
    }
    std::cout<<"sock:"<<sock<<std::endl;
    struct sockaddr_in local;
    local.sin_family = AF_INET;
    local.sin_port = htons( atoi(argv[2]));
    local.sin_addr.s_addr = inet_addr(argv[1]);
    //绑定端口号
    if(bind(sock,(struct sockaddr*)&local,sizeof(local))<0)
    {
        std::cerr<<"bind err"<<std::endl;
        return 2;
    }
    char buf[1024];
    for(;;)
    {
        struct sockaddr_in peer;
        socklen_t len = sizeof(peer);
        ssize_t s = recvfrom(sock,buf,sizeof(buf)-1,0,(struct sockaddr* )&peer,&len);
        if(s>0)
        {
            buf[s] = 0;
            std:: cout<<"client# "<<buf<<std::endl;
             sendto(sock,buf,strlen(buf),0,(struct sockaddr*)&peer,len);
        }
        
    }
    close(sock);
    return 0;
}
