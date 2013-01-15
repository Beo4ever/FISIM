#ifndef _NET_SOCKET_CLASS_H_
#define _NET_SOCKET_CLASS_H_

#ifdef __unix__
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <netdb.h>
#include <arpa/inet.h>
#include <unistd.h>
#endif

#if defined(_WIN32) || defined(WIN32)
#include <winsock2.h>
#include <Ws2tcpip.h>

#pragma comment(lib, "Ws2_32.lib")
#endif

#include <exception>
#include <string>

class CNetSocket {

    public:
        CNetSocket();
        CNetSocket(int , sockaddr_in);
        virtual ~CNetSocket();
        int send(const char *, int = 0);
        int recv(char *, int);
        void setNonBlocking();
        void setBlocking();
        void setAddr(const char *, const int);
        sockaddr_in & getAddr();
        unsigned int getPort();
#ifdef __unix__
        int & getSock();
        bool isValid() { return _sock >= 0; }
#endif
#if defined(_WIN32) || defined(WIN32)
        SOCKET & getSock();
        bool isValid() { return _sock != INVALID_SOCKET; };
#endif
        void erase();
    protected:
        unsigned int _port;
        char * _address;
        struct sockaddr_in _addr;
#ifdef __unix__
        int _sock;
#endif
#if defined(_WIN32) || defined(WIN32)
        SOCKET _sock;
        WSADATA _wsaData;
#endif
};

class NetException : public std::exception
{
    public:
        NetException(std::string msg) throw() { _msg = msg; }
        ~NetException() throw() {}
        virtual const char* what() const throw()
        {
	
            return _msg.c_str();
        }
        std::string getMsg() {return _msg;}
    private:
        std::string _msg;
};
#endif
