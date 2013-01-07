#include "client.h"

CNetClient::CNetClient(int sock, sockaddr_in addr)
{
    _sock = sock;
    _addr = addr;
    _connected = false;

    if(!isValid()) {
        throw NetException("Client Construct Error");
    }
}

bool CNetClient::connect(const char * address, const int port)
{
    setAddr(address, port);
    int result = ::connect(_sock, (struct sockaddr *)&_addr, sizeof(_addr));
    if(result < 0) {
        throw NetException("Client Connect Error");
    }
    _connected = true;

    return true;
}

bool CNetClient::disconnect()
{

    int result = ::shutdown(_sock, 0);
    if(result < 0) {
        throw NetException("Client Disconnect Error");
    }
    _connected = false;

    return true;
}

bool CNetClient::isConnected()
{

    return (_connected == true);
}
