#include "server.h"
#include <string.h>
#include <fcntl.h>
#include <iostream>

CNetServer::~CNetServer()
{
    erase();
}

int CNetServer::bind(const char * address, const int port)
{
    if(!isValid()) {
        throw NetException("Server Socket error");
    }

    setAddr(address, port);

    int result = ::bind(_sock, (struct sockaddr *) & _addr, sizeof(_addr));

    if(result < 0) {
        throw NetException("Server Bind error");
    }

    return 0;
}

int CNetServer::list(const int maxConnect)
{
    if(!isValid()) {
        throw NetException("Server Socket error");
    }

    _maxConnect = maxConnect;
    int result = ::listen(_sock, _maxConnect);

    if(result < 0) {
        throw NetException("Server Listen Error");
    }

    return 0;
}

CNetClient * CNetServer::accept()
{
    struct sockaddr_in addr;
    int addrLen = sizeof(addr);

    memset(&addr, 0, addrLen);

    int sock = ::accept(_sock, (struct sockaddr *) &addr, (socklen_t *) &addrLen);
    _clients.push_back(new CNetClient(sock, addr));

    return _clients.back();
}

void CNetServer::erase()
{
    for (_iter = _clients.begin(); _iter != _clients.end(); _iter++)
    {
        (*_iter)->erase();
        delete (*_iter);
    }
    _clients.clear();
}
