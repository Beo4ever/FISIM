#if defined(_WIN32) || defined(WIN32)
#include "../stdafx.h"
#endif
#include "socket.h"
#include <string.h>
#include <fcntl.h>
#include <iostream>

CNetSocket::CNetSocket()
{
#if defined(_WIN32) || defined(WIN32)
    int wsaInitError = WSAStartup(0x0202, &_wsaData);
    if(wsaInitError != NO_ERROR) { // != 0
        throw NetException("WSAStartup error");
    }
#endif
    _sock = socket(AF_INET, SOCK_STREAM, 0);

    if(!isValid()) {
        throw NetException("Socket error");
    }

    // TIME_WAIT - argh
    int on = 1;
    if (setsockopt(_sock, SOL_SOCKET, SO_REUSEADDR, (char*)&on, sizeof(on)) < 0) {
        throw NetException("Socket set reuse error");
    }

    memset(&_addr, 0, sizeof(_addr));
}

CNetSocket::~CNetSocket()
{
    erase();
}

int CNetSocket::send(const char * buf, int len)
{

    return ::send(_sock, buf, len, 0);
}

int CNetSocket::recv(char * buf, int len)
{

    return ::recv(_sock, buf, len, 0);
}

void CNetSocket::setNonBlocking()
{
#ifdef __unix__
    int opts;
    opts = fcntl(_sock, F_GETFL);

    if (opts < 0) {

        return;
    }

    opts = (opts | O_NONBLOCK);
    fcntl(_sock, F_SETFL, opts);
#endif
#if defined(_WIN32) || defined(WIN32)
    ioctlsocket(_sock, FIONBIO, (unsigned long *)1);
#endif
}

void CNetSocket::setBlocking()
{
#ifdef __unix__
    int opts;
    opts = fcntl(_sock, F_GETFL);

    if (opts < 0) {

        return;
    }

    opts = (opts & ~O_NONBLOCK);
    fcntl(_sock, F_SETFL, opts);
#endif
#if defined(_WIN32) || defined(WIN32)
    ioctlsocket(_sock, FIONBIO, (unsigned long *)0);
#endif
}

void CNetSocket::setAddr(const char * address, const int port)
{
    _address = (char*) address;
    _port = port;

    memset(&_addr, 0, sizeof(_addr));

    _addr.sin_family = AF_INET;
    _addr.sin_port = htons(_port);
    if(strcmp(address, "0.0.0.0") == 0) {
        _addr.sin_addr.s_addr = htonl(INADDR_ANY);
    } else {
        inet_pton(AF_INET, address, &(_addr.sin_addr));
    }
}

sockaddr_in & CNetSocket::getAddr()
{

    return _addr;
}

unsigned int CNetSocket::getPort()
{

    return _port;
}

#ifdef __unix__
int& CNetSocket::getSock()
{

    return _sock;
}
#endif
#if defined(_WIN32) || defined(WIN32)
SOCKET& CNetSocket::getSock()
{

    return _sock;
}
#endif

void CNetSocket::erase()
{
    if(isValid()){
#ifdef __unix__
        close(_sock);
#endif
#if defined(_WIN32) || defined(WIN32)
        closesocket(_sock);
#endif
    }

#ifdef __unix__
    _sock = -1;
#endif
#if defined(_WIN32) || defined(WIN32)
    WSACleanup();
#endif

    memset(&_addr, 0, sizeof(_addr));
    memset(&_address, 0, sizeof(_address));
    memset(&_port, 0, sizeof(_port));
}
