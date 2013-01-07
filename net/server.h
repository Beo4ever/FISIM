#ifndef _NET_SERVER_CLASS_H_
#define _NET_SERVER_CLASS_H_

#include <map>
#include "socket.h"
#include "client.h"

class CNetServer : public CNetSocket {

    public:
	CNetServer() : CNetSocket() { _clientsCount = 0; _clients.clear();}
	~CNetServer();
	int bind(const char *, const int);
	int list(const int);
	CNetClient* accept();
	virtual void erase();
    protected:
	int _maxConnect;
	int _clientsCount;
	std::map <int, CNetClient*> _clients;
	std::map <int, CNetClient*>::iterator _iter;
};
#endif
