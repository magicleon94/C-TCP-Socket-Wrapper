#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <netdb.h>
#include <arpa/inet.h>
#include <sys/wait.h>
#include <exception>



class MagicSocket{
    private:
        int mysockfd;
        int backlog;
        MagicSocket(int);

    public:
        /* The constructor parameter specifies wether the socket should be reusable or not */
        MagicSocket(bool reusable);  
        /* Edit the backlog to whatever you need (negative values will be ignored) */
        void setBacklog(int newBacklogValue);
        /* Bind the socket and start listening */
        void Listen(int port);
        /* Accept an incoming connection and return the new socket */
        MagicSocket Accept();
        /* Connect to a node */
        int Connect(const char* ip, int port);
        /* Receive data on a buffer */
        int Receive(void* buffer, int bufflen);
        /* Send a message */
        int Send(const void* buffer, int bufflen);
        /* Close the socket */
        void Close();
        /* Destroy the socket */
        ~MagicSocket();
};

class MagicSocketCreationException : public std::exception{
    virtual const char *what() const throw()
    {
        return "There was an error while creating the MagicSocket Object";
    }
};

class MagicSocketBindException : public std::exception{
    virtual const char *what() const throw()
    {
        return "There was an error while creating the MagicSocket Object";
    }
};

class MagicSocketConnectException : public std::exception{
    virtual const char *what() const throw()
    {
        return "There was an error while creating the MagicSocket Object";
    }
};

class MagicSocketAcceptException : public std::exception{

    virtual const char *what() const throw()
    {
        return "There was an error while creating the MagicSocket Object";
    }
};

