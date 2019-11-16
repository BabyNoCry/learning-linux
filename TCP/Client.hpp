#ifndef _CLIENT_HPP
#define _CLIENT_HPP
#include<sys/types.h>
#include<iostream>
#include<netinet/in.h>
#include<arpa/inet.h>
#include<string>
#include<string.h>
#include<sys/socket.h>
#include<unistd.h>
#include<stdlib.h>
#include<iostream>
using namespace std;
class TcpClient{

    private:
        int sock;
        string ip;
        int port;
    public:
    TcpClient(string ip_,int port_):sock(-1),ip(ip_),port(port)
    {
    }

     void InitClient()
    {

        sock = socket(AF_INET, SOCK_STREAM,0); 
        if(sock<0)
        {
            cerr<<"socket error "<<endl;
            exit(2);
        }
    }

     void Start()
     {
         struct sockaddr_in peer;
         bzero(&peer,sizeof(peer));
         //客户端必须先与服务端建立连接
         peer.sin_family = AF_INET;
         peer.sin_port = htons(port);
         peer.sin_addr.s_addr = inet_addr(ip.c_str());
        
         if(connect(sock,(struct sockaddr*)&peer,sizeof(peer))<0)
         {
             cerr<<"connect error"<<endl;
             exit(3);
         }
         char buf[1024];
         string in;
         while(1)
         {
            cout<<"Please Enter#";
            cin>>in;
            write(sock,in.c_str(),in.size());
            int s = read(sock,buf,sizeof(buf)-1);
            if(s>0)
            {
                buf[s] = 0;
                cout<<"Server Echo#"<<buf<<endl;
            }
         }

     }
     ~TcpClient();
};
#endif
