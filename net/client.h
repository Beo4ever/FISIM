#ifndef _NET_CLIENT_CLASS_H_
#define _NET_CLIENT_CLASS_H_

#include "socket.h"

class CNetClient : public CNetSocket 
{
    public:
    CNetClient() : CNetSocket() {_connected = false;}
	CNetClient(int , sockaddr_in);
//	virtual ~CNetClient();
    bool connect(const char *, const int);
    bool disconnect();
    bool isConnected();
    protected:
        bool _connected;
    private:
	CNetClient(const CNetClient&);
	CNetClient& operator=(const CNetClient&);
};
#endif
