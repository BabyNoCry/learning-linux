#ifndef _SERVER_HPP
#define _SERVER_HPP
#include<iostream>
#include<string.h>
#include<unistd.h>
#include<stdlib.h>
#include<sys/types.h>
#include<sys/socket.h>
#include<netinet/in.h>
#include<arpa/inet.h>
using namespace std;
//流程：创建套接字 绑定端口号 ip  将服务器设置监听模式

class TcpServer{
    private:
        int listen_sock;
        string ip;
        int port;
    public:
        TcpServer(string ip_,int port_):listen_sock(-1),ip(ip_),port(port_)
        { }
        
        void InitServer()
        {
            listen_sock = socket(AF_INET,SOCK_STREAM,0);
            if(listen_sock < 0)
            {

                cerr<<"socket erro"<<endl;
                exit(2);
            }
            struct sockaddr_in local;
            bzero(&local,sizeof(local));//将该结构体清零
            local.sin_family = AF_INET;
            local.sin_port = htons(port);
            local.sin_addr.s_addr = inet_addr(ip.c_str());

            //绑定
            if(bind(listen_sock,(struct sockaddr*)&local,sizeof(local))<0)
            {
                cerr<<"bind error "<<endl;
                exit(3);
            }

            //监听
            if(listen(listen_sock,5)<0)
            {
                cerr<<"listen error"<<endl;
                exit(4);
            }

        }

        void Service(int sock)
        {
            while(1)
            {
                char buf[1024];
                ssize_t s = read(sock,buf,sizeof(buf)-1);
                if(s>0)
                {
                    buf[s] = 0;
                    write(sock,buf,strlen(buf));
                }
                else if(s == 0)
                {
                    cout<<"client quit!"<<endl;
                    break;
                }
                else
                {
                    cerr<<"read error"<<endl;
                    break;
                    
                }
            }
            close(sock);
        }
        void Start()
        {
            struct sockaddr_in peer;
            socklen_t len = sizeof(peer);
            while(1)
            {
                int sock = accept(listen_sock,(struct sockaddr*)&peer,&len);
                if(sock<0)
                {
                    cerr<<"accpet error"<<endl;
                    continue;
                }
                cout<<"Get a new client "<<endl;
                Service(sock);//提供服务
            }
        }

        ~TcpServer()
        {
            if(listen_sock>0)
            {
                close(listen_sock);
            }
        }

};
#endif
