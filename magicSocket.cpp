#include "magicSocket.hpp"

MagicSocket::MagicSocket(bool reusable){
    mysockfd = socket(AF_INET6, SOCK_STREAM, IPPROTO_TCP);

    int disable = 0;
    if(setsockopt(mysockfd,IPPROTO_IPV6,IPV6_V6ONLY,(void*)&disable,sizeof(disable)) < 0){
        throw new MagicSocketCreationException;
    }

    if (reusable){
        int yes = 1;
        if (setsockopt(mysockfd,SOL_SOCKET,SO_REUSEADDR,(void*)&yes,sizeof(yes)) == -1){
            throw new MagicSocketCreationException;
        }
    }   
} 

MagicSocket::MagicSocket(int fd){
    mysockfd = fd;
}

void MagicSocket::Close(){
    close(mysockfd);
}

void MagicSocket::setBacklog(int newBacklog){
    if (newBacklog>0){
        backlog = newBacklog;
    }
}

void MagicSocket::Listen(int port){
    struct sockaddr_in6 mSockaddr_in6;
    socklen_t mSockaddr_len = sizeof(sockaddr_in6);
    memset(&mSockaddr_in6, 0, mSockaddr_len);
    mSockaddr_in6.sin6_family = AF_INET6;
    mSockaddr_in6.sin6_port = htons(port);
    mSockaddr_in6.sin6_addr = in6addr_any;

    if (bind(mysockfd,(struct sockaddr*)&mSockaddr_in6,sizeof(mSockaddr_in6)) != 0){
        throw new MagicSocketBindException;
    }
    listen(mysockfd,backlog);
}

MagicSocket MagicSocket::Accept(){
    struct sockaddr_in6 sock_from;
    socklen_t size = sizeof(sockaddr_in6);
    int newsockfd = accept(mysockfd,(struct sockaddr*)&sock_from,&size);
    if (newsockfd < 0){
        throw new MagicSocketAcceptException;
    }
    return MagicSocket(newsockfd);

}

int MagicSocket::Connect(const char *ip, int port){
    close(mysockfd);

    struct addrinfo hints;
    struct addrinfo *address_info, *dst_list;
    char charPort[6];
    int connectionResult = -1;
    sprintf(charPort,"%d",port);

    memset(&hints,0,sizeof(hints));
    hints.ai_family = AF_UNSPEC;
    hints.ai_socktype = SOCK_STREAM;
    hints.ai_protocol = IPPROTO_TCP;
    hints.ai_flags = AI_V4MAPPED | AI_ADDRCONFIG;
    if (getaddrinfo(ip,charPort,&hints,&address_info) != 0){
        throw new MagicSocketConnectException;
    }
    dst_list = address_info;
    do{
        mysockfd = socket(dst_list->ai_family,dst_list->ai_socktype,dst_list->ai_protocol);
        connectionResult = connect(mysockfd,dst_list->ai_addr,dst_list->ai_addrlen);
        if (connectionResult != 0){
            close(mysockfd);
            dst_list = dst_list->ai_next;
        }
    }while(connectionResult != 0 && dst_list!= nullptr);
    freeaddrinfo(address_info);
    return connectionResult;
}

int MagicSocket::Receive(void* buffer, int bufflen ){
    memset(buffer,0,bufflen);
    return recv(mysockfd,buffer,bufflen,0);
}

int MagicSocket::Send(const char *msg){
    int len = strlen(msg);
    return send(mysockfd,msg,len,0);
}
MagicSocket::~MagicSocket(){
    Close();
}
