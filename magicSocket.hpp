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

    public:

        MagicSocket(bool);
        MagicSocket(int);
        void setBacklog(int);
        void Listen(int);
        MagicSocket Accept();
        int Connect(const char*, int);
        int Receive(void*, int);
        int Send(const char*);
        void Close();
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

